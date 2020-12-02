#ifndef TC0_HANDLER
#define TC0_HANDLER

#include "vars.h"

#define measPin A1

void 
TC0_Handler( void )
{
	static uint32_t Count = 500000; // 500ms
	TC0->TC_CHANNEL[0].TC_SR;  		// Read and clear status register
	if(Count-- == 0)
	{
		// read voltage from measPin (measPin * (maxVoltage / maxMeasureValue))
		float voltage = analogRead(measPin) * (3.3 / 1023.0);

		// set state according to measured voltage
		voltageState = 
			voltage >= 3.00 ? 
				State::A : 
			voltage >= 2.00 ? 
				State::B : 
			voltage >= 1.00 ? 
				State::C : 
			State::D;

		printf("voltage : %f ; State : %d\n\r", voltage, (int)voltageState);

		// reset count
		Count = 500000;
	}
}

#endif // TC0_HANDLER