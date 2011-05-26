#include <avr/io.h>
#include "atmega-adc.h"

// In this example we toggle PORTB when ADC value on channel 0 is bigger
// than 512

void main() {
	DDRB = 0xff;
	PORTB = 0;
	
	while(1) {
		if (adc_read(ADC_PRESCALER_128, ADC_VREF_AVCC, 0) >= 512)
			PORTB = 0xff;
		else
			PORTB = 0;
	}
}
