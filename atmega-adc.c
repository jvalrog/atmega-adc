#include "atmega-adc.h"

void (*_adc_handler)(uint8_t pin, uint16_t);
volatile uint8_t _adc_pin_qty;

uint16_t adc_read(uint8_t prescaler, uint8_t vref, uint8_t pin) {
#ifdef MUX5
	if (pin > 7) {
		ADCSRB |= _BV(MUX5);
		ADMUX = vref | (pin - 8);
	} else {
		ADCSRB &= ~(_BV(MUX5));
		ADMUX = vref | pin;
	}
#else
	ADMUX = vref | pin;
#endif
	
	ADCSRA = _BV(ADEN) | _BV(ADSC) | prescaler;
	while(!(ADCSRA & _BV(ADIF)));
	
	return (ADCL | (ADCH<<8));
}

void adc_start(uint8_t prescaler, uint8_t vref, uint8_t pin_qty, void (*handler)(uint8_t, uint16_t)) {
	_adc_handler = handler;
	_adc_pin_qty = pin_qty;
	ADMUX = vref;
#ifdef MUX5
	ADCSRB &= ~(_BV(MUX5));
#endif
	ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADIE) | prescaler;
}

void adc_stop() {
	ADCSRA = 0;
}

#ifdef ENABLE_ADC_INT
ISR(ADC_vect) {
	static uint8_t cur_pin = 0;
	
	_adc_handler(cur_pin, ADCL | (ADCH<<8));

	cur_pin++;
	if (cur_pin >= _adc_pin_qty)
		cur_pin = 0;
	
#ifdef MUX5
	if (cur_pin > 7) {
		ADCSRB |= _BV(MUX5);
		ADMUX = (ADMUX & 0xe0) | (cur_pin - 8);
	} else {
		ADCSRB &= ~(_BV(MUX5));
		ADMUX = (ADMUX & 0xe0) | cur_pin;
	}
#else
	ADMUX = (ADMUX & 0xe0) | cur_pin;
#endif

	ADCSRA |= _BV(ADSC);
}
#endif
