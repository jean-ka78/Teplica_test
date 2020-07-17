#include "U8glib.h"
//#include "rus10x20.h"// подключаем нужный шрифт
#include "rus6x10.h"
//#include <DS3232RTC.h>  
//#include "encoder.h"   

U8GLIB_ST7920_128X64_1X u8g(LCD_A, LCD_B, LCD_C);
// U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    u8g.print(':');
    if(digits < 10)
        u8g.print('0');
    u8g.print(digits);
    
}
void Digits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    //u8g.print(':');
    if(digits < 10)
        u8g.print('0');
    u8g.print(digits);
    
}
void u8g_prepare(void) {
 // u8g.setFont(u8g_font_6x10);
 // analogWrite (5,60);
  u8g.setFont(rus6x10);
 // u8g.setFontRefHeightExtendedText();
 // u8g.setDefaultForegroundColor();
 // u8g.setFontPosTop();
}
void Delay(void) {
  // graphic commands to redraw the complete screen should be placed here  
  //u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 22, "Delay Light !");
  u8g.setPrintPos( 0, 35); 
  u8g.print(String(DELAY_Backlight)+"sec");
  //u8g.print('sec');
  //u8g.drawStr( 18, 35, "sec");
}
void sPoliv(){
   u8g.drawStr( 0, 8, "Настройка полива"); 
}
void sWindow(){
  u8g.drawStr( 0, 8, "Настройка окон"); 
  u8g.drawStr( 0, 20, "Моторы");
  u8g.setPrintPos( 16, 30); u8g.print(VentTime);
  u8g.drawStr( 40, 20, "Т откр");
  u8g.setPrintPos( 45, 30); u8g.print(VentTempStart);
  u8g.drawStr( 80, 20, "Т закр");
  u8g.setPrintPos( 85, 30); u8g.print(VentTempStop);
}

void MainScreen() {
 //Serial.println("LCD_Start");
  //analogWrite (5,60);
  //u8g.setFont(u8g_font_unifont);
  //u8g.setFont(rus6x10);
  //u8g.setFont(u8g_font_osb21);
 u8g.drawStr( 0, 8, "Влаж:"); 
  u8g.setPrintPos( 35, 8); 
  u8g.print(String(Humid1)+"%"); //u8g.drawStr("%");
  //u8g.drawStr(35, 8, "String(Humid1)"+"%")
  //u8g.drawStr( 49, 8, "%");
  u8g.drawStr( 0, 18, "Свет:"); 
  u8g.setPrintPos( 35, 18); u8g.print(String(lux)); //u8g.drawStr("%");
  //u8g.drawStr( 49, 18, "Lx");
  u8g.drawStr( 0, 30, "Т Внутри");
  u8g.setPrintPos( 0, 40); 
  u8g.print(String(Temp_in)+"˚C");
  //u8g.setPrintPos( 0, 50); u8g.print(WindowsValue);
  //u8g.drawStr( 0, 50, WindowsValue);
  u8g.drawStr( 0, 50, "Моторы");
    u8g.setPrintPos( 16, 60); u8g.print(VentTime);
      u8g.drawStr( 40, 50, "Т мин");
   u8g.setPrintPos( 45, 60); u8g.print(Tmin_i);
  u8g.drawStr( 80, 50, "Т макс");
  u8g.setPrintPos( 85, 60); u8g.print(Tmax_i);
  //u8g.drawStr( 30, 40, "C");
  u8g.drawStr( 70, 30, "Т Снаружи");
  u8g.setPrintPos( 70, 40); 
  u8g.print(String(Temp_out)+"˚C");
  //u8g.drawStr( 100, 40, "C");
  u8g.setPrintPos( 70, 17); Digits(dt.hour); 
  u8g.setPrintPos( 81, 17); printDigits(dt.minute); 
  u8g.setPrintPos( 98, 17); printDigits(dt.second);
  u8g.setPrintPos( 70, 8); Digits(dt.day); 
  u8g.setPrintPos( 81, 8); printDigits(dt.month); 
  u8g.setPrintPos( 98, 8); printDigits(dt.year); 
 }

 
 void Menu(void) {
    u8g_prepare();
  // long newPosition = enc.read() >> 2;  
  int e=enc.read();
  switch(m) {
    case 0: 
   // enc1.tick();
          MainScreen();
          if (button.pressed()){ analogWrite (5,60);m=10;Serial.println("Click"); msBacklight=ms; msSM=ms;}
        //  if (newPosition > oldPosition){Serial.println("right");
          if (e==encRIGHT){Serial.println("right");
            m++;
      if ( m >= 3 )
        m = 0;
        msBacklight=ms;
        msSM=ms;
         analogWrite (5,60);
        }
          if (e==encLEFT){ analogWrite (5,60);Serial.println("left");
      if ( m == 0 )
        m = 3;
      m--;
       msBacklight=ms;
       msSM=ms;
      //menu_redraw_required = 1;
       } 
         // msBacklight=ms;
          break;
          case 10:
        //  enc1.tick();
          Delay();
     
          if (e==encRIGHT){DELAY_Backlight++; Serial.println(DELAY_Backlight); analogWrite (5,60);}
          if (e==encLEFT){ analogWrite (5,60);if (DELAY_Backlight!=0){DELAY_Backlight--; Serial.println(DELAY_Backlight);} } 
          if (button.pressed()){ analogWrite (5,60);m=0; 
          EEPROM.write(34,DELAY_Backlight);
          Serial.println("запись значения");}
          msBacklight=ms;
          msSM=ms;
          
          break;
    case 1: 
    //enc1.tick();
    sPoliv();
     if (button.pressed()){ analogWrite (5,60);u8g.drawBox(16, 30, 20, 30);Serial.println("Click");}
     if (e==encRIGHT){ analogWrite (5,60); Serial.println("right"); m++;
     if ( m >= 3 ) m = 0; msBacklight=ms; msSM=ms;}
     if (e==encLEFT){ analogWrite (5,60);Serial.println("left");
     if ( m == 0 ) m = 3; m--; msBacklight=ms; msSM=ms;} 
   
     break;
    case 2:
     sWindow();
     if (button.pressed()){ analogWrite (5,60);m=0; EEPROM.write(31, VentTime); Serial.println("запись значения");}
     if (e==encRIGHT){ analogWrite (5,60); VentTime++; msBacklight=ms; msSM=ms; Serial.println(VentTime);}
     if (e==encLEFT){ analogWrite (5,60);if (VentTime!=0) {VentTime--; msBacklight=ms; msSM=ms; Serial.println(VentTime);}} 
     break;
      }
}//Menu()



void picture_loop(){
   u8g.firstPage();  
     do {
       
      //enc1.tick(); 
    Menu();
    //ClearScreen();
  } while ( u8g.nextPage() );
  }

void ClearScreen (void) { // функция очистки экрана
  u8g.firstPage();
  do {
  } while ( u8g.nextPage() );
}
