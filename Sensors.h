/////////////////////////////////////////
//              DHT  Датчик №1        //

#include <SPI.h> // DHT работает по SPI
#include <DHT.h> // библиотека датчика

// Выбираем конкретный тип датчика
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE); //инициализируем датчик

void Sensor1()
{
  
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // или dht.readTemperature(true) для вывода по Фаренгейту
   
  if (isnan(h) || isnan(t)) {      // видно, что тут, проверяется полученно ли значение
   //Serial.println("Failed to read from DHT sensor!");
    return; //Прекращает вычисления в функции, то есть ждем когда следующий раз обратимся к функции Sensor
  }
  Humid1 = int(h);
  Temp1 = int(t);
// Serial.println(Humid1);
// Serial.println(Temp1);
  

}//Sensor1

//              DHT  Датчик №1        //
/////////////////////////////////////////
/////////////////////////////////////////
//       DS18B20  Датчики №2-3        //

// Подключаем библиотеки
#include <OneWire.h>
#include <DallasTemperature.h>
//#define ONE_WIRE_BUS D3 //PIN куда подключена шина ONE_WIRE (DS18B20)(Определено в  Settings.h)
#define TEMPERATURE_PRECISION 12 // Точность температуры
// #define TEMP_SUM 2 // Количество датчиков (Определено в  Settings.h)
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
// Настройка экземпляра oneWire для взаимодействия с любыми устройствами OneWire (а не только с температурными микросхемами Maxim/Dallas)
OneWire oneWire_in_1(ONE_WIRE_BUS_IN_1);
OneWire oneWire_in_2(ONE_WIRE_BUS_IN_2);
OneWire oneWire_in_3(ONE_WIRE_BUS_IN_3);
OneWire oneWire_in_4(ONE_WIRE_BUS_IN_4);
OneWire oneWire_out(ONE_WIRE_BUS_OUT);
//OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
// Передаем нашу ссылку oneWire на Даллас Температуру.
DallasTemperature sensors_in_1(&oneWire_in_1);
DallasTemperature sensors_in_2(&oneWire_in_2);
DallasTemperature sensors_in_3(&oneWire_in_3);
DallasTemperature sensors_in_4(&oneWire_in_4);
DallasTemperature sensors_out(&oneWire_out);
//DallasTemperature sensors(&oneWire);

// arrays to hold device addresses
// массивы для хранения адресов устройств
//DeviceAddress Thermometer[TEMP_SUM];
//DeviceAddress insideThermometer, outsideThermometer;
//DeviceAddress sensor1, sensor2, sensor3, sensor4, sensor5;
// function to print a device address
 const int    SAMPLE_NUMBER      = 15;
  DeviceAddress sensor1   = { 0x28, 0xF5, 0x75, 0xC9, 0x2F, 0x14, 0x01, 0xD0 };
  DeviceAddress sensor2   = { 0x28, 0xAA, 0xF0, 0x86, 0x13, 0x13, 0x02, 0x50 };
  DeviceAddress sensor3   = { 0x28, 0xFF, 0x49, 0xA1, 0x81, 0x16, 0x05, 0xC4 };
// int thermistorPin = A3;  // Вход АЦП, выход делителя напряжения
int thermistorPin1 = A3;// Вход АЦП, выход делителя напряжения
int thermistorPin2 = A4;
int thermistorPin3 = A5;
int thermistorPin4 = A6;
int thermistorPin5 = A7;

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

