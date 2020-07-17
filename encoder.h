//#include "GyverEncoder.h"
#include <iarduino_Encoder_tmr.h>             //  Подключаем библиотеку iarduino_Encoder_tmr для работы с энкодерами через аппаратный таймер

#include <Button.h>
//#include <Encoder.h>

Button button(SW);
iarduino_Encoder_tmr enc(CLK,DT);


void RankDirection(bool Direction){
  static int RankIndex=0;
  if (Direction) {RankIndex++; if (RankIndex > 2) {RankIndex=2;}}
  else           {RankIndex--; if (RankIndex < 0) {RankIndex=0;}}
  
  switch(RankIndex){
    case 0:
      Rank=0.1;
    break;
    case 1:
      Rank=1.0;
    break;
    case 2:
      Rank=10.0;
    break;
  }
}

void checkEncoder(){
     
  if (ms - msBacklight > (DELAY_Backlight*1000) && DELAY_Backlight!=0){ // Если долго не нажимали не одну кнопку, то экран состояния
     analogWrite (5,0);
  }
    
  if (ms - msSM > DELAY_StartMenu){
    m = 0; 
   }
  }
  
