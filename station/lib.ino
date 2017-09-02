

/*
boolean blinker(int zeit){
  static unsigned long zeitletzte;
  static boolean result;
  unsigned long zeitaktuell = millis();
  
  if (zeitaktuell - zeitletzte > zeit){
    if (result!=true){
      result=true;
    }
    else{
      result=false;
    }
    zeitletzte = zeitaktuell;
  }
  return result;

}
   */
