/*
 * SmartRoom2.c
 *
 * Created: 11/28/2017 3:30:21 PM
 * Author : MSN
 */ 
#include <avr/io.h>
#include <util/delay.h>
//PD0 >> DP
//PD1 >> G
//PD2 >> F
//PD3 >> E
//PD4 >> D
//PD5 >> C
//PD6 >> B
//PD7 >> A

void sevenSegDec(unsigned char decimal){
	switch(decimal){
		case 0: PORTD = 0b10000001; break;
		case 1: PORTD = 0b11100111; break;
		case 2: PORTD = 0b01001001; break;
		case 3: PORTD = 0b01000011; break;
		case 4: PORTD = 0b00100111; break;
		case 5: PORTD = 0b00010011; break;
		case 6: PORTD = 0b00010001; break;
		case 7: PORTD = 0b11000111; break;
		case 8: PORTD = 0b00000001; break;
		case 9: PORTD = 0b00000011; break;
	}
}

void lightAndHeatSystem(){
	ADCSRA |= (1<<ADSC);
	while ((ADCSRA & (1<<ADIF)) == 0);
	//Min = 0, Max = 0x03FF = 1023
	if (ADC>=512 && ADC<=607){
		//turn on PORTC/PINS(2,3,4,5)
		PORTC = 0b00111100;

	}
	if (ADC>=608 && ADC<=703){
		//turn on PORTC/PINS(2,3,4)
		PORTC = 0b00011100;
	}
	if (ADC>=704 && ADC<=799){
		//turn on PORTC/PINS(2,3)
		PORTC = 0b00001100;
	}
	if (ADC>=800 && ADC<=895){
		//turn on PORTC/PINS(2)
		PORTC = 0b00000100;
	}
	//clear the interrupt flag
	ADCSRA |= (1<<ADIF);
	//ADCSRA = 0b10000111;
	//set the MUX to the temperature sensor
	ADMUX = 0b01000001;
	//start conversion
	ADCSRA |= (1<<ADSC);
	while ((ADCSRA & (1<<ADIF)) == 0);
	//Min = 0, Max = 0x03FF = 1023
	if(ADC<140){
		//turn off the fan
		PORTB &= ~(1 << 0);
		//turn off test led
		PORTB &= ~(1 << 3);
	} else {
		//turn on the fan
		PORTB |= (1 << 0);
		//turn on test led
		PORTB |= (1 << 3);
	}
	//clear the interrupt flag
	ADCSRA |= (1<<ADIF);
	//set the MUX to the LDR
	ADMUX = 0b01000000;
}

int main(void)
{
	unsigned char counter = 0;
	//set PORTD to 7-SEG-DEC o/p
	DDRD = 0xFF;
	DDRB &= ~(1<<1);
	DDRB &= ~(1<<2);
	PORTB |= (1<<1);
	PORTB |= (1<<2);
	unsigned char in = 0;
	unsigned char out = 0;

	//set PORTC/PINS(2,3,4,5) to be output
	DDRC |= 0b00111100;
	//set PORTC/PIN(0) to be input -LDR-
	DDRC &= ~(1 << 0);

	//set PORTC/PIN(1) to be input -temperature sensor-
	DDRC &= ~(1 << 1);
	//pull-up resistor
	PORTC |= (1 << 1);
	//set PORTB/PIN(0) to be the output -fan-
	DDRB |= (1 << 0);

	//set PORTB/PIN(3) to be the led test output -led TEST-
	DDRB |= (1 << 3);

	//REFS1 REFS0 ADLAR - MUX3 MUX2 MUX1 MUX0
	ADMUX = 0b01000000;
	//ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0
	ADCSRA = 0b10000111;

	while (1)
	{
		if(counter>0){
			lightAndHeatSystem();
			} else {
			//turn off the LEDs
			PORTC &= ~(0b00111100);
			//turn off the fan
			PORTB &= ~(1 << 0);
			//turn off test led
			PORTB &= ~(1 << 3);
		}

		if((PINB&(1<<1)) == 0){
			in = 1;
			_delay_ms(500);
		}
		while(in && ((PINB&(1<<1)) == 0));
		if(in && (counter<9)){
			in = 0;
			counter++;
		}

		if((PINB&(1<<2)) == 0){
			out = 1;
			_delay_ms(500);
		}
		while(out && ((PINB&(1<<2)) == 0));
		if(out && (counter>0)){
			out = 0;
			counter--;
		}

		sevenSegDec(counter);
		_delay_ms(500);

	}

	return 0;
}

