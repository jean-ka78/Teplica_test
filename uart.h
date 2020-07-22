#include <EasyTransfer.h>
EasyTransfer ETin, ETout; 
// EasyTransfer ETout_temp;

struct DATA{ 
  float Temp1;
  float Temp2;
  float Temp3;
  float Temp4;
  float Temp5;
  float Humid;
  float NH3;
  float t_in_min;
  float t_in_max;
  float t_out_min;
  float t_out_max;
  // int32_t CO2;
  // int32_t lux;
  int32_t Time_on;
  int32_t Temp_on;
  int32_t Temp_off;
  bool window;
  bool flag_z1;
  bool flag_z2;
  bool flag_z3;
  bool flag_z4;
  };

//DATA Data_mega;

union uart_t
{
DATA uart_txdata;
byte SEND_ARRAY[62];
};

uart_t txdata_u;

struct Resive_DATA
{
    float Vent_tstart;
    float Vent_tstop;
    float Temp_z_1;
    float Temp_z_2;
    float Temp_z_3;
    float Temp_z_4;
    int16_t Vent_time;
    int16_t hour;
    int16_t minute;
    int16_t second;
    bool but_esp;
    bool relley_poliv;
    bool relley_heat;
    bool lux_relley;
};

 //Resive_DATA Esp;

 union uart_r
 {
   Resive_DATA uart_rxdata;
   byte RESIVE_ARRAY[56];
 };
 
 uart_r rxdata_u;

void SEND_DATA()
{
    txdata_u.uart_txdata.Temp1 = Temp[0];
    txdata_u.uart_txdata.Temp2 = Temp[1];
    txdata_u.uart_txdata.Temp3 = Temp[2];
    txdata_u.uart_txdata.Temp4 = Temp[3];
    txdata_u.uart_txdata.Temp5 = Temp_out;
    txdata_u.uart_txdata.Temp_on = temp_on;
    txdata_u.uart_txdata.Temp_off = temp_off;
    txdata_u.uart_txdata.Time_on = time_on;
    txdata_u.uart_txdata.Humid = Humid;
    txdata_u.uart_txdata.NH3 = NH3;
    // txdata_u.uart_txdata.CO2 = CO2;
    txdata_u.uart_txdata.t_in_max = Tmax_i;
    txdata_u.uart_txdata.t_in_min = Tmin_i;
    txdata_u.uart_txdata.t_out_max = Tmax;
    txdata_u.uart_txdata.t_out_min = Tmin;
    txdata_u.uart_txdata.window = flag_wind;
    // txdata_u.uart_txdata.lux = lux;
    txdata_u.uart_txdata.flag_z1 = flag_Zona[0];
    txdata_u.uart_txdata.flag_z2 = flag_Zona[1];
    txdata_u.uart_txdata.flag_z3 = flag_Zona[2];
    txdata_u.uart_txdata.flag_z4 = flag_Zona[3];
    ETout.sendData();
    // Serial.println(txdata_u.uart_txdata.flag_z1);
    // Serial3.write((uint8_t*)&txdata_u.SEND_ARRAY, sizeof(txdata_u.SEND_ARRAY)); 
}

void DATA_Resive()
{
    //  while (Serial3.available()>0) 
    //     {
    //    uint8_t len = sizeof(rxdata_u.RESIVE_ARRAY);
      //  Serial3.readBytes((uint8_t*)&rxdata_u.RESIVE_ARRAY, len);
      //  for(int i=0; i<5; i++){
    // remember, you could use an if() here to check for new data, this time it's not needed.
   
   if (ETin.receiveData()){
  
        VentTime_t = rxdata_u.uart_rxdata.Vent_time;
        // 
         
        VentTempStart_t = rxdata_u.uart_rxdata.Vent_tstart;
        
         VentTempStop_t = rxdata_u.uart_rxdata.Vent_tstop;
       
        hour_t = rxdata_u.uart_rxdata.hour;
        minute_t = rxdata_u.uart_rxdata.minute;
        sec_t = rxdata_u.uart_rxdata.second;
        String currentTime = String(dt.hour)+":"+String(dt.minute)+":"+ String(dt.second);
        relay_poliv = rxdata_u.uart_rxdata.relley_poliv;
        heat_t = rxdata_u.uart_rxdata.relley_heat;
        // if (heat_t!=heat)
        // {
        //   heat=heat_t;
        //   Serial.println("heat: "+String (heat)); 
        // }
        
        relay_svet = rxdata_u.uart_rxdata.lux_relley;
        button_esp = rxdata_u.uart_rxdata.but_esp;
        U_Temp_u = rxdata_u.uart_rxdata.Temp_z_1;



        U_Temp_u1 = rxdata_u.uart_rxdata.Temp_z_2;

        U_Temp_u2 = rxdata_u.uart_rxdata.Temp_z_3;

        U_Temp_u3 = rxdata_u.uart_rxdata.Temp_z_4;

//         for (int i = 0; i < 4; i++)
//         {
//           if (U_Temp[i] > 50)
//         {
//           U_Temp[i] = 0;
//         }
//         }
//             // Serial.println(currentTime); 
//         }
//         else
//         {
//           // Serial.println("Нет связи UART ");
//           VentTempStart = 30;
//           // EEPROM.write(29, VentTempStart);
//           VentTempStop = 25;
//           // EEPROM.write(30, VentTempStop);
//            VentTime = 10;
//           // EEPROM.write(31, VentTime);
//           EEPROM.end();

//         }
        // if (rxdata_u.uart_rxdata.but_esp!=0)
        // {
        //   // Serial.println("esp_but: "+String(rxdata_u.uart_rxdata.but_esp));
        //   slave_data[10] = HIGH;
        // }
        // else
        // {
        //   slave_data[10] = LOW;
        }
        
        


      //  
      //   Serial.println("U_Temp2: "+String(U_Temp[1]));
      //   Serial.println("U_Temp3: "+String(U_Temp[2]));
      //   Serial.println("U_Temp4: "+String(U_Temp[3]));
      //   Serial.println("VentStart: "+String(VentTempStart));
      //   Serial.println("VentStop: "+String(VentTempStop));
      //   Serial.println("VentTime: "+String(VentTime));  
            
}

void uart()
{
  DATA_Resive();
  SEND_DATA();
}
void setup_uart()
{
//  ETin.begin(details(rxdata), &Serial2);
//   ETout.begin(details(txdata), &Serial2);
  
  ETin.begin(details(rxdata_u.RESIVE_ARRAY), &Serial3);
  ETout.begin(details(txdata_u.SEND_ARRAY), &Serial3);
  // ETout_temp.begin(details(txdata_u_temp.send_array_temp), &Serial3);
  
}
