void funk() {

  /********************************** Sensor Daten vom Sender **********************/
  if ( radio.available() ) {                   // if there is data ready
    while (radio.available()) {                // Dump the payloads until we've gotten everything
      radio.read( &sens, sizeof(sens) );       // Get the payload, and see if this was the last one.
    }

    BaroC = sens[1];
    //BaroKPA = (sens[2] * 10) + 64.6;
    Temp  = sens[3];
    Feuchte = sens[4];

    //--------------- Parameter für Internationale Barometische Höhenformel
    float Hoehe = 517.0;
    float TempGradient = 0.0065;
    float TempMeerKelvin = (273.15 + (Temp + (TempGradient * Hoehe)));
    float Exponent = 5.255;

    //KPA in hPA
    sens[2] = sens[2] * 10;
    
    //Internationale Barometische Höhenformel
    BaroKPA = sens[2] / pow((1 - ((TempGradient * Hoehe) / TempMeerKelvin)), Exponent);

    //Serial.println(BaroC);
    //Serial.println(sens[2]);
    //Serial.println(BaroKPA);
    //Serial.println(Temp);
    //Serial.println(Feuchte);
    
    //Zeitstempel
    sensDateTime = now;

    //Aufruf Tendenz
    barotendenz();

    radio.startListening();
  }


/******************************** Zeitstempel auswerten ******************************/
  if( now.unixtime() > (sensDateTime.unixtime() + 960)){
    BaroC = 0.0;
    BaroKPA = 0.0;
    Temp  = 0.0;
    Feuchte = 0.0;
  }
  
}

