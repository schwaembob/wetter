void inTemp() {
  
  //Alle x millis 
  static unsigned long Timesafe = 0;
  if (millis() - Timesafe > 10000) {

    //Sensor auslesen
    InTemp = dht.readTemperature();
    InFeuchte = dht.readHumidity();
    float hic = dht.computeHeatIndex(InTemp, InFeuchte, false);

//    Serial.print("Humidity: ");
//    Serial.print(InFeuchte);
//    Serial.print(", ");
//    Serial.print("Temperature: ");
//    Serial.println(InTemp);
//    Serial.print(" *C ");
//    Serial.print("Heat index: ");
//    Serial.print(hic);
//    Serial.println(" *C ");

    Timesafe = millis();
  }
}
