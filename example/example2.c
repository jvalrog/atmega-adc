#include <avr/io.h>
#include "atmega-adc.h"

// This sample function is called on every ADC read with 2 parameters:
// the current pin/channel where ADC is reading and the actual value.

void myfunction(uint8_t pin, uint16_t value) {
	switch(pin) {
		case(0):
			// do something
			break;
			
		case(1):
			if (value >= 512)
				PORTB = 0xff;
			else
				PORTB = 0;
			break;
			
		case(2):
			// do something else
			break;
	}
}

void main() {
	DDRB = 0xff;
	PORTB = 0;
	
	// set ADC to monitor the first 3 channels using AVCC as reference
	adc_start(ADC_PRESCALER_128, ADC_VREF_AVCC, 3, myfunction);
	
	// enable global interrupts
	sei();
	
	while(1) {
		// your code goes here
	}
}
