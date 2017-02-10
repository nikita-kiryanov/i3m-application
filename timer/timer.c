#include "timer.h"
#include "../lib/syntax.h"

extern struct scheduler_task adc_tick_task;
extern struct scheduler_task ambient_tick_task;
extern struct scheduler_task pending_req_tick_task;

struct scheduler_tick_task {
	struct scheduler_task task;
	int overlaps_count;
	uint16_t offset;
};

#define NUMBER_OF_TICK_TASKS		3
static struct scheduler_tick_task tick_tasks_to_do[NUMBER_OF_TICK_TASKS] = { 0 };

static uint32_t get_ticks_in_sec()
{
	return sysclk_get_cpu_hz() / tc_get_div();
}

void set_tick_task_timer(double sec_to_update, int task_id)
{
	struct scheduler_tick_task *task = &tick_tasks_to_do[task_id];
	uint32_t ticks = sec_to_update * get_ticks_in_sec();
	uint16_t ticks_to_overflow = TIMER_MAX_VALUE - TCC0.CNT;
	if (ticks < ticks_to_overflow) {
		task->offset = ticks + TCC0.CNT;
		task->overlaps_count = 0;
	} else {
		ticks -= ticks_to_overflow;
		task->overlaps_count = ticks / TIMER_MAX_VALUE + 1;
		task->offset = ticks % TIMER_MAX_VALUE;
	}
}

static bool task_due_before_scheduled(uint8_t task_id)
{
	return tick_tasks_to_do[task_id].overlaps_count == 0 &&
		(!is_tc_cmp_enable() || tick_tasks_to_do[task_id].offset < TCC0.CCA);
}

static void schedule_closest_task(void)
{
	bool scheduled_task_exists = false;
	array_foreach(struct scheduler_tick_task, tick_tasks_to_do, index) {
		if (task_due_before_scheduled(index)) {
			TCC0.CCA = tick_tasks_to_do[index].offset;
			scheduled_task_exists = true;
		}
	}

	if (scheduled_task_exists)
		tc_cmp_enable();
	else
		tc_cmp_disable();
}

static struct scheduler_tick_task new_tick_task(struct scheduler_task task)
{
	struct scheduler_tick_task res = { 0 };
	res.task = task;
    res.overlaps_count = -1;
    res.offset = 0;
	return res;
}

static bool tc_can_schedule = false;
void switch_tc_interrupt_schedule(bool on)
{
	tc_can_schedule = on;
}

void tc_scheduler_init(void)
{
    tick_tasks_to_do[0] = new_tick_task(pending_req_tick_task);
	tick_tasks_to_do[1] = new_tick_task(ambient_tick_task);
	tick_tasks_to_do[2] = new_tick_task(adc_tick_task);

	array_foreach(struct scheduler_tick_task, tick_tasks_to_do, index)
		set_tick_task_timer(tick_tasks_to_do[index].task.get_recur_period(), index);

	schedule_closest_task();
}

void tasks_init(void)
{
	rtc_scheduler_init();
	tc_scheduler_init();
	switch_rtc_interrupt_schedule(true);
	switch_tc_interrupt_schedule(true);
}

void ticks_task_update_overlap(void)
{
	if (!tc_can_schedule)
		return;

	for (uint8_t i = 0; i < NUMBER_OF_TICK_TASKS; i++) {
		if (tick_tasks_to_do[i].overlaps_count <= 0)
			continue;
		else
			tick_tasks_to_do[i].overlaps_count--;
	}

	schedule_closest_task();
}


void ticks_task_update_work(void)
{
	if (!tc_can_schedule)
		return;

	/* Find expired task and add it to the work queue */
	for (uint8_t i = 0; i < NUMBER_OF_TICK_TASKS; i++) {
		if (tick_tasks_to_do[i].overlaps_count == 0 &&  tick_tasks_to_do[i].offset <= TCC0.CNT) {
			if (!insert_work(tick_tasks_to_do[i].task.work))
				insert_to_log('T'+i);
			set_tick_task_timer(tick_tasks_to_do[i].task.get_recur_period(), i);
		}
	}

	schedule_closest_task();
}

/*
 * Updating the time of tasks (By ticks) to start
 */
ISR(TCC0_CCA_vect)
{
	ticks_task_update_work();
}

/*
 * Updating the overlaps of tick tasks
 */
ISR(TCC0_OVF_vect)
{
	ticks_task_update_overlap();
}
