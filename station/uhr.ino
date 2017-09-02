void uhrzeit() {
  static  int uhrcase = 0;
  static unsigned int stunde1 = 0;
  static unsigned int stunde2 = 0;
  static unsigned int minute1 = 0;
  static unsigned int minute2 = 0;
  static unsigned int day1 = 0;
  static unsigned int day2 = 0;
  static unsigned int month1 = 0;
  static unsigned int month2 = 0;
  static unsigned int year1 = 0;
  static unsigned int year2 = 0;

  int stunden = 0;
  int minuten = 0;
  int day = 0;
  int month = 0;
  int year = 0;

  //Weiterschalten
  if (SetFlanke) {
    uhrcase = uhrcase + 1;
  }

  /************************************* Datum/Uhrzeit stellen ************************************/
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


    //---------------- Tag1 -----------------------
    case 6:
      lcd.setCursor(4, 1);
      lcd.print("Datum ");
      lcd.print(day1);
      if (PlusFlanke) {
        day1 = day1 + 1;
      }
      if (MinusFlanke) {
        day1 = day1 - 1;
      }
      break;


    //---------------- Tag2 -----------------------
    case 7:
      lcd.setCursor(4, 1);
      lcd.print("Datum ");
      lcd.print(day1);
      lcd.print(day2);
      if (PlusFlanke) {
        day2 = day2 + 1;
      }
      if (MinusFlanke) {
        day2 = day2 - 1;
      }
      break;


    //---------------- Monat1 -----------------------
    case 8:
      lcd.setCursor(4, 1);
      lcd.print("Datum ");
      lcd.print(day1);
      lcd.print(day2);
      lcd.print(".");
      lcd.print(month1);
      if (PlusFlanke) {
        month1 = month1 + 1;
      }
      if (MinusFlanke) {
        month1 = month1 - 1;
      }
      break;


//---------------- Monat2 -----------------------
    case 9:
      lcd.setCursor(4, 1);
      lcd.print("Datum ");
      lcd.print(day1);
      lcd.print(day2);
      lcd.print(".");
      lcd.print(month1);
      lcd.print(month2);
      if (PlusFlanke) {
        month2 = month2 + 1;
      }
      if (MinusFlanke) {
        month2 = month2 - 1;
      }
      break;


      //---------------- Jahr1-----------------------
    case 10:
      lcd.setCursor(4, 1);
      lcd.print("Datum ");
      lcd.print(day1);
      lcd.print(day2);
      lcd.print(".");
      lcd.print(month1);
      lcd.print(month2);
      lcd.print(".");
      lcd.print(year1);
      if (PlusFlanke) {
        year1 = year1 + 1;
      }
      if (MinusFlanke) {
        year1 = year1 - 1;
      }
      break;


//---------------- Jahr2 -----------------------
    case 11:
      lcd.setCursor(4, 1);
      lcd.print("Datum ");
      lcd.print(day1);
      lcd.print(day2);
      lcd.print(".");
      lcd.print(month1);
      lcd.print(month2);
      lcd.print(".");
      lcd.print(year1);
      lcd.print(year2);
      if (PlusFlanke) {
        year2 = year2 + 1;
      }
      if (MinusFlanke) {
        year2 = year2 - 1;
      }
      break;


//---------------- Berechnen -- setzen -----------------------
    case 12:
      stunden = stunde1 * 10;
      minuten = minute1 * 10;
      stunden = stunden + stunde2;
      minuten = minuten + minute2;
      day = day1 * 10;
      day = day + day2 ;
      month = month1 * 10;
      month = month + month2;
      year = year1 * 10;
      year = year + year2 + 2000;

      // This line sets the RTC with an explicit date & time, for example to set
      // January 21, 2014 at 3am you would call:
      rtc.adjust(DateTime(year, month, day, stunden, minuten, 0));

      // Turn off the cursor:
      lcd.noCursor();
      lcd.clear();
      uhrcase = 0;
      Bildwahl = 0;
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
  if (day1 >= 10) {
    day1 = 0;
  }
  if (day2 >= 10) {
    day2 = 0;
  }
  if (month1 >= 10) {
    month1 = 0;
  }
  if (month2 >= 10) {
    month2 = 0;
  }
  if (year1 >= 10) {
    year1 = 0;
  }
  if (year2 >= 10) {
    year2 = 0;
  }
}



