void barotendenz() {

  /********************************* Wetter Vorhersage ***************************************************/
  enum { WetterSchlechter, WetterGleich, WetterBesser };
  static byte WetterTendenz = WetterGleich; // anfänglicher Startwert für den Algorithmus "veränderlich"
  static float BaroTendenz;

  float BaroTendenzDiff = BaroKPA - BaroTendenz;


  //-------------- Zeit unabhängige Tendenz
  if (BaroTendenzDiff >= 3.0 && WetterTendenz < WetterBesser) // Vorhersage eine Stufe besser
  {
    WetterTendenz++;
    BaroTendenz = BaroKPA;
  }
  else if (BaroTendenzDiff <= -3.0 && WetterTendenz > WetterSchlechter) // Vorhersage eine Stufe schlechter
  {
    WetterTendenz--;
    BaroTendenz = BaroKPA;
  }
  else if (BaroTendenzDiff > 0 && WetterTendenz == WetterBesser) BaroTendenz = BaroKPA;
  else if (BaroTendenzDiff < 0 && WetterTendenz == WetterSchlechter) BaroTendenz = BaroKPA;

  switch (WetterTendenz) {
    case WetterSchlechter:
      BaroFifoDiff[0] = (8);
      break;
    case WetterGleich:
      BaroFifoDiff[0] = (7);
      break;
    case WetterBesser:
      BaroFifoDiff[0] = (6);
      break;
  }



  /********************************** Tendenzen der letzten 24 berechnen *******************************/
  for (int i = 1; i <= 24; i++) {
    BaroTendenzDiff = BaroKPA - BaroFifo[i];
    if (BaroTendenzDiff >= 3.0) {
      BaroFifoDiff[i] = (5);
    }
    else if (BaroTendenzDiff >= 1.5) {
      BaroFifoDiff[i] = (4);
    }
    else if (BaroTendenzDiff <= -3.0) {
      BaroFifoDiff[i] = (1);
    }
    else if (BaroTendenzDiff <= -1.5) {
      BaroFifoDiff[i] = (2);
    }
    else {
      BaroFifoDiff[i] = (3);
    }
  }

}