double printTemperature_in_1()
{
  float adcTemp  = 0;            // Хранит среднее значение напряжения
  float adcSamples[SAMPLE_NUMBER];  // Массив для хранения отдельных результатов

for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    unsigned long real_time = millis();
    unsigned long old_time = 0;
    if (real_time - old_time>5)
    {
      old_time = real_time;
      // adcSamples[i] = sensors_in_1.getTempC(deviceAddress);  // прочитать значение на выводе и сохранить
       adcSamples[i] = sensors_in_1.getTempCByIndex(0);
    }
  }

  /* Затем мы просто усредняем все эти выборки для "сглаживания" измерений. */
  for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    adcTemp += adcSamples[i];      // складываем все выборки . . .
  }
  adcTemp /= SAMPLE_NUMBER;        // . . . усредняем их с помощью деления

  float tempC = adcTemp;

  //tempC = sensors.getTempC(deviceAddress);
  // if(tempC == DEVICE_DISCONNECTED_C) 
  // {
  //   Serial.println("Error: Could not read temperature data");
  //   return;
  // }
  // Serial.print("Temp C: ");
  // Serial.println(tempC);
  return tempC; 
  //Serial.print(" Temp F: ");
  //Serial.print(DallasTemperature::toFahrenheit(tempC));
}
double printTemperature_in_2()
{
  float adcTemp  = 0;            // Хранит среднее значение напряжения
  float adcSamples[SAMPLE_NUMBER];  // Массив для хранения отдельных результатов

for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    unsigned long real_time = millis();
    unsigned long old_time = 0;
    if (real_time - old_time>5)
    {
      old_time = real_time;
      // adcSamples[i] = sensors_in_2.getTempC(deviceAddress);  // прочитать значение на выводе и сохранить
       adcSamples[i] = sensors_in_2.getTempCByIndex(0);
    }
  }

  /* Затем мы просто усредняем все эти выборки для "сглаживания" измерений. */
  for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    adcTemp += adcSamples[i];      // складываем все выборки . . .
  }
  adcTemp /= SAMPLE_NUMBER;        // . . . усредняем их с помощью деления

  float tempC = adcTemp;

  //tempC = sensors.getTempC(deviceAddress);
  // if(tempC == DEVICE_DISCONNECTED_C) 
  // {
  //   Serial.println("Error: Could not read temperature data");
  //   return;
  // }
  // Serial.print("Temp C: ");
  // Serial.println(tempC);
  return tempC; 
  //Serial.print(" Temp F: ");
  //Serial.print(DallasTemperature::toFahrenheit(tempC));
}

double printTemperature_in_3()
{
  float adcTemp  = 0;            // Хранит среднее значение напряжения
  float adcSamples[SAMPLE_NUMBER];  // Массив для хранения отдельных результатов

for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    unsigned long real_time = millis();
    unsigned long old_time = 0;
    if (real_time - old_time>5)
    {
      old_time = real_time;
      // adcSamples[i] = sensors_in_3.getTempC(deviceAddress);  // прочитать значение на выводе и сохранить
      adcSamples[i] = sensors_in_3.getTempCByIndex(0);
    }
  }

  /* Затем мы просто усредняем все эти выборки для "сглаживания" измерений. */
  for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    adcTemp += adcSamples[i];      // складываем все выборки . . .
  }
  adcTemp /= SAMPLE_NUMBER;        // . . . усредняем их с помощью деления

  float tempC = adcTemp;

  //tempC = sensors.getTempC(deviceAddress);
  // if(tempC == DEVICE_DISCONNECTED_C) 
  // {
  //   Serial.println("Error: Could not read temperature data");
  //   return;
  // }
  // Serial.print("Temp C: ");
  // Serial.println(tempC);
  return tempC; 
  //Serial.print(" Temp F: ");
  //Serial.print(DallasTemperature::toFahrenheit(tempC));
}
double printTemperature_in_4()
{
  float adcTemp  = 0;            // Хранит среднее значение напряжения
  float adcSamples[SAMPLE_NUMBER];  // Массив для хранения отдельных результатов

for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    unsigned long real_time = millis();
    unsigned long old_time = 0;
    if (real_time - old_time>5)
    {
      old_time = real_time;
       //adcSamples[i] = sensors_in_4.getTempC(deviceAddress);  // прочитать значение на выводе и сохранить
       adcSamples[i] = sensors_in_4.getTempCByIndex(0);
    }
  }

  /* Затем мы просто усредняем все эти выборки для "сглаживания" измерений. */
  for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    adcTemp += adcSamples[i];      // складываем все выборки . . .
  }
  adcTemp /= SAMPLE_NUMBER;        // . . . усредняем их с помощью деления

  float tempC = adcTemp;

  //tempC = sensors.getTempC(deviceAddress);
  // if(tempC == DEVICE_DISCONNECTED_C) 
  // {
  //   Serial.println("Error: Could not read temperature data");
  //   return;
  // }
  // Serial.print("Temp C: ");
  // Serial.println(tempC);
  return tempC; 
  //Serial.print(" Temp F: ");
  //Serial.print(DallasTemperature::toFahrenheit(tempC));
}
double printTemperature_out()
{
  float adcTemp  = 0;            // Хранит среднее значение напряжения
  float adcSamples[SAMPLE_NUMBER];  // Массив для хранения отдельных результатов

for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    unsigned long real_time = millis();
    unsigned long old_time = 0;
    if (real_time - old_time>5)
    {
      old_time = real_time;
       //adcSamples[i] = sensors_out.getTempC(deviceAddress);  // прочитать значение на выводе и сохранить
       adcSamples[i] = sensors_out.getTempCByIndex(0);
    }
  }

  /* Затем мы просто усредняем все эти выборки для "сглаживания" измерений. */
  for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    adcTemp += adcSamples[i];      // складываем все выборки . . .
  }
  adcTemp /= sizeof(adcSamples)/sizeof(adcSamples[0]);        // . . . усредняем их с помощью деления

  float tempC = adcTemp;

  //tempC = sensors.getTempC(deviceAddress);
  // if(tempC == DEVICE_DISCONNECTED_C) 
  // {
  //   Serial.println("Error: Could not read temperature data");
  //   return;
  // }
