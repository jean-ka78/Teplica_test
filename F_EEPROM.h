#include <EEPROM.h>         
// #include "EEPROMAnything.h" // http://playground.arduino.cc/Code/EEPROMWriteAnything

// Функция чтения данных из Энергонезовисимой памяти EEPROM
void EEPROM_READ()
{
  Serial.println("EEPROM_READ_Start");
  
  int addr=0; // Номер байта EEPROM
  //EEPROM.begin(512);
// Флаги адреса с 0 по 19
  flag_AutoManual = EEPROM.read(addr);   // Адрес 0
//  flag_TableStop = EEPROM.read(addr+1);  // Адрес 1

// Уставки констант с 20 по 39
  addr = 20;
  Delta = EEPROM.read(addr);             // Адрес 20
  AlarmTempStart = EEPROM.read(addr+4);  // Адрес 24 
  AlarmTempStop = EEPROM.read(addr+8);   // Адрес 28
  VentTempStart = EEPROM.read(29);
  VentTempStop = EEPROM.read(30);
  VentTime = EEPROM.read(31);
  
  // EEPROM.write(29, VentTempStart);
  // EEPROM.write(30, VentTempStop);
  // EEPROM.write(31, VentTime);
   //  Адрес 29
  // if (EEPROM.read(29)>= 10 && EEPROM.read(29)<=40)
  // {
  //    VentTempStart = EEPROM.read(29);
  // }
  // else
  // {
  //    EEPROM.write(29, 30);
  // }
  
  // if ( EEPROM.read(30)>=10 && EEPROM.read(30)<=40)
  // {
  //   VentTempStop = EEPROM.read(30);
  // }
  // else
  // {
  //   EEPROM.write(30, 25);
  // }
  
  //   if (EEPROM.read(31)>=0 && EEPROM.read(31)<=180)
  //   {
  //     VentTime = EEPROM.read(31); // 31 
  //   }
  //   else
  //   {
  //     EEPROM.write(31, 15);
  //   }
    

  
  //Tmax = EEPROM.read(32);//32
  // Tmin = EEPROM.read(33);//33
  DELAY_Backlight = EEPROM.read(34);//34

  

//EEPROM.write(32, Tmax);
// EEPROM.write(33, Tmin);
// Уставки температуры c 100 по 199
  // addr = 100;
  // for (int i=0; i < 4; i++)
  // {EEPROM_readAnything(addr+i*10, TempTuning[i]);}  
/*  
  TempTuning[0] // Адрес 100
  TempTuning[1] // Адрес 110
  TempTuning[2] // Адрес 120
  TempTuning[3] // Адрес 130
*/    
// Уставки времени c 200 по 399
  // addr = 200;
  // for (int i=0; i < 4; i++)
  // {EEPROM_readAnything(addr+i*10, TimerTuning[i]);} 
/*  
  TimerTuning[0] // Адрес 200
  TimerTuning[1] // Адрес 210
  TimerTuning[2] // Адрес 220
  TimerTuning[3] // Адрес 230
*/     
  Serial.println("VentTempStart:"+String(VentTempStart));
  Serial.println("VentTempStop:"+String(VentTempStop));
  Serial.println("VentTime:"+String(VentTime));
  EEPROM.end(); 

  Serial.println("EEPROM_READ_Stop");
}
/*
bool Recorded;  // Служит для перезаписи заводских настроек (Factory Settings)
  int addr = 400;   // Начальный адрес EEPROM
  int a[7];       // Массив адресов EEPROM. Хранятся адреса переменных.

  // Перечесление для удобного доступа к адресу переменной в EEPROM.
  // Сами адреса переменных хранятся в массиве a объявленном выше.  
  enum n_addr {    
  a_Recorded,

  a_ModeAuto,
  a_RLL,  
  a_Ts,
  a_D,
  a_RegulatorType,
  a_DELAY_Backlight
  };

// Функция служит для автоматического заполнения Массива адресов EEPROM.
void setupAddrEEPROM(){
  a[a_Recorded]=addr;             addr+=sizeof(Recorded); 
  a[a_ModeAuto]=addr;             addr+=sizeof(ModeAuto);
  a[a_RLL]=addr;                  addr+=sizeof(RLL); 
  a[a_Ts]=addr;                   addr+=sizeof(Ts);
  a[a_D]=addr;                    addr+=sizeof(D);
//  a[a_RegulatorType]=addr;        addr+=sizeof(RegulatorType); 
  a[a_DELAY_Backlight]=addr;      addr+=sizeof(DELAY_Backlight); 

  // Выводит таблицу:
  //             / адрес в EEPROM         /       ИМЯ переменной             / Размер занимаемый переменной в байтах /
  Serial.println("");
  Serial.print(a[n_addr::a_Recorded]);        Serial.print(" Recorded ");         Serial.println(sizeof(Recorded));
  Serial.print(a[n_addr::a_ModeAuto]);        Serial.print(" ModeAuto ");         Serial.println(sizeof(ModeAuto));
  Serial.print(a[n_addr::a_RLL]);             Serial.print(" RLL ");              Serial.println(sizeof(RLL));
  Serial.print(a[n_addr::a_Ts]);              Serial.print(" Ts ");               Serial.println(sizeof(Ts));  
  Serial.print(a[n_addr::a_D]);               Serial.print(" D ");                Serial.println(sizeof(D)); 
//  Serial.print(a[n_addr::a_RegulatorType]);   Serial.print(" RegulatorType ");    Serial.println(sizeof(RegulatorType));
  Serial.print(a[n_addr::a_DELAY_Backlight]); Serial.print(" DELAY_Backlight ");  Serial.println(sizeof(DELAY_Backlight));   
  Serial.println(addr);
  
} 

// Читаем все сохраненные настройки из EEPROM
void ReadEEPROM()
{
  EEPROM_readAnything(a[a_ModeAuto], ModeAuto);
  EEPROM_readAnything(a[a_RLL], RLL);
//  EEPROM_readAnything(a[a_RegulatorType], RegulatorType); 
  EEPROM_readAnything(a[a_DELAY_Backlight], DELAY_Backlight); 
  EEPROM.get(a[a_Ts],  Ts);
  EEPROM.get(a[a_D],   D);
}

void setupEEPROM(){
  Serial.print("EEPROM Begin!");
  setupAddrEEPROM();
  
  EEPROM_readAnything(a[a_Recorded], Recorded); // Прочитаем из EEPROM состониие переменной Recorded
  
  // Если в переменной Recorded ненаходится слова true то запишем в EEPROM базовые настройки
  if (Recorded == false){
    Recorded=true;
    EEPROM_writeAnything(a[a_Recorded], Recorded);
//    EEPROM_writeAnything(a[a_RegulatorType], RegulatorType);
    EEPROM_writeAnything(a[a_DELAY_Backlight], DELAY_Backlight);
    EEPROM_writeAnything(a[a_ModeAuto], ModeAuto);
    EEPROM_writeAnything(a[a_RLL], RLL);
    EEPROM.put(a[a_Ts],  Ts);
    EEPROM.put(a[a_D],   D);
  }

  ReadEEPROM();
  Serial.println("  Done!");   
}
*/