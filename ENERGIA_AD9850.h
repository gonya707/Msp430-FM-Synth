/*   Library for Stellaris and MSP430 boards with Energia.
 *
 *    This library contains several functions for using with a DDS generator
 *    AD9850 module. All the functions are intended to work with this device
 *    in SERIAL mode, so you need to connect the parallel pins D0 and D1 to VCC
 *    and D2 GND, as written in the AD9850 datasheet. For further information
 *    check the Analog Devices website.
 *
 *    Coded by Gonzalo Recio
 *
 *	  http://grsynth.com
 */
 
#include "Energia.h"

#ifndef ENERGIA_AD9850_H
	#define ENERGIA_AD9850_H

	//Frequency of your crystal oscillator (CLKIN input pin 9 in datasheet), measured in MHz.
	// This reference frequency must be higher than 1MHz.
	#define XTAL_MHZ 125

	//Relationship value between actual frequency and 32-bit word sent in the serial streaming
	#define FREQ_FACTOR 4294.967295
	
	class AD9850{
		 public:
			AD9850(int givenW_CLK, int givenFQ_UD, int givenDATA, int givenRESET);
			void init();
			void doReset();
			void osc(long code);

			void powerDown();
		 private:
			int W_CLK;
			int FQ_UD;
			int DATA;
			int RESET;
                        void sendPulse(int pin);
	};

#endif