//   Serial.print("Temp C_out: ");
//   Serial.println(tempC);
  return tempC; 
  //Serial.print(" Temp F: ");
  //Serial.print(DallasTemperature::toFahrenheit(tempC));
}

void setSetupDS18B20()
{
  //sensors.begin();
  sensors_in_1.begin();
  sensors_in_2.begin();
  sensors_in_3.begin();
  sensors_in_4.begin();
  sensors_out.begin();
  sensors_in_1.setResolution(TEMPERATURE_PRECISION);
  sensors_in_2.setResolution(TEMPERATURE_PRECISION);
  sensors_in_3.setResolution(TEMPERATURE_PRECISION);
  sensors_in_4.setResolution(TEMPERATURE_PRECISION);
  sensors_out.setResolution(TEMPERATURE_PRECISION);
 }//setSetupDS18B20




double temp_s() {
  //const byte tempPin = A13;
  #define B 3950 // B-коэффициент
  #define SERIAL_R 9950 // сопротивление последовательного резистора, 102 кОм
  #define THERMISTOR_R 10000 // номинальное сопротивления термистора, 100 кОм
  #define NOMINAL_T 25 // номинальная температура (при которой TR = 100 кОм)
  float steinhart;
  int t;
  float tr;
  t = analogRead( thermistorPin2 );
  tr = 1023.0 / t - 1;
  tr = SERIAL_R / tr;
//  Serial.print("R=");
//  Serial.print(tr);
//  Serial.print(", t=");
  steinhart = tr / THERMISTOR_R; // (R/Ro)
  steinhart = log(steinhart); // ln(R/Ro)
  steinhart /= B; // 1/B * ln(R/Ro)
  steinhart += 1.0 / (NOMINAL_T + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart; // Invert
  steinhart -= 273.15;
//  Serial.print(steinhart);
//  Serial.print(", t=");
  return steinhart;
}

double readThermistor(int thermistorPin) 
{
  //int thermistorPin = A13;  // Вход АЦП, выход делителя напряжения
  const double BALANCE_RESISTOR   = 9950.0;
  const double MAX_ADC            = 1023.0;
  const double BETA               = 3977.0;
  const double ROOM_TEMP          = 298.15;   // комнатная температура в Кельвинах
  const double RESISTOR_ROOM_TEMP = 10000.0;
 // const int    SAMPLE_NUMBER      = 10;
  
  // переменные
  double rThermistor = 0;            // Хранит значение сопротивления термистора
  double tKelvin     = 0;            // Хранит рассчитанную температуру
  double tCelsius    = 0;            // Хранит температуру в градусах Цельсия
  double adcAverage  = 0;            // Хранит среднее значение напряжения
  int    adcSamples[SAMPLE_NUMBER];  // Массив для хранения отдельных результатов
                                     // измерений напряжения

  /* Рассчитать среднее сопротивление термистора:
     Как упоминалось выше, мы будем считывать значения АЦП несколько раз,
     чтобы получить массив выборок. Небольшая задержка используется для
     корректной работы функции analogRead. */
  
  for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    unsigned long real_time = millis();
    unsigned long old_time = 0;
    if (real_time - old_time>5)
    {
      old_time = real_time;
       adcSamples[i] = analogRead(thermistorPin);  // прочитать значение на выводе и сохранить
    }
  }

  /* Затем мы просто усредняем все эти выборки для "сглаживания" измерений. */
  for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    adcAverage += adcSamples[i];      // складываем все выборки . . .
  }
  adcAverage /= SAMPLE_NUMBER;        // . . . усредняем их с помощью деления

  /* Здесь мы рассчитываем сопротивление термистора, используя уравнение,
     описываемое в статье. */
  rThermistor = BALANCE_RESISTOR / ( (MAX_ADC / adcAverage) - 1);

  /* Здесь используется бета-уравнение, но оно отличается от того, что 
     описывалось в статье. Не беспокойтесь! Оно было перестроено, чтобы
     получить более "красивую" формулу. Попробуйте сами упростить уравнение,
     чтобы поупражняться в алгебре. Или просто используйте показанное здесь
     или то, что приведено в статье. В любом случае всё будет работать! */
  tKelvin = (BETA * ROOM_TEMP) / 
            (BETA + (ROOM_TEMP * log(rThermistor / RESISTOR_ROOM_TEMP)));

  /* Я буду использовать градусы Цельсия для отображения температуры.
     Я сделал это, чтобы увидеть типовую комнатную температуру, которая
     составляет 25 градусов Цельсия. */
  tCelsius = tKelvin - 273.15;  // преобразовать кельвины в цельсии

  return tCelsius;    // вернуть температуру в градусах Цельсия
}

