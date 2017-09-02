void loop() {

  //Uhrzeit auslesen
  now = rtc.now();

  //Aufruf Tasten Auswertung
  tasten();

  //BaroFifo jede volle Stunde befüllen
  static bool blockade; barotendenz();
  if (now.minute() == 0 && BaroKPA != 0.0 && blockade == false) {
    blockade = true;
    for (int i = 23; i >= 0; i--) {
      BaroFifo[i + 1] = BaroFifo[i];
    }
    BaroFifo[0] = BaroKPA;
  }
  if (now.minute() == 1) {
    blockade = false;
  }

  //Aufruf Innenraum Temp
  inTemp();

  //Aufruf Funk
  funk();

  //Aufruf Summer
  //summer();

  //Aufruf Display
  display();


  if ( Serial.available() ) {
    String a = Serial.readString();
    BaroKPA = a.toFloat();


    for (int i = 23; i >= 0; i--) {
      BaroFifo[i + 1] = BaroFifo[i];
    }
    BaroFifo[0] = BaroKPA;

    barotendenz();

    for (int z = 0; z <= 24; z++) {
      Serial.print(BaroFifo[z], 1);
      Serial.print(" / ");
    }
    Serial.println(" ");
    for (int z = 0; z <= 24; z++) {
      Serial.print(BaroFifoDiff[z], 1);
      Serial.print("   /   ");
    }
    Serial.println(" ");
  }


}
