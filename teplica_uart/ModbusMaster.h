#include <ModbusRtu.h>


// data array for modbus network sharing


uint8_t u8state; //!< machine state

uint8_t u8query; //!< pointer to message query
/**
 *  Modbus object declaration
 *  u8id : node id = 0 for master, = 1..247 for slave
 *  u8serno : serial port (use 0 for Serial)
 *  u8txenpin : 0 for RS-232 and USB-FTDI 
 *               or any pin number > 1 for RS-485
 */
Modbus master(0,2,DERE); // this is master and RS-232 or USB-FTDI via software serial
Modbus slave_1(1, 1, 11);
// Modbus slave_3(10, 3, 0);
/**
 * This is an structe which contains a query to an slave device
 */
uint8_t id_t = 3;
modbus_t telegram[3];
modbus_t p16[16];
unsigned long u32wait;
  unsigned long wait;
uint8_t p16state; //!< machine state

uint8_t p16query; //!< pointer to message query

union t0{
 float f;
 uint16_t u[2];
}t8A;


 void telegram_8A()
{
      unsigned long u32wait2=millis()+200;
       master.query( telegram[0] ); // send query (only once)
       master.poll();
       int count = 0;
      //  Serial.println("modbus_querry:"+String(i)+","+String(millis()));
      while (master.getState() != COM_IDLE)
        {
          // unsigned long u32wait2=millis()+200;
          master.poll(); // check incoming messages
          // Вот эта штука очень важная. Эти символы вносят некую задержку, чтобы функция считывания прочухалась
          // про это нигде не написано, но если их подобрать неправильно почему данные нифига не считываются
         
          //  Serial.println("8A...:"+String(count));
          if (millis()>u32wait2)
             {
               
               Serial.println("modbus error 8A");
              //  flag = 1;
             
               return 1;
               break;
             } 
             count++;
        }
}
void telegram_8AC()
{
      unsigned long u32wait2=millis()+200;
       master.query( telegram[1] ); // send query (only once)
       master.poll();
       int count = 0;
      //  Serial.println("modbus_querry:"+String(i)+","+String(millis()));
      while (master.getState() != COM_IDLE)
        {
          // unsigned long u32wait2=millis()+200;
          master.poll(); // check incoming messages
          // Вот эта штука очень важная. Эти символы вносят некую задержку, чтобы функция считывания прочухалась
          // про это нигде не написано, но если их подобрать неправильно почему данные нифига не считываются
         
          //  Serial.println("8AC...:"+String(count));
          if (millis()>u32wait2)
             {
               
               Serial.println("modbus error 8AC");
              //  flag = 1;
             
               return 1;
               break;
             } 
             count++;
        }
}
void telegram_16P()
{
      unsigned long u32wait2=millis()+200;
       master.query( telegram[2] ); // send query (only once)
       master.poll();
       int count = 0;
      //  Serial.println("modbus_querry:"+String(i)+","+String(millis()));
      while (master.getState() != COM_IDLE)
        {
          // unsigned long u32wait2=millis()+200;
          master.poll(); // check incoming messages
          // Вот эта штука очень важная. Эти символы вносят некую задержку, чтобы функция считывания прочухалась
          // про это нигде не написано, но если их подобрать неправильно почему данные нифига не считываются
         
          //  Serial.println("16P...:"+String(count));
          if (millis()>u32wait2)
             {
               
               Serial.println("modbus error");
              //  flag = 1;
             
               return 1;
               break;
             } 
             count++;
        }
     
  //  slave_1.poll(slave_data, 100 );
//  if (state > 4) { //Si es mayor a 4 = el pedido fué correcto
//     tempus = millis() + 200; //Tiempo actual + 50ms
//     // digitalWrite(13, HIGH);//Prende el led
//   }
  // if (millis() > tempus)  io_poll();
 }
