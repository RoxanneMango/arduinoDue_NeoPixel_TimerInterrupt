#include <Arduino.h>

#include "TC0_handler.h"
#include "neo_pixel.h"
//
#include "vars.h"

int
main( void )
{
	// init arduino (due)
	watchdogSetup();
	init();
	delay(1);

	// set maximum voltage that can be measured on analog input pins to default (3.3v)
	analogReference(AR_DEFAULT);

	// Enable printf on serial output
	RingBuffer rx_buffer;
	RingBuffer tx_buffer;
	UARTClass uart(UART, UART_IRQn, ID_UART, &rx_buffer, &tx_buffer);
	uart.begin(9600);

	// Enable interrupts on TimerClock 0 channel [0]
	NVIC_EnableIRQ(TC0_IRQn);
	pmc_enable_periph_clk(ID_TC0);
	TC_Configure(TC0, 0, TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_WAVSEL_UP_RC);
	//
	TC0->TC_CHANNEL[0].TC_RC = 42;							// Frequency = (Mck/2)/TC_RC  Hz = 1 MHz
	TC0->TC_CHANNEL[0].TC_RA = 5;							// Duty cycle = (TC_RA/TC_RC) * 100  %
	TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;				// Interrupt on RC compare match
	TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG | TC_CCR_CLKEN;// Software trigger TC0 counter and enable

	// init neopixel controller
	unsigned int ledNum = 1;
	unsigned int ledPin = 6;
	//
	NeoPixelController neoPixelController(ledNum, ledPin);
	neoPixelController.init();

	// attach powerLoss interrupt on powerLostPin and call neopixel clear() on interrupt
	// attachInterrupt(digitalPinToInterrupt(powerLostPin), neoPixelController.clear(), FALLING);

	for (;;)
	{
		switch(voltageState)
		{
			case State::A:
			{
				neoPixelController.setColor(255, 0, 0);		// RED
				break;
			}
			case State::B:
			{
				neoPixelController.setColor(255, 124, 0);	// ORANGE
				break;
			}
			case State::C:
			{
				neoPixelController.setColor(255, 255, 0);	// YELLOW
				break;
			}
			case State::D:
			{
				neoPixelController.setColor(0, 255, 0);		// GREEN
				break;
			}
		}
		neoPixelController.update();
	}
	return 0;
}