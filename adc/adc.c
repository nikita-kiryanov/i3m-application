/*
 * adc.c
 *
 *  Created on: Aug 12, 2015
 *      Author: arkadi
 */
#include "adc.h"
#include <stdio.h>


//***ADC configuration
#define MY_ADC    ADCA
#define MY_ADC_CH ADC_CH0

#define POWER_COUNT		1000

long current_power;
int32_t power_sum;
float gain = 0;
float vcc = 3.3;



void adc_init()
{
	struct adc_config adc_conf;
	struct adc_channel_config adcch_conf;


	adc_read_configuration(&MY_ADC, &adc_conf);
	adcch_read_configuration(&MY_ADC, MY_ADC_CH, &adcch_conf);

	adc_set_conversion_parameters(&adc_conf, ADC_SIGN_ON, ADC_RES_12, ADC_REFSEL_INTVCC2_gc);  //signed, 12-bit resolution, VREF = VCC/2
	adc_set_conversion_trigger(&adc_conf, ADC_TRIG_EVENT_SINGLE, 1, 0);
	adc_set_clock_rate(&adc_conf, 100000UL); // 100KHz. Up to 200000UL=200KHz

	adcch_set_input(&adcch_conf, ADCCH_POS_PIN1, ADCCH_NEG_INTERNAL_GND, gain); // GAIN = 0.5
	adc_write_configuration(&MY_ADC, &adc_conf);
	adcch_write_configuration(&MY_ADC, MY_ADC_CH, &adcch_conf);
	adc_enable(&MY_ADC);
}

double adc_avg()
{
	int16_t i;
	int16_t adca1_result = 0;
	power_sum = 0;
	for (i=0; i < POWER_COUNT ;i++) {
		adc_start_conversion(&MY_ADC, MY_ADC_CH);  //one conversion begins
		adc_wait_for_interrupt_flag(&MY_ADC, MY_ADC_CH);
		adca1_result = adc_get_result(&MY_ADC, MY_ADC_CH); // & 0x0FFF;
//		power_log[i] = adca1_result;
		power_sum = power_sum + adca1_result;
	}

	return power_sum / (i);
}

void print_adc_log(long adc_avg)
{
//	uart_send_string_working("\n\r======== ADC log =====\n\r");
//	uart_send_num_working(POWER_COUNT, 10);
//	uart_send_string_working(" samples:\n\r");
//	for (uint32_t i = 0; i < POWER_COUNT; i++) {
//		uart_send_num_working(power_log[i], 10);
//		uart_send_string_working(", ");
//	}
//
//	uart_send_string_working("\n\r adc sum: ");
//	uart_send_num_working(power_sum, 10);
//	uart_send_string_working("\n\r adc avg: ");
//	uart_send_num_working(adc_avg, 10);
//	uart_send_string_working(" adc result: ");
//	uart_send_num_working(current_power, 10);
}

void set_power_data(char *str)
{
	double avg = adc_avg();
	long power = avg * 0.10137 + 2.9;

	if (power >= 1 && power <= 300) {
		current_power = power;
//		print_adc_log(avg);
		sprintf(str, "%ld W", current_power);
//		strcpy(current_power_str, str);
	}
}
