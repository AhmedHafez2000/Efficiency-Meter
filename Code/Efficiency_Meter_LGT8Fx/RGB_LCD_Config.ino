void display_data(){  
  
  tft.setTextWrap(false);
  tft.setCursor(30, 0);
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setTextSize(2);
  tft.print("OUTPUT   INPUT");
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
  tft.setTextSize(2);
  tft.print("V:");
  tft.setCursor(0, 60);
  tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
  tft.setTextSize(2);
  tft.print("C:");
  tft.setCursor(0, 90);
  tft.setTextColor(ST77XX_MAGENTA, ST77XX_BLACK);
  tft.setTextSize(2);
  tft.print("P:");
  // Voltages
  if(VOUT > 19){
    tft.setCursor(30, 30);
    tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.print(VOUT,3);
    tft.print("v");
  }
  else{
    tft.setCursor(30, 30);
    tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.print(VOUT,3);
    tft.print("v");
  
    if(VOUT < 10){
      tft.fillRect(100, 30, 12, 20, ST77XX_BLACK);
    }
  }
  if(VIN > 19){
    tft.setCursor(140, 30);
    tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.print(VIN,3);
    tft.print("v");
  }
  else{
    tft.setCursor(140, 30);
    tft.setTextColor(ST77XX_GREEN, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.print(VIN,3);
    tft.print("v");
  
    if(VIN < 10){
      tft.fillRect(210, 30, 12, 20, ST77XX_BLACK);
    }
  }
  // Currents
  if(COUT > 6){
    tft.setCursor(30, 60);
    tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.print(COUT,3);
    tft.print("A");
  }
  else{
    tft.setCursor(30, 60);
    tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.print(COUT,3);
    tft.print("A");
  }
  if(CIN > 6){
    tft.setCursor(140, 60);
    tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.print(CIN,3);
    tft.print("A");
  }
  else{
    tft.setCursor(140, 60);
    tft.setTextColor(ST77XX_CYAN, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.print(CIN,3);
    tft.print("A");
  }
  //POWER
  if(POUT > 50){
    tft.setCursor(30, 90);
    tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.print(POUT);
    tft.print("W");
  }
  else{
    tft.setCursor(30, 90);
    tft.setTextColor(ST77XX_MAGENTA, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.print(POUT);
    tft.print("W");
  
    if(POUT < 10){
      tft.fillRect(90, 90, 12, 20, ST77XX_BLACK);
    }
  }
  if(PIN > 50){
    tft.setCursor(140, 90);
    tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.print(PIN);
    tft.print("W");
  }
  else{
    tft.setCursor(140, 90);
    tft.setTextColor(ST77XX_MAGENTA, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.print(PIN);
    tft.print("W");
  
    if(PIN < 10){
      tft.fillRect(200, 90, 12, 20, ST77XX_BLACK);
    }
  }
  //Efficiency
  tft.setCursor(0, 120);
  tft.setTextColor(ST77XX_YELLOW, ST77XX_BLACK);
  tft.setTextSize(2);
  tft.print("Eff:");
  tft.setCursor(52, 120);
  tft.print(Efficiency);
  tft.print("%");
  if(Efficiency < 10){
    tft.fillRect(112, 120, 24, 20, ST77XX_BLACK);
  }else if(Efficiency < 100){
    tft.fillRect(124, 120, 12, 20, ST77XX_BLACK);
  }
  if(E_enable == 1){
    if(energy > 100 && energy < 1000){
      energy = energy + (PIN/36);  //(PIN*1000)/(0.1/3600)
      tft.setCursor(132, 120);
      tft.setTextColor(ST77XX_ORANGE, ST77XX_BLACK);
      tft.setTextSize(2);
      tft.print(energy);
      tft.print("mWh");
    }else if(energy > 1000){
      if(energy_Wh < 1.01){tft.fillRect(132, 120, 11, 20, ST77XX_BLACK);}
      energy_Wh = energy_Wh + (PIN*(.1/3600));  //PIN*(0.1/3600)
      tft.setCursor(140, 120);
      tft.setTextColor(ST77XX_ORANGE, ST77XX_BLACK);
      tft.setTextSize(2);
      tft.print(energy_Wh);
      tft.print("Wh   ");
    }else{
      energy = energy + (PIN/36);  //(PIN*1000)/(0.1/3600)
      tft.setCursor(140, 120);
      tft.setTextColor(ST77XX_ORANGE, ST77XX_BLACK);
      tft.setTextSize(2);
      tft.print(energy);
      tft.print("mWh");
    }
  }
  if(E_enable == 0){
    tft.setCursor(132, 120);
    tft.setTextColor(ST77XX_ORANGE, ST77XX_BLACK);
    tft.setTextSize(2);
    tft.print("         ");
  }
}