void modbus_up()
{
 switch( u8state ) {
  case 0: 
    if (millis() > u32wait) u8state++; // wait state
    break;
  case 1: 
    master.query( telegram[u8query] ); // send query (only once)
    // Serial.println("modbus_querry:"+String(u8query));
    u8state++;
	u8query++;
	if (u8query > id_t) u8query = 0;
    break;
  case 2:
    master.poll(); // check incoming messages
    if (master.getState() == COM_IDLE) {
      u8state = 0;
      u32wait = millis() + 200; 
     }
    break;
  }
// switch( p16state ) {
//   case 0: 
//     if (millis() > wait) p16state++; // wait state
//     break;
//   case 1: 
//     master.query( p16[p16query] ); // send query (only once)
//     Serial.println("modbus_querry:"+String(p16query));
//     p16state++;
// 	p16query++;
// 	if (p16query > 16) p16query = 0;
//     break;
//   case 2:
//     master.poll(); // check incoming messages
//     if (master.getState() == COM_IDLE) {
//       p16state = 0;
//       wait = millis() + 50; 
//      }
//     break;
// }
// P16_update();
  }



void GetMessage_old(int addr)
{
  flag = LOW;
   
    // uint8_t p16state; //!< machine state

    // uint8_t p16query; //!< pointer to message query
    
      unsigned long u32wait2=millis()+200;
       master.query( p16[addr] ); // send query (only once)
       master.poll();
       int count = 0;
      //  Serial.println("modbus_querry:"+String(i)+","+String(millis()));
      while (master.getState() != COM_IDLE)
        {
          // unsigned long u32wait2=millis()+200;
          master.poll(); // check incoming messages
          // Вот эта штука очень важная. Эти символы вносят некую задержку, чтобы функция считывания прочухалась
          // про это нигде не написано, но если их подобрать неправильно почему данные нифига не считываются
         delay(20);
          // Serial.println("p16.:........"+String(count));
          if (millis()>u32wait2)
             {
               
               Serial.println("modbus error p16");
              //  flag = 1;
             
               return 1;
               break;
             } 
             count++;
        }

}
    
  void GetMessage()
{
// for ( i = 0; i < 16; i++)
// {
//   GetMessage_old(i);
// }
switch( p16state ) {
  case 0: 
    if (millis() > wait) p16state++; // wait state
    break;
  case 1: 
    master.query( p16[p16query] ); // send query (only once)
    Serial.println("modbus_querry:"+String(p16query));
    p16state++;
	p16query++;
	if (p16query > 16) p16query = 0;
    break;
  case 2:
    master.poll(); // check incoming messages
    if (master.getState() == COM_IDLE) {
      p16state = 0;
      // wait = millis() + 50; 
     }
    break;
}
}

void setup_modbus()
{
  telegram[0].u8id = 32; // slave address 8 my 32 work
  telegram[0].u8fct = 3; // function code (this one is registers read)
  telegram[0].u16RegAdd = 0x000; // start address in slave
  telegram[0].u16CoilsNo = 0x001D; // number of elements (coils or registers) to read
  telegram[0].au16reg = reg; // pointer to a memory array in the Arduino
// telegram 1: write a single register
  telegram[1].u8id = 48; // slave address 10 my 48 work
  telegram[1].u8fct = 3; // function code (this one is write a single register 6)
  telegram[1].u16RegAdd = 0x100; // start address in slave
  telegram[1].u16CoilsNo = 7; // number of elements (coils or registers) to read
  telegram[1].au16reg = regs_8AC; // pointer to a memory array in the Arduino

  telegram[2].u8id = 16; // slave address 32
  telegram[2].u8fct = 16; // function code (this one is registers read)
  telegram[2].u16RegAdd = 50; // start address in slave
  telegram[2].u16CoilsNo = 1; // number of elements (coils or registers) to read
  telegram[2].au16reg = regs_16P_read; // pointer to a memory array in the Arduino
  

  for ( i = 0; i < 16; i++)
  {
  p16[i].u8id = 16; // slave address
  p16[i].u8fct = 5; // function code (this one is registers read)
  p16[i].u16RegAdd = i; // start address in slave
  p16[i].u16CoilsNo = 1; // number of elements (coils or registers) to read
  p16[i].au16reg = regs_16P+i; // pointer to a memory array in the Arduino
  }
  
  
  // Serial.begin(9600);//use the hardware serial if you want to connect to your computer via usb cable, etc.
  master.begin( 9600 ); // begin the ModBus object. The first parameter is the address of your SoftwareSerial address. Do not forget the "&". 9600 means baud-rate at 9600
  master.setTimeOut( 1000 ); // if there is no answer in 2000 ms, roll over
  u32wait = millis() + 100;
  u8state = 0; 
    //////////
    //  slave_1.begin( 115200 ); // baud-rate at 19200
    //  tempus = millis() + 100; //Guarda el tiempo actual + 100ms
     /////////
  
  
}

