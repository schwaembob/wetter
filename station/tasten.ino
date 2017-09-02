void tasten() {

  //Tasten Einlesen
  Menue = digitalRead(iMenue);
  Set = digitalRead(iSet);
  Plus = digitalRead(iPlus);
  Minus = digitalRead(iMinus);

  static bool MenuePos;
  if (Menue == HIGH && MenuePos == 0) {
    MenuePos = 1;
    MenueFlanke = 1;
  } else {
    MenueFlanke = 0;
  }
  if (Menue == LOW) {
    MenuePos = 0;
  }

  static bool SetPos;
  if (Set == HIGH && SetPos == 0) {
    SetPos = 1;
    SetFlanke = 1;
  } else {
    SetFlanke = 0;
  }
  if (Set == LOW) {
    SetPos = 0;
  }

  static bool PlusPos;
  if (Plus == HIGH && PlusPos == 0) {
    PlusPos = 1;
    PlusFlanke = 1;
  } else {
    PlusFlanke = 0;
  }
  if (Plus == LOW) {
    PlusPos = 0;
  }

  static bool MinusPos;
  if (Minus == HIGH && MinusPos == 0) {
    MinusPos = 1;
    MinusFlanke = 1;
  }   else {
    MinusFlanke = 0;
  }
  if (Minus == LOW) {
    MinusPos = 0;
  }
}
