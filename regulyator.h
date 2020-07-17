
// Вентиляция
 unsigned long newtime = 0;
 unsigned long newtime1 = 0;
void closewindows(){
  bool run = true;
  while (closeWindows){ 
  if(!flag_RELAY4_Vent){
   digitalWrite(RELAY4PIN, LOW);
  //  regs_16P[1] = HIGH;
   bitWrite(regs_16P_read[0],1,HIGH);
   slave_data[40] = 2;
  //  GetMessage_old(1);
   telegram_16P();
    if (run)
     {
     slave_loop();
     Serial.println("RUN_close");
     run = false;
     }
  
   flag_RELAY4_Vent = true;
    Serial.println("окна закрываются");
   new_time = millis() + (VentTime*1000);
   flag_wind = false;
 }
  else if(millis() > new_time) {
     digitalWrite(RELAY4PIN, HIGH);
    //  regs_16P[1] = LOW;
     bitWrite(regs_16P_read[0],1,LOW);
     slave_data[40] = 0;
    //  GetMessage();
    //  GetMessage_old(1);
     telegram_16P();
     slave_loop();
     flag_RELAY4_Vent = false;
     Serial.println("окна закрыты");
     closeWindows = false;
     openWindows = true;
  }
 } 
}
void openwindows()
{
  bool run = true;
   while (openWindows)
   {
    if(!flag_RELAY3_Vent){
     digitalWrite(RELAY3PIN, LOW);// Включить реле
      slave_data[40] = 3;
    //  regs_16P[0]= HIGH;
     bitWrite(regs_16P_read[0],0,HIGH);
    //  GetMessage_old(0);
     telegram_16P();
     if (run)
     {
     slave_loop();
     Serial.println("RUN_open");
     run = false;
     }
     
     
     flag_RELAY3_Vent = true;
     Serial.println("окна открываются");
     newtime = millis()+(VentTime*1000);
     }
    else if(millis() > newtime){
        digitalWrite(RELAY3PIN, HIGH);
        // regs_16P[0] = LOW;
        bitWrite(regs_16P_read[0],0,LOW);
        slave_data[40] = 1;
        //  GetMessage_old(0);
         telegram_16P();
        slave_loop();
        flag_RELAY3_Vent = false;
        flag_wind = true;
        openWindows = false;
        closeWindows = true;
        run = false; 
        Serial.println("окна открыты");
        }
}
}
 void VentTemp(int PINon, int PINoff, float Tin, float VentStart, float VentStop){
  //  Serial.println("Tin:"+String(Tin));
  //  Serial.println("Tstart:"+String(VentStart));
  // Если текущая температура больше или равно Температуры открытия и окно закрыто
  if (!isFirstConnect)
  {
     if (Tin > VentStart&&!flag_wind&&!flag_RELAY4_Vent)  {
      openwindows();

   } 
  if (Tin < VentStop && flag_wind && !flag_RELAY3_Vent)
  {  closewindows(); }  
  }
  }
//функция закрытия окон при первом запуске
void start()
{
  while (isFirstConnect)
  {
    for ( i = 0; i < 16; i++)
    {
      bitWrite(regs_16P_read[0],i,LOW);
      regs_8AC[i]=0;
    }
    if (VentTempStart!=temp_on)
    {
    slave_data[20] = VentTempStart;
    }
    if (VentTempStop!=temp_off)
    {
    slave_data[21] = VentTempStop;
    }
    if (VentTime!=time_on)
    {
    slave_data[22] = VentTime;
    }
    
    // modbus_update();
    loop_modbus();
    VentTime = 5;
    closewindows();
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