void loop_modbus()
{
//   for ( i = 0; i < 16; i++)
// {
//   if (regs_16P[i]!=regs_16P_read[i]/1000)
//   {
//     regs_16P[i]=regs_16P_read[i]/1000; /* code */
//     flag = 0;
//   }
// }

  // for ( i = 0; i < 16; i++)
  // {
  //   if (regs_16P[i] != regs_16P_in[i])
  // {
  //   regs_16P[i]=regs_16P_in[i];
  //   flag = HIGH;
  // }
  // }
  // if (flag)
  // {
  //   // P16_update();
  //   // P16_update();
  //   GetMessage();
  //   // GetMessage();
  //   flag=LOW;
  // }
  
  // for ( i = 0; i < 8; i++)
  // {
  //   /* code */
  // }
  
  
    // reg_16P[0] = 0;
    int16_t status_1 = reg[2];
    t8A.u[0] = reg[5];
    t8A.u[1] = reg[4];
    if (status_1 == 0)
    {
      Temp_8A[0] = t8A.f;
    }
    else
    {
      Temp_8A[0] = status_1;
    }
    t8A.u[0] = reg[11];
    t8A.u[1] = reg[10];
    int16_t status_2 = reg[8];
    if (status_2 == 0)
    {
      Temp_8A[1] = t8A.f;
    }
    else
    {
      Temp_8A[1] = status_2;
    }
    int16_t status_3 = reg[14];
    t8A.u[0] = reg[17];
    t8A.u[1] = reg[16];
    if (status_3 == 0)
    {
      Temp_8A[2] = t8A.f;
    }
    else
    {
      Temp_8A[2] = status_3;
    }
    // MB110_8A.Temp_in3 = (reg(13)/10.0);
    // Temp_8A[2] = MB110_8A.Temp_in3;
    int16_t status_4 = reg[20];
    t8A.u[0] = reg[23];
    t8A.u[1] = reg[22];
    if (status_4 == 0)
    {
      Temp_8A[3] = t8A.f;
    }
    else
    {
      Temp_8A[3] = status_4;
    }
    int16_t status_5 = reg[26];
    t8A.u[0] = reg[29];
    t8A.u[1] = reg[28];
    if (status_5 == 0)
    {
      Temp_8A[4] = t8A.f;
    }
    else
    {
      Temp_8A[4] = status_5;
    }
 
 int16_t I_out1 = regs_8AC[0];
 int16_t I_out2 = regs_8AC[1];
 int16_t I_out3 = regs_8AC[2];
 int16_t I_out4 = regs_8AC[3];
 int16_t I_out5 = regs_8AC[4];
 int16_t I_out6 = regs_8AC[5];
 int16_t I_out7 = regs_8AC[6];
 int16_t I_out8 = regs_8AC[7];

 float RH = (I_out1-4)/16*100;
 float res = I_out3/10.00;
 float res1 = I_out4/10.00;
 Humid = res;
 NH3 = res1;
  // Serial.print("1: "+String(reg_8AC[2]));
  // Serial.println(" 2: "+String(reg_8AC[3]));
  // Serial.println(" poliv: "+String(reg_16P[1]));

//  slave_loop();

}
