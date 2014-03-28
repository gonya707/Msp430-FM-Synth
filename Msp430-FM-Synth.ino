#include "energia.h"
#include "ENERGIA_AD9850.h"
#include "freqCodes.h"

AD9850 device(P2_0, P2_1, P2_2, P2_3);

void setup(){
  // put your setup code here, to run once:
  Serial.begin(31250);

  pinMode(P2_0, OUTPUT);
  pinMode(P2_1, OUTPUT);
  pinMode(P2_2, OUTPUT);
  pinMode(P2_3, OUTPUT);
  
  pinMode(RED_LED, OUTPUT);
  digitalWrite( RED_LED, LOW);
  
  device.init();
  device.doReset();
  device.osc(0);
  
}

void loop(){
  // put your main code here, to run repeatedly:
  
        unsigned long message;
        unsigned long note;
        unsigned short z, y;
        long freq;
        boolean ascending = true;
        
        int on = 0, off = 0;
        int flagON = 0, flagOFF = 0;
        unsigned short i = 0;
        long t = 0;
        
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
              
                  flagON = (message >= 0x90 && message <= 0x9F);
                  flagOFF = (message >= 0x80 && message <= 0x8F);
              }
              else {
                digitalWrite( RED_LED, LOW);
              }
              
              if (on == off){ //quitar comentarios cuando este listo
                  //device.powerDown();
                  
                  //sync
                  //i = 0; 
                  //ascending = true;
              }
              else{
                  // 1 ~ 1024
                  z = analogRead(P1_3) + 1;
                  // 1 ~ 1024
                  y = 4*analogRead(P1_4) + 1;
                  
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
                  
                  // numero entre -4096 y +4096
                  t = ((i * 8192) / z) - 4096;
                  
                
                  // ogiginal AD9850_Osc(freq + y*sin(t), 0);
                  device.osc(freq + (t * (y-1) *4096) / 4096 / 4096);
                  
                  
                  
              }
        }
}



