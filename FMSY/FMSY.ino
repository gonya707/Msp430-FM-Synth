#include "energia.h"
#include "ENERGIA_AD9850.h"
#include "freqCodes.h"

#define AD_W_CLK P2_0
#define AD_FQ_UD P2_1
#define AD_DATA P2_2
#define AD_RESET P2_3

#define SWITCH P2_4
#define JUMPER P2_5

AD9850 device(AD_W_CLK, AD_FQ_UD, AD_DATA, AD_RESET);

void setup(){
  // 31250 baud UART, no parity bit, 1 stop bit
  Serial.begin(31250);

  pinMode(AD_W_CLK, OUTPUT);
  pinMode(AD_FQ_UD, OUTPUT);
  pinMode(AD_DATA, OUTPUT);
  pinMode(AD_RESET, OUTPUT);

  pinMode(SWITCH, INPUT); 
  pinMode(JUMPER, INPUT); 
  
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  
  //Init the AD9850
  device.init();
  device.doReset();
  device.osc(0);

}

void loop(){
  unsigned long message, note, freq;
  signed long t = 0;
  unsigned short z, y, x;
  unsigned short i = 0;
  unsigned short on = 0, off = 0;
  boolean ascending = true;
  boolean flagON = false, flagOFF = false;

  while (true){

    if (Serial.available() > 0){
      digitalWrite( RED_LED, HIGH);
      message = Serial.read();
      if(flagON){

        on++;
        if (note != message){
          note = message;
          freq = code[note - 24];
        }
      }

      if(flagOFF){
        off++;
      }

      flagON = isNoteOn(message);
      flagOFF = isNoteOff(message);
    }
    else {
      digitalWrite( RED_LED, LOW);
    }

    if ( (on == off) && (digitalRead(JUMPER)) ){ 
      device.powerDown();

      //sync
      i = 0; 
      ascending = true;
    }
    else{
      x = analogRead(P1_2);
      z = analogRead(P1_3) / 4 + 1;
      y = analogRead(P1_4);

// 0 ~ z ~ 0
      if (ascending){
        i++;
        if (i >= z){
          ascending = false;
        }
      }
      else{
        i--;
        if (i <= 0){
          ascending = true;
        }
      }

// floats used, remove in next releases
      t = (float)(((float)i / (float)z) * 100000) * ((float)y / (float)1024);

      device.osc(freq + (long)t + x);
    }
  }
}

boolean isNoteOn(unsigned short m){
  return (m >= 0x90 && m <= 0x9F);
}

boolean isNoteOff (unsigned short m){
  return (m >= 0x80 && m <= 0x8F);
}


