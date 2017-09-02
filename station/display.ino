void display() {

  /**************************************** Display Helligkeit ***********************/
  //Dimmer LED niedrig=dunkel hoch=hell 0-255
  //Helligkeitssensor hoch=dunkel niedrig=hell 600-1023
  Licht = analogRead(iLicht);
  int y = map(Licht, 0, 1023, 70, 0);
  y = 40;
  analogWrite(oLcd, y);



  /*************************************** Bildwahl *****************************/
  //Standart Menue wechsel
  static bool BildwechselFlanke = 1;
  if (MenueFlanke && Bildwahl != 10) {
    BildwechselFlanke = 1;
    Bildwahl = Bildwahl + 1;
    if (Bildwahl > 2) {
      Bildwahl = 0;
    }
  }

  //Einstellungs Menue
  static unsigned long SetTime = 0;
  if (Set == HIGH) {
    if (SetFlanke) {
      SetTime = millis();
    }
    if (Set == HIGH && (millis() - SetTime) > 3000) {
      BildwechselFlanke = 1;
      Bildwahl = 10;
      SetTime = 0;
    }
  }



  switch (Bildwahl) {
    /************************************* Menue Seite 0 ****************************/
    case 0:
      //------------ Init -----------------------
      if (BildwechselFlanke == 1) {
        lcd.clear();

        //Zweite Zeile
        lcd.setCursor(0, 1);
        lcd.print("In");
        lcd.setCursor(9, 1);
        lcd.print("*C");
        lcd.setCursor(18, 1);
        lcd.print("%F");

        //Dritte Zeile
        lcd.setCursor(0, 2);
        lcd.print("Out");
        lcd.setCursor(9, 2);
        lcd.print("*C");
        lcd.setCursor(18, 2);
        lcd.print("%F");

        //           lcd.setCursor(12, 3);
        //   lcd.print("hP");
      }
      //------------------- Aktualisieren -------------------

      //------------------- Erste Zeile
      static int secondOld;
      static int dayOld;

      if ((now.day() != dayOld) || BildwechselFlanke == 1) {
        lcd.setCursor(0, 0);
        lcd.print(now.day(), DEC);
        lcd.print(".");
        lcd.print(now.month(), DEC);
        lcd.print(".");
        lcd.print((now.year() - 2000), DEC);

        lcd.print(" ");
        lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
        lcd.print(" ");
        dayOld = now.day();
      }

      if (now.second() != secondOld) {
        lcd.setCursor(12, 0);
        if (now.hour() < 10) {
          lcd.print("0");
          lcd.print(now.hour());
        }
        else {
          lcd.print(now.hour());
        }
        lcd.print(":");
        if (now.minute() < 10) {
          lcd.print("0");
          lcd.print(now.minute());
        }
        else {
          lcd.print(now.minute());
        }
        lcd.print(":");
        if (now.second() < 10) {
          lcd.print("0");
          lcd.print(now.second());
        }
        else {
          lcd.print(now.second());
        }
        secondOld = now.second();
      }


      //--------------------------- Zweite Zeile
      static float InTempOld;
      static float InFeuchteOld;

      if ((InTemp != InTempOld) || BildwechselFlanke == 1) {
        lcd.setCursor(4, 1);
        lcd.print(InTemp);
        InTempOld = InTemp;
      }

      if ((InFeuchte != InFeuchteOld) || BildwechselFlanke == 1) {
        lcd.setCursor(12, 1);
        lcd.print(InFeuchte);
        InFeuchteOld = InFeuchte;
      }


      //---------------------------------- Dritte Zeile
      static float TempOld;
      static float FeuchteOld;

      if ((Temp != TempOld) || BildwechselFlanke == 1) {
        lcd.setCursor(4, 2);
        lcd.print(Temp);
        TempOld = Temp;
      }

      if ((Feuchte != FeuchteOld) || BildwechselFlanke == 1) {
        lcd.setCursor(12, 2);
        lcd.print(Feuchte, 2);
        FeuchteOld = Feuchte;
      }


      //---------------------------------------- Vierte Zeile
      static float BaroKPAOld;
      static byte BaroFifoDiffOld[25];

      if ((BaroKPA != BaroKPAOld) || BildwechselFlanke == 1) {
        lcd.setCursor(0, 3);
        lcd.print(BaroKPA, 1);
        BaroKPAOld = BaroKPA;
      }

      for (int z = 1; z <= 24; z++) {
        if ((BaroFifoDiff[z] != BaroFifoDiffOld[z]) || BildwechselFlanke == 1) {
          lcd.setCursor(9, 3);
          lcd.write(BaroFifoDiff[24]);
          lcd.write(BaroFifoDiff[21]);
          lcd.write(BaroFifoDiff[18]);
          lcd.write(BaroFifoDiff[15]);
          lcd.write(BaroFifoDiff[12]);
          lcd.write(BaroFifoDiff[9]);
          lcd.write(BaroFifoDiff[6]);
          lcd.write(BaroFifoDiff[3]);
          lcd.write(BaroFifoDiff[1]);
          lcd.setCursor(19, 3);
          lcd.write(BaroFifoDiff[0]);
          for (int e = 1; e <= 24; e++) {
            BaroFifoDiffOld[e] = BaroFifoDiff[e];
          }
        }
      }

      BildwechselFlanke = 0;
      break;


    /************************************* Menue Seite 1 ****************************/
    case 1:
      //--------------- Init ---------------
      if (BildwechselFlanke == 1) {
        lcd.clear();
        BildwechselFlanke = 0;

        int BaroFifo1Zaehler1 = 0;
        for (int z = 0; z <= 3; z++) {
          int y = 0;
          lcd.setCursor(0, z);
          for (int x = 1; x <= 3; x++) {
            lcd.setCursor(y, z);
            lcd.print(BaroFifo[BaroFifo1Zaehler1], 1);
            BaroFifo1Zaehler1++;
            y = y + 7;
          }
        }
      }
      break;


    /************************************* Menue Seite 2 ****************************/
    case 2:
      //--------------- Init ---------------
      if (BildwechselFlanke == 1) {
        lcd.clear();
        BildwechselFlanke = 0;

        int BaroFifo1Zaehler2 = 12;
        for (int z = 0; z <= 3; z++) {
          int y = 0;
          lcd.setCursor(0, z);
          for (int x = 1; x <= 3; x++) {
            lcd.setCursor(y, z);
            lcd.print(BaroFifo[BaroFifo1Zaehler2], 1);
            BaroFifo1Zaehler2++;
            y = y + 7;
          }
        }
      }
      break;


    /************************************* Einstellungen Seite 10 ****************************/
    case 10:
      //Aufruf Uhr
      uhrzeit();
      break;

    case 98:
      lcd.setCursor(0, 0);
      //lcd.write(0);
      lcd.write(1);
      lcd.write(2);
      lcd.write(3);
      lcd.write(4);
      lcd.write(5);
      lcd.write(6);
      lcd.write(7);
      lcd.write(8);
      break;

    case 99: //Display Zeichensatz ausgeben
      if (BildwechselFlanke == 1) {
        lcd.clear();
        BildwechselFlanke = 0;
      }
      //Aktualisieren
      uint8_t i = 0;
      while (1) {
        lcd.clear();
        lcd.print("Codes 0x"); lcd.print(i, HEX);
        lcd.print("-0x"); lcd.print(i + 16, HEX);
        lcd.setCursor(0, 1);
        for (int j = 0; j < 16; j++) {
          lcd.write(i + j);
        }
        i += 16;

        delay(5000);
      }

      break;
  }

}
