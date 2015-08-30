#include <string.h>
#include <math.h>
#include "twi/twi-slave.h"
#include "gfx/gfx_components.h"
#include "debug.h"
#include "gfx/menu-handler.h"
#include "twi/testTwi.h"
#include "timer/tc.h"
#include "adc/adc.h"
#include "config/cnf_blk_components.h"
#include "gfx/gfx_utils.h"
#include "gfx/sampleMenus/sampleConfig.h"
#include "gfx/sampleMenus/sampleMainMenu.h"

ISR(TWIE_TWIS_vect)
{
	twi_slave_interrupt_handler();
}

ISR(TWIC_TWIM_vect){
	interrupt_handler();
}


ISR(PORTF_INT0_vect){
	update_power_state();
}

ISR(TCC0_OVF_vect){
	menu_handler();
}

void init_menu(){
	load_config_block();
	set_menu_by_id(&present_menu,0);
	gfx_action_menu_init(present_menu);
}

void power_state_interrupts_init(){
	PORTF.INTCTRL =  PORT_INT0LVL_MED_gc;
	PORTF.INT0MASK = PIN0_bm | PIN1_bm |PIN2_bm;
	update_power_state();
}



void update_data(uint8_t data){
	MSG_T_N("data updated:" ,data)
	delay_s(3);
	init_menu();
}

void power_state_init(){
	power_state_interrupts_init();
	uint8_t sreg = SREG;
	uint8_t pin_cfg =(uint8_t)  PORT_ISC_BOTHEDGES_gc | PORT_OPC_PULLUP_gc;
	cli();
	PORTCFG.MPCMASK = PIN0_bm | PIN1_bm | PIN2_bm;
	PORTF.PIN0CTRL = pin_cfg;
	SREG = sreg;
}

void init(){
	board_init();
	sysclk_init();
	gfx_mono_init();
	adc_init();
	pmic_init();
	power_state_init();
	tc_init();
	sei();
	twi_slave_init();
	twi_master_init();
}

void test_twi(){
	send_write_package();
	delay_s(1);
	send_read_package(update_data);
}



int main(void){
	init();
	init_menu();
//	testTWI();
//	delay_s(5);
//	initMenu();
	PORTC.DIR |= PIN4_bm;
	PORTC.OUT &= ~PIN4_bm;
	while(true)
	{}
}
