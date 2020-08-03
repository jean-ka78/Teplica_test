  /**************************************************************

                            Settings
                            Настройки`

 **************************************************************/
uint16_t regs_16P[16]; //Массив 16Р
uint16_t regs_16P_in[16];//Массив 16Р
uint16_t regs_16P_read[50];//Массив 16Р
uint16_t reg[29]; // Массив 8А
uint16_t regs_8AC[16]; // Массив 8АС
uint16_t slave_data[100]; // Массив Панели
// u16 slave_data[100];
uint16_t slave_data_3[250]; //Массив ESP
uint16_t regs_PLK[100]; //Массив ПЛК 


/*
   База - GPIO
*/
// пин к которому ципляем датчик
#define DHTPIN A7           // D7 и 13(GPIO) это одно и то же. 
#define ONE_WIRE_BUS_IN_1 A11 // PIN куда подключена шина ONE_WIRE (DS18B20)
#define ONE_WIRE_BUS_IN_2 A12 // PIN куда подключена шина ONE_WIRE (DS18B20)
#define ONE_WIRE_BUS_IN_3 A13 // PIN куда подключена шина ONE_WIRE (DS18B20)
#define ONE_WIRE_BUS_IN_4 A14 // PIN куда подключена шина ONE_WIRE (DS18B20)
#define ONE_WIRE_BUS_OUT A15 // PIN куда подключена шина ONE_WIRE (DS18B20)


// encoder------------
#define CLK A0
#define DT A1
#define SW A10
// encoder end--------
//#define ONE_WIRE_BUS A12
//#define GPIO_B_Select A10
// LCD 128x64 ---------------
#define LCD_A 52
#define LCD_B 51
#define LCD_C 4
// LCD 128x64 end ---------------
// pin number > 1 for RS-485
#define DERE 12
// pin number > 1 for RS-485 end
#define RELAY1PIN 42  // PIN реле 1 Теплый пол
#define RELAY2PIN 44  // PIN реле 2 Аварийный нанреватель
#define RELAY3PIN 40  // PIN реле 3 Открытия Окон проветривания
#define RELAY4PIN 41  // Пин реле 4 Закрытия Окон Проветривания
#define RELAY_ZONA_1_PIN 30 // Пин реле обогрева Зона 1
#define RELAY_ZONA_2_PIN 31 // Пин реле обогрева Зона 1
#define RELAY_ZONA_3_PIN 32 // Пин реле обогрева Зона 1
#define RELAY_ZONA_4_PIN 33 // Пин реле обогрева Зона 1
#define PIN_SVET 34
#define PolivPin 35
bool relay_Zona[4]; 
bool relay_Zona2 = LOW;
bool relay_Zona3 = LOW;
bool relay_Zona4 = LOW;
bool flag_Zona[4];
bool relay_svet = LOW;
bool relay_poliv = LOW;
bool flag_heat = false;

//#define ENC_REVERSE 0      // 1 - инвертировать направление энкодера, 0 - нет


////////////////////////////////////////////////////
//            Данные хранятся в EEPROM            //

// Данные об Уставках
// Массив уставок температуры
int16_t TempTuning[4]; //= {10, 15, 20, 25};
// Массив уставок температуры
uint32_t TimerTuning[4]; //= {36000, 43200, 54000, 82800};
uint32_t ms; //Время начало работі
uint32_t msBL;
uint32_t msBackLight;
uint32_t msSM;
uint8_t m = 0;
// Гистерезис Дельта температуры
int8_t Delta; //=2;
// Настройки Аварийного нагревателя
float AlarmTempStart; //Температура Включения
float AlarmTempStop;  //Температура Выключения
int32_t VentTempStart = 25; //Температура открытия окон

int32_t VentTempStop = 24; //Температура закрытия окон
uint8_t VentTime_t; //Время открытия окон с Блинк
float VentTempStop_t; //Температура закрытия окон с Блинк
float VentTempStart_t; // Температура открытия окон с Блинк
float U_Temp_u;
float U_Temp_u1;
float U_Temp_u2;
float U_Temp_u3;
int32_t temp_on; //Температура открытия окон с Панели
int32_t temp_off; //Температура закрытия окон с Панели
int32_t VentTime = 5;    //Время открытия
int8_t time_on; // время закрытия окон с Панели
bool heat_t;
#define DELAY_StartMenu 10000UL // время блокировки кнопок при бездействии
// Флаги
uint8_t flag_AutoManual;
uint8_t flag_TableStop = true;
bool isFirstConnect  = true;
bool close = true;
bool open = true;
 bool run = true;
//            Данные хранятся в EEPROM            //
////////////////////////////////////////////////////

// Данные от датчиков
float Temp1;  // Температура от датчика 1
float Temp2;  // Температура от датчика 2
float Temp3;  // Температура от датчика 3
float Temp4;  // Температура от датчика 4

float Temp[8];
float Temp_8A[8];
float Temp_out;
float U_Temp1 = 18; // Уставка температуры зона 1
float U_Temp2 = 18; // Уставка температуры зона 2
float U_Temp3 = 18; // Уставка температуры зона 3
float U_Temp4 = 18; // Уставка температуры зона 4
float U_Temp[4];
float NH3 = 0;
int16_t CO2 = 0;

//float Humid1;
int8_t Humid1; // Влажность от датчика 1
float Humid;
uint16_t lux; 
#define TEMP_SUM 2 // Количество датчиков
//int8_t TempDS18B20[TEMP_SUM];
float TempDS18B20[TEMP_SUM];
// 0 Датчик в помещении
// 1 Датчик в полу

float Tmin = 50.00;
float Tmax = -50.00;
float Tmax_i = -50.00;
float Tmin_i =  50.00;
float Tout;
float Temp_in;
float Tin;
float  temp_ust_esp;
int  button_esp;
long oldPosition  = -999;
// Флаги выходных устройств
boolean heat = false;
boolean heat_esp = false;
// boolean svet = false;
boolean flag_RELAY1 = false;
boolean flag_A_logicRegulatorT = false;
boolean flag_RELAY2_Alarm = false;
boolean flag_RELAY3_Vent = false;
boolean flag_RELAY4_Vent = false;
boolean flag_wind = false;
boolean flag = HIGH;
int i = 0;
bool s1_timeout = false;
bool s2_timeout = false;
unsigned long new_time = 0;

//timezone Временная зона
//full list of supported timezones could be found here
//Полный список поддерживаемых часовых поясов можно найти здесь
//https://www.mkyong.com/java/java-display-list-of-timezone-with-gmt/
// char TimeZone[] = "Europe/Kiev";
uint8_t hour_t;
uint8_t minute_t;
uint8_t sec_t;
// Переменные для настройки параметров
long TimerInput;  // Тут хранятся данные от TimerInput (Ввод времени)
int StepControl; // Тут хранятся данные от StepControl (Шаговые кнопки)
boolean Button1; // Тут храниться данные от Нажата ли кнопка
unsigned long previousMillis = 0;
int Tuning; // служит для настройки всех уставок через StepControl (Шаговые кнопки)
long TunTime; // служит для настройки всех уставок через TimerInput (Ввод времени)

/*
   База - Таймеров
*/
int timerTable_ID; // Номер таймера Таблица
int timerTimeString_ID; // Номер таймера TimeString
int ID_timer_RTS; // Номер Таймера для установки времени

#define TintervalSensor1 2000L


// Переменные для таймера на millis();
// uint32_t ms;            // Хранит время с начала работы МК

// Хранят время с последнего события
uint32_t msTempIn1;     // Служит для опроса датчика температуры с заданным интевалом
uint32_t msLCD1;        // Служит для обновления информации на LSD дисплее с заданной частотой
// uint32_t msBL;          // Служит для блокировки кнопок по истечению заданного промежутка времени
uint32_t msBacklight;   // Служит для отключения подсветки экрана по истечению заданного промежутка времени
// uint8_t m = 0;
#define DELAY_TempIn1 2000UL  // Частота опроса датчика температуры
#define DELAY_LCD1 200UL      // Частота обновления информации на LCD экране

#define DELAY_ButtonLock 30000UL // время блокировки кнопок при бездействии
uint32_t DELAY_Backlight = 10000UL; // время отключения подсветки экрана при бездействии (Factory Settings)

//      База переменных
// Флаг ошибки. Если true то ошибка, если false то все хорошо
bool Error = false;
//  int Enc;
// Данные от датчика температуры
float TempIn1;

// Переменные для терморегулятора
float Ts = 20.0;            // Уставка терморегулятора                            (Factory Settings)
float D =  0.5;             // Дельта (Гистерезес) терморегулятора                (Factory Settings)
float Rank = 0.1;           // Ранг(шаг) изменения переменных Ts и D
bool StateRelay1 = false;   // Состояние выхода Реле 1 (Выход терморегулятора)
bool ModeAuto = false;      // Режим рулятора (Автоматический/Ручной)(true/false) (Factory Settings)
bool RLL = HIGH;            // Relay Logic Level (Уровень Логики Реле)            (Factory Settings)
bool Buttonlock = true;     // Блокировка кнопок
uint16_t statistics[31]; //масив статистики
