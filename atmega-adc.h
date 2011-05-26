#ifndef atmega_adc_h
#define atmega_adc_h

#ifdef __cplusplus
extern "C" {
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

// Comment or delete this line to disable interrupt definition.
// You can still use the "adc_read" function if this is disabled.
#define ENABLE_ADC_INT

#define ADC_PRESCALER_2 	0
#define ADC_PRESCALER_4 	2
#define ADC_PRESCALER_16 	4
#define ADC_PRESCALER_32 	5
#define ADC_PRESCALER_64 	6
#define ADC_PRESCALER_128 	7

#define ADC_VREF_AREF 	0
#define ADC_VREF_AVCC 	64
#define ADC_VREF_MISC1 	128
#define ADC_VREF_MISC2 	192


uint16_t adc_read(uint8_t prescaler, uint8_t vref, uint8_t pin);
void adc_start(uint8_t prescaler, uint8_t vref, uint8_t pin_qty, void (*handler)(uint8_t, uint16_t));
void adc_stop();

#ifdef __cplusplus
}
#endif

#endif
