
// Вентиляция
 unsigned long newtime = 0;
 unsigned long newtime1 = 0;
void closewindows(){
  // bool run = true;
  // while (close){ 
  if(!flag_RELAY4_Vent){
   digitalWrite(RELAY4PIN, LOW);
  //  regs_16P[1] = HIGH;
   bitWrite(regs_16P_read[0],1,HIGH);
   slave_data[45] = 2;
  //  GetMessage_old(1);
   telegram_16P();
    // if (run)
    //  {
    //  slave_loop();
    //  Serial.println("RUN_close");
    //  run = false;
    //  }
  
   flag_RELAY4_Vent = true;
    Serial.println("окна закрываются");
   new_time = millis() + (VentTime*1000);
   
 }
  else if(millis() > new_time) {
     digitalWrite(RELAY4PIN, HIGH);
    //  regs_16P[1] = LOW;
     bitWrite(regs_16P_read[0],1,LOW);
     slave_data[45] = 0;
    //  GetMessage();
    //  GetMessage_old(1);
     telegram_16P();
     slave_loop();
     flag_RELAY4_Vent = false;
     Serial.println("окна закрыты");
     close = false;
     run = false;
     open = true;
     flag_wind = false;
  }
//  } 
}
void openwindows()
{
  // bool run = true;
  //  while (openWindows)   {
    if(!flag_RELAY3_Vent){
     digitalWrite(RELAY3PIN, LOW);// Включить реле
      slave_data[45] = 3;
    //  regs_16P[0]= HIGH;
     bitWrite(regs_16P_read[0],0,HIGH);
    //  GetMessage_old(0);
     telegram_16P();
    //  if (run)
    //  {
    //  slave_loop();
    //  Serial.println("RUN_open");
    //  run = false;
    //  }
     
     
     flag_RELAY3_Vent = true;
     Serial.println("окна открываются");
     newtime = millis()+(VentTime*1000);
     }
    else if(millis() > newtime){
        digitalWrite(RELAY3PIN, HIGH);
        // regs_16P[0] = LOW;
        bitWrite(regs_16P_read[0],0,LOW);
        slave_data[45] = 1;
        //  GetMessage_old(0);
         telegram_16P();
        slave_loop();
        flag_RELAY3_Vent = false;
        flag_wind = true;
        open = false;
        close = true;
        run = false; 
        Serial.println("окна открыты");
        }
// }
}
 void VentTemp(int PINon, int PINoff, float Tin, float VentStart, float VentStop){
  //  Serial.println("Tin:"+String(Tin));
  //  Serial.println("Tstart:"+String(VentStart));
  // Если текущая температура больше или равно Температуры открытия и окно закрыто
  if (!isFirstConnect)
  {
     if (Tin > VentStart&&!flag_wind&&!flag_RELAY4_Vent&&VentStart>VentStop)  {
      openwindows();

   } 
  if (Tin < VentStop && flag_wind && !flag_RELAY3_Vent && VentStart>VentStop)
  {  closewindows(); }  
  }
  }
//функция закрытия окон при первом запуске
void start()
{
  while (isFirstConnect)
  {
    // for ( i = 0; i < 16; i++)
    // {
    //   bitWrite(regs_16P_read[0],i,LOW);
    //   regs_8AC[i]=0;
    // }
    if (VentTempStart!=temp_on)
    {
    slave_data[25] = VentTempStart;
    }
    if (VentTempStop!=temp_off)
    {
    slave_data[26] = VentTempStop;
    }
    if (VentTime!=time_on)
    {
    slave_data[27] = VentTime;
    }
    
    // modbus_update();
    loop_modbus();
    VentTime = 5;
   
    while (run)
    {
       closewindows();/* code */
    }
    
   
    Tmin = 50.00;
    Tmax = -50.00;
    Tmax_i = -50.00;
    Tmin_i =  50.00;
    statistic();

    isFirstConnect = false;
  }
  
}




void vent()
{
  // if (VentTempStart != temp_on )
  // {
  //   VentTempStart = temp_on;
  // }
  // if (VentTempStop != temp_off )
  // {
  //   VentTempStop = temp_off;
  // }
  // if (VentTime != time_on )
  // {
  //   VentTime = time_on;
  // }
  VentTemp(RELAY3PIN, RELAY4PIN, Temp_in, VentTempStart, VentTempStop); 
}

//Обогрев