void statistic(){//Статистика температуры
 Tout = Temp_out;
 Tin = Temp_in; 
 if (Temp_out == 0 || Tmin == 0) 
 {
   Tmin = 50.00;
   Tmax = -50.00;
  
 }
 if (Temp_in == 0 || Tmin_i == 0)
 {
   Tmax_i = -50.00;
   Tmin_i =  50.00;
 }
 
if (Tmax<Tout){
  Tmax=Tout;
 
   EEPROM.write(41, Tmax);
}
if (Tmin>Tout){
  Tmin=Tout;
 
    EEPROM.write(40, Tmin);
}
if (Tmin <=-50.0){
      Tmin = 50;
   }


if (Tmax_i<Tin){
  Tmax_i=Tin;
  EEPROM.write(43, Tmax_i);
}

if (dt.hour==0 && dt.minute ==1 && dt.second >=1 & dt.second <=5){ Tmax_i=Tin; Tmin_i=Tin;Tmax=Tout;Tmin=Tout;}

if (Tmin_i>Tin){
  Tmin_i=Tin;
     EEPROM.write(42, Tmin_i);
}
if (Tmin_i <= -50.00 || Tmin_i == 0){
      Tmin_i =  50;
     }
  EEPROM.end();

}
double Temp_in_sr()
{
  double absTemp_in = 0;
int count = 0;
  for (int i = 0; i < 4;i++) 
  {
     if (Temp[i]>= -40 & Temp[i] <= 50.00 & Temp[i] !=0)
     {
        absTemp_in += Temp[i];
        count ++;
     }
  }
     if (count > 0) {
    absTemp_in /= count;
  } 
  
  return absTemp_in;
}

void updateTemp()
{
  // sensors_in_1.requestTemperatures();
  // sensors_in_2.requestTemperatures();
  // sensors_in_3.requestTemperatures();
  // sensors_in_4.requestTemperatures();
  // sensors_out.requestTemperatures();
  
  for (int i = 0; i < sizeof(Temp)/sizeof(Temp[0]); i++)
  {
   Temp[i] = Temp_8A[i];
  }
   Temp_out = Temp_8A[4];
/////////////////////////////////////////////////////
// double DS;
// Temp[0] = printTemperature_in_1()-6;
// Temp[1] = readThermistor(thermistorPin2);
// Temp[2] = readThermistor(thermistorPin1);
// Temp[3] = readThermistor(thermistorPin2);
// Temp_out =  readThermistor(thermistorPin2);
 
  // if (Temp_out <= -50 || Temp_out >= 70.00)
  // {
  //   // Temp_out = 0;
  //     EEPROM.write(40, Tmin);
  //     EEPROM.write(41, Tmax);
  //     EEPROM.end();
  //     // Serial.print("Temp_out: "+String(Temp_out));
  // }
//Вычисление средей  температуры
Temp_in = Temp_in_sr();
//  
 statistic();
  //  Serial.print("Temp_out: "+String(Temp_out));
  //  Serial.println(" Temp: "+String(Temp_in));
}



//       DS18B20  Датчики №2-3        //
/////////////////////////////////////////


/////////////////////////////////////////
//        BH1750
#include <BH1750FVI.h>
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

void Light(){
 int32_t lux_t = 0;
 lux_t = LightSensor.GetLightIntensity();
 if (lux_t < 0)
 {
   lux = 0;
 }
 else 
 {
   if (lux_t > 54612)
   lux_t = 54612;

   lux = lux_t;
 }
//  Serial.println(" lux: "+String(lux_t));
  // return lux;
}
