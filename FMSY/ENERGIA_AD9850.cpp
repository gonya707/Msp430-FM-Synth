#include "Energia.h"
#include "ENERGIA_AD9850.h"

//Constructor for the class AD9850
AD9850::AD9850(int givenW_CLK, int givenFQ_UD, int givenDATA, int givenRESET){
	W_CLK = givenW_CLK;
   	FQ_UD= givenFQ_UD;
   	DATA= givenDATA;
   	RESET = givenRESET;
}

void AD9850::init(){
	digitalWrite(W_CLK, LOW);
	digitalWrite(FQ_UD, LOW);
	digitalWrite(DATA, LOW);
	digitalWrite(RESET, LOW);
}

/* Reset operation for the AD9850. This function must be called before using AD9850_Osc
 * first time in the execution (check page 12 on datasheet)
 * */
void AD9850::doReset(){
	sendPulse(W_CLK);
        sendPulse(RESET);
        sendPulse(FQ_UD);
	osc(0);
}

/* Sets the DDS sine and square oscillator to the "frequency" code

*/
void AD9850::osc(long code){
	long y = abs(code);

	int i;
	//Frequency 32-bit word
	for (i = 0; i < 32; i++){
	        digitalWrite(DATA, (y >> i) & 0x01);
		sendPulse(W_CLK);
	}
	
	//control bit #1, control bit #2 and Power off, all to low
        digitalWrite(DATA, 0);
        sendPulse(W_CLK);
        sendPulse(W_CLK);
        sendPulse(W_CLK);
	
	//phase 5-bit word -> 0
	for (i=0;i<5;i++){
                sendPulse(W_CLK);
	}

        sendPulse(FQ_UD);
}

/* Enables power down mode. This method is used for a quick "all outputs" disable.
 * The effect is the same as AD9850_Osc(0,0), but it takes less clock cycles
 */
void AD9850::powerDown(){
	int i;
        sendPulse(FQ_UD);

	for (i=0;i<8;i++){
		digitalWrite(DATA, (0x04 >> i) & 0x01);
                sendPulse(W_CLK);
	}

        sendPulse(FQ_UD);
}


void AD9850::sendPulse(int pin){
	digitalWrite(pin, HIGH);
	digitalWrite(pin, LOW);
}