void zona(){
  vent();
  if (heat)
  {
  for (int i = 0; i < 4; i++)
{
  if (U_Temp[i] > Temp[i] && Temp[i]>= -50 && Temp[i] <= 70.00 && Temp[i] !=0)
{
  flag_Zona[i] = HIGH;
  slave_data[38+i] = HIGH;
  slave_data_3[38+i] = HIGH;
  // Serial.println("flag_Zona"+String(i)+":"+String (flag_Zona[i])); 
}
else
{
  flag_Zona[i] = LOW;
  slave_data[38+i] = LOW;
  slave_data_3[38+i] = LOW;
}
}
for (int i = 0; i < 4; i++)
{
  if (flag_Zona[i])
{
  relay_Zona[i] = HIGH;
  // regs_16P[i+12] = HIGH;
  bitWrite(regs_16P_read[0],i+12,HIGH);
}
else
{
  relay_Zona[i] = LOW;
  // regs_16P[i+12] = LOW;
  bitWrite(regs_16P_read[0],i+12,LOW);
}
}
  digitalWrite(RELAY_ZONA_1_PIN, relay_Zona[0]);
  digitalWrite(RELAY_ZONA_2_PIN, relay_Zona[1]);
  digitalWrite(RELAY_ZONA_3_PIN, relay_Zona[2]);
  digitalWrite(RELAY_ZONA_4_PIN, relay_Zona[3]);
  }
  else
  {
    for (int i = 0; i < 4; i++)
    {
      flag_Zona[i] = LOW;
      //  regs_16P[i+12] = LOW;
       bitWrite(regs_16P_read[0],i+12,LOW);
       slave_data[38+i] = LOW;
       slave_data_3[38+i] = LOW;
    }
  digitalWrite(RELAY_ZONA_1_PIN, LOW);
  digitalWrite(RELAY_ZONA_2_PIN, LOW);
  digitalWrite(RELAY_ZONA_3_PIN, LOW);
  digitalWrite(RELAY_ZONA_4_PIN, LOW);
  }
 
}

void up_uart(){


if (temp_on!=VentTempStart)
{
    VentTempStart = temp_on;
    VentTempStart_t = temp_on;
    Serial.print("tempStart: "+String(slave_data[25]));
    Serial.println(" Label: "+String(VentTempStart));
    EEPROM.update(29, VentTempStart);
    // EEPROM.end();
}
if (temp_off!=VentTempStop)
{
    VentTempStop = temp_off;
    VentTempStop_t = temp_off;
     Serial.print("tempstop: "+String(slave_data[26]));
    Serial.println(" Label: "+String(VentTempStop));
     EEPROM.update(30, VentTempStop);
    // EEPROM.end();
}
if (time_on!=VentTime)
{
    VentTime = time_on;
    VentTime_t = time_on;
     EEPROM.update(31, VentTime);
      Serial.print("venttime: "+String(slave_data[27]));
    Serial.println(" Label: "+String(VentTime));
    // EEPROM.end();
}
//  EEPROM.end();

 if (slave_data[46]!=heat)
  {
    heat = slave_data[46];
    heat_t = slave_data[46];
    // slave_data_3[98] = slave_data[45];
    Serial.println("heat_панель:"+String(heat));
   }
 
  // Serial.println("VentTime_uart: "+String(VentTime_t));  
        
        if (VentTime_t >= 0 && VentTime_t <= 120)
        {
        
          if (VentTime_t!=VentTime)
          {
            slave_data[27] = VentTime_t;
             VentTime = VentTime_t;
          EEPROM.update(31, VentTime);
          // EEPROM.end(); 
            // Serial.println("VentTime: "+String(VentTime)); 
          }
          
          //  Serial.println("VentTime_write_EEPROM: " + String(VentTime));
        }
        else 
        {
          VentTime = 10;
          slave_data[27] = VentTime;
          VentTime_t = VentTime;
          // Serial.println("VentTime_reed_EEPROM: " + String(VentTime)); 
         
        }
        if (VentTempStart_t >= 10 && VentTempStart_t <= 40 )
        {
          
           
           if (VentTempStart!=VentTempStart_t)
           {
           slave_data[25] = VentTempStart_t; 
           VentTempStart = VentTempStart_t;
           EEPROM.update(29, VentTempStart);
          //  EEPROM.end();
            // Serial.println("VentTempStart: " +String(VentTempStart) ); 
           }
        }
        else 
        {
         VentTempStart = 30;
          slave_data[25] = VentTempStart;
          VentTempStart_t = VentTempStart;
        }
         if (VentTempStop_t >= 10 && VentTempStop_t <= 40)
        {
          
           if (VentTempStop!=VentTempStop_t)
           {
          slave_data[26] = VentTempStop_t;
          VentTempStop = VentTempStop_t;
          EEPROM.update(30, VentTempStop);
          //  EEPROM.end();
          //  Serial.println("VentTempStop: "+String (VentTempStop)); 
           }

        }
        else 
        {
          VentTempStop = 28;
          slave_data[26] = VentTempStop;
          VentTempStop_t = VentTempStop;
        }
        
EEPROM.end(); 
//         if (U_Temp_u!=U_Temp[0])
// {
//   U_Temp[0] = U_Temp_u;
//   s_data.f = U_Temp[0];
//   slave_data[30] = s_data.u[0];
//   slave_data[31] = s_data.u[1];
// }
// if (U_Temp_u1!=U_Temp[1])
// {
//   U_Temp[1] = U_Temp_u1;
//   s_data.f = U_Temp[1];
//   slave_data[32] = s_data.u[0];
//   slave_data[33] = s_data.u[1];
// }
// if (U_Temp_u2!=U_Temp[2])
// {
//   U_Temp[2] = U_Temp_u2;
//   s_data.f = U_Temp[2];
//   slave_data[34] = s_data.u[0];
//   slave_data[35] = s_data.u[1];
// }
// if (U_Temp_u3!=U_Temp[3])
// {
//   U_Temp[3] = U_Temp_u3;
//   s_data.f = U_Temp[3];
//   slave_data[36] = s_data.u[0];
//   slave_data[37] = s_data.u[1];
// }

}