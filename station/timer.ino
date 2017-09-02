/*    static  int uhrcase = 0;
  static unsigned int stunde1 = 0;
  static unsigned int stunde2 = 0;
  static unsigned int minute1 = 0;
  static unsigned int minute2 = 0;


    //Weiterschalten
  if (SetFlanke) {
    uhrcase = uhrcase + 1;
  }

switch (uhrcase) {  



    //---------------- Start -----------------------
    case 0:
      lcd.clear();
      uhrcase = 2;
      break;


    //---------------- Stunde1 -----------------------
    case 2:
      // Turn on the cursor:
      lcd.cursor();

      lcd.setCursor(5, 0);
      lcd.print("Zeit ");
      lcd.print(stunde1);
      if (PlusFlanke) {
        stunde1 = stunde1 + 1;
      }
      if (MinusFlanke) {
        stunde1 = stunde1 - 1;
      }
      break;


    //---------------- Stunde2 -----------------------
    case 3:
      lcd.setCursor(5, 0);
      lcd.print("Zeit ");
      lcd.print(stunde1);
      lcd.print(stunde2);
      if (PlusFlanke) {
        stunde2 = stunde2 + 1;
      }
      if (MinusFlanke) {
        stunde2 = stunde2 - 1;
      }
      break;


    //---------------- Minute1 -----------------------
    case 4:
      lcd.setCursor(5, 0);
      lcd.print("Zeit ");
      lcd.print(stunde1);
      lcd.print(stunde2);
      lcd.print(":");
      lcd.print(minute1);
      if (PlusFlanke) {
        minute1 = minute1 + 1;
      }
      if (MinusFlanke) {
        minute1 = minute1 - 1;
      }
      break;


    //---------------- Minute2 -----------------------
    case 5:
      lcd.setCursor(5, 0);
      lcd.print("Zeit ");
      lcd.print(stunde1);
      lcd.print(stunde2);
      lcd.print(":");
      lcd.print(minute1);
      lcd.print(minute2);
      if (PlusFlanke) {
        minute2 = minute2 + 1;
      }
      if (MinusFlanke) {
        minute2 = minute2 - 1;
      }
      break;
      
      case 5:
      
      TimerZeit= now + TimeSpan(0, 1, 0, 0);
      break;
      
}





  //------------------------ Variblen begrenzen ----------------------
  if (stunde1 >= 3) {
    stunde1 = 0;
  }
  if (stunde2 >= 10) {
    stunde2 = 0;
  }
  if (minute1 >= 6) {
    minute1 = 0;
  }
  if (minute2 >= 10) {
    minute2 = 0;
  }


*/
  
