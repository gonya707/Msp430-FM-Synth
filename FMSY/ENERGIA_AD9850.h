/*   Modified Library for Stellaris and MSP430 boards with Energia.
 *
 *    This is a modified library of my AD9850 library for several boards and devices. 
 *    Don't use it in other projects unless you know what are doing
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
