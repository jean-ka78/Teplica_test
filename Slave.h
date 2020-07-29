/* 
   SimpleModbusSlaveV10 supports function 3, 6 и 16.
   serial ring buffer 64 bytes or 32 registers.
   function 3       58 bytes or 29 registers.
   function 16      54 bytes or 27 registers.
*/
// #include <SimpleModbusSlave.h>

// #include <SimpleModbusSlave_DUE.h>


//////////////////// Макроопределения портов и настройки программы  ///////////////////
// #define TxEnablePin  11	   // Tx/Rx пин RS485
// #define baud         115200  // скоростьобмена по последовательному интерфейсу. (UART)
// #define timeout      200  // Длительность ожидание ответа (таймаут modbus)
// #define polling      300   // скорость опроса по modbus
// #define retry_count  10    // количесво запросов modbus до ошибки и останова обмена
// #define Slave_ID     1     // Адрес Slave устройсва
// // #define LED1         13    // светодиод 1
// // #define LED2         9     // светодиод 2
// // const int  buttonPin = 3;     // номер входа, подключенный к кнопке
// // переменные
// // int buttonState = 0;         // переменная для хранения состояния кнопки


// #define TxEnablePin_3  0	   // Tx/Rx пин RS485
// #define baud_3         115200  // скоростьобмена по последовательному интерфейсу. (UART)
// #define timeout_3      200  // Длительность ожидание ответа (таймаут modbus)
// #define polling _3     300   // скорость опроса по modbus
// #define retry_count_3  10    // количесво запросов modbus до ошибки и останова обмена
// #define Slave_ID_3     10
// Modbus slave_3 (Slave_ID_3,3,TxEnablePin_3); // this is slave @1 and RS-485
// Modbus slave_1(1, 1, 11);
unsigned long tempus;
int8_t state = 0;


////////////////////////////////////////////////////////////
union float_0{
 float f;
 uint16_t u[2];
}s_data;

void io_poll_3(){
//  if (slave_data_3[93]!= VentTempStart)
// {
//   VentTempStart = slave_data_3[93];
  
// }

if (slave_data_3[98]!= heat)
{
  heat = slave_data_3[98];
  slave_data[45] = slave_data_3[98];
  Serial.println("heat:"+String(heat));
}


}

void io_poll() {
  
  
 
  // slave_data[98] = slave_1.getInCnt();
  // slave_data[99] = slave_1.getOutCnt();
  // slave_data[100] = slave_1.getErrCnt();
  slave_data[0] = reg[5];
  slave_data_3[0] = reg[5];
  slave_data[1] = reg[4];
  slave_data_3[1] = reg[4];
  slave_data[2] = reg[11];
  slave_data_3[2] = reg[11];
  slave_data[3] = reg[10];
  slave_data_3[3]= reg[10];
  slave_data[4] = reg[17];
  slave_data_3[4] = reg[17];
  slave_data[5] = reg[16];
  slave_data_3[5] = reg[16];
  slave_data[6] = reg[23];
  slave_data_3[6] = reg[23];
  slave_data[7] = reg[22];
  slave_data_3[7] = reg[22];
  slave_data[8] = reg[29];
  slave_data_3[8] = reg[29];
  slave_data[9] = reg[28];
  slave_data_3[9] = reg[28];
  s_data.f = Temp_in;
  // Serial.println(Temp_in);
  // Serial.println(slave_data[10]);
  slave_data[10] = s_data.u[0];
  slave_data_3[10] = s_data.u[0];
  slave_data[11] = s_data.u[1];
  slave_data_3[11] = s_data.u[1];
  s_data.f = Humid;
  slave_data[12] = s_data.u[0];
  slave_data_3[12] = s_data.u[0];
  slave_data[13] = s_data.u[1];
  slave_data_3[13] = s_data.u[1];
  s_data.f = NH3;
  slave_data[14] = s_data.u[0];
  slave_data_3[14] = s_data.u[0];
  slave_data[15] = s_data.u[1];
  slave_data_3[15] = s_data.u[1];
  s_data.f = Tmax;
  // slave_data[14] = s_data.u[0];
  slave_data_3[16] = s_data.u[0];
  // slave_data[15] = s_data.u[1];
  slave_data_3[17] = s_data.u[1];
   s_data.f = Tmin;
  // slave_data[14] = s_data.u[0];
  slave_data_3[18] = s_data.u[0];
  // slave_data[15] = s_data.u[1];
  slave_data_3[19] = s_data.u[1];
   s_data.f = Tmax_i;
  // slave_data[14] = s_data.u[0];
  slave_data_3[20] = s_data.u[0];
  // slave_data[15] = s_data.u[1];
  slave_data_3[21] = s_data.u[1];
   s_data.f = Tmin_i;
  // slave_data[14] = s_data.u[0];
  slave_data_3[22] = s_data.u[0];
  // slave_data[15] = s_data.u[1];
  slave_data_3[23] = s_data.u[1];
//   button_esp = slave_data[9];
// if (slave_data[9]!=0)
// {
//    Serial.println("button: "+String(slave_data[9]));
// }
button_esp = slave_data[10];
// Serial.print("data20: "+String(slave_data[20]));
temp_on = slave_data[20];
temp_off = slave_data[21];
time_on = slave_data[22];


s_data.u[0] = slave_data[30];
s_data.u[1] = slave_data[31];
U_Temp[0] = s_data.f;
s_data.u[0] = slave_data[32];
s_data.u[1] = slave_data[33];
U_Temp[1] = s_data.f;
s_data.u[0] = slave_data[34];
s_data.u[1] = slave_data[35];
U_Temp[2] = s_data.f;
s_data.u[0] = slave_data[36];
s_data.u[1] = slave_data[37];
U_Temp[3] = s_data.f;



// io_poll_3();
}

void slave_setup()
{
//////////////////


////////////////
    //////////
     slave_1.begin( 115200 );
    //  slave_3.begin( 115200 ); // baud-rate at 19200
    //  tempus = millis() + 100; //Guarda el tiempo actual + 100ms
  //    /////////
 
  //  modbus_configure(&Serial1, baud, SERIAL_8N1, Slave_ID, TxEnablePin, sizeof(slave_data)/sizeof(slave_data[0]), slave_data);
  //  modbus_configure(&Serial1, baud, Slave_ID, TxEnablePin, sizeof(slave_data)/sizeof(slave_data[0]), slave_data);
  //  modbus_configure(&Serial3, baud_3, Slave_ID_3, TxEnablePin_3, sizeof(slave_data_3)/sizeof(slave_data_3[0]), slave_data_3);

  //  modbus_update_comms(baud, SERIAL_8N1, Slave_ID);  
  //  modbus_update_comms(baud, Slave_ID);  
  //  modbus_update_comms(baud_3, Slave_ID_3);  
}// конец void setup()

void slave_loop()
{

slave_1.poll(slave_data, sizeof(slave_data)/sizeof(slave_data[0]));
// slave_3.poll(slave_data_3, sizeof(slave_data_3)/sizeof(slave_data_3[0]));


  
  // Serial.print("in:"+String(slave_3.getInCnt()));
  // Serial.print(" out:"+String(slave_3.getOutCnt()));
  // Serial.println(" Err:"+String(slave_3.getErrCnt()));
 

  // int8_t state_err = modbus_update(); // запуск обмена по Modbus

  
}// конец void loop()
