# atmega-adc

`atmega-adc` is an Arduino/Avr compatible library to control Analogic-To-Digital conversor (ADC). It
supports up to 16 ADC channels.

## Description

Three functions are currently provided:

	uint16_t adc_read(uint8_t prescaler, uint8_t vref, uint8_t pin)
	
- This function reads the value on an specific channel only once.
	
- Where `prescaler` is a predefined constant to choose from:

		ADC_PRESCALER_2
		ADC_PRESCALER_4
		ADC_PRESCALER_16
		ADC_PRESCALER_32
		ADC_PRESCALER_64
		ADC_PRESCALER_128

- `vref` is another constant needed to select voltage reference:
	
		ADC_VREF_AREF
		ADC_VREF_AVCC
		ADC_VREF_MISC1
		ADC_VREF_MISC2
	
- And `pin` is the channel to read from: 0-7 or 0-16 if available.
	
	
	void adc_start(uint8_t prescaler, uint8_t vref, uint8_t pin_qty, void (*handler)(uint8_t, uint16_t))
	
- This function uses the ADC interrupt to read values from a number of channels. A user defined
function handler is used to process the data.
	
- `prescaler` and `vref` are the same constants as above.
	
- `pin_qty` is the number of pins/channels to read from: 1-8 or 1-16 if available.
	
- `handler` is the user defined function, and it should be defined as:
	
		void examle(uint8_t pin, uint16_t value) {
			// code goes here
		}


	`void adc_stop()`

- This function stops the ADC and disables the interrupt.

## Sample Code

- Using `adc_read`:

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

- Using `adc_start`:

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

## Running it in Arduino

1. Download the source code by using the Download Button on this page
2. Rename and install the library as: `{arduino_path}/libraries/AtmegaADC`
3. Open Arduino and go to "Import Library" option. Choose AtmegaADC from menu.

## Atmel Model Support

It should work with a long range of devices, for example:

- atmega48, 88, 168, 328
- atmega164, 324, 644, 1284
- atmega640, 1280, 1281, 2560, 2561
- atmega325, 645
- ...
