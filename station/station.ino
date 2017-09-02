
/********************* Libs und Paramenter ********************************************************/
//Bus
#include <Wire.h>

//Display
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
uint8_t BaroUpUp[8]  = {0x0,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f};
uint8_t BaroUp[8]  = {0x0,0x0,0x0,0x1f,0x1f,0x1f,0x1f,0x1f};
uint8_t BaroUnchanged[8] = {0x0,0x0,0x0,0x0,0x1f,0x1f,0x1f,0x1f};
uint8_t BaroDown[8] = {0x0,0x0,0x0,0x0,0x0,0x1f,0x1f,0x1f};
uint8_t BaroDownDown[8]  = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f};
uint8_t BaroSun[8] = {0x1c,0x1c,0x19,0x10,0x4,0x12,0x11,0x10};
uint8_t BaroChangeable[8] = {0x0E,0x1F,0x0E,0x00,0x00,0x17,0x1D,0x00};
uint8_t BaroRain[8] = {0xe,0x1f,0xe,0x0,0x15,0x0,0xa};

//Uhr
#include "RTClib.h"
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};

//Funk
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
RF24 radio(7, 8);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };   // Radio pipe addresses for the 2 nodes to communicate.


//DHT22 Sensor
#include "DHT.h"
#define DHTPIN A1     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

//IOs Pins
int iMenue = 4;
int iSet = 5;
int iPlus = 2;
int iMinus = 3;
int oLcd = 6;
int oSummer = 9;
int iLicht = A0;


/******************************* Globale Variablen ***********************/
//Tasten
bool Menue;
bool Set;
bool Plus;
bool Minus;
bool MenueFlanke;
bool SetFlanke;
bool PlusFlanke;
bool MinusFlanke;

DateTime now;

int Bildwahl =0;

float Volt = 0;
float BaroC = 0;
double BaroKPA = 0;
float Temp = 0;
float Feuchte = 0;
float InTemp = 0;
float InFeuchte = 0;

DateTime sensDateTime;
float sens[5] = {Volt, BaroC, BaroKPA, Temp, Feuchte};

float Licht = 0;

float BaroFifo[25];
byte BaroFifoDiff[25];
/***********
bool TimerFertig;
bool TimerLäuft;
DateTime TimerZeit;
******************/
/******************************************* Setup *******************************/
void setup() {
  Serial.begin(115200);
  
  //DHT22 Sensor starten
  dht.begin();

  //Uhr starten
  rtc.begin();

  //Pins zuweisen
  pinMode(iMenue, INPUT);
  pinMode(iSet, INPUT);
  pinMode(iPlus, INPUT);
  pinMode(iMinus, INPUT);
  pinMode(oLcd, OUTPUT);
  pinMode(oSummer, OUTPUT);

  //Funk
  //printf_begin();
  radio.begin();
  radio.setChannel(25);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled

  // Open pipes to other nodes for communication
  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1, pipes[1]);

  // Start listening
  radio.startListening();

  // Dump the configuration of the rf unit for debugging
  //radio.printDetails();

  //LCD Library starten
  lcd.begin(20, 4);
  lcd.backlight();

  lcd.createChar(1, BaroUpUp);
  lcd.createChar(2, BaroUp);
  lcd.createChar(3, BaroUnchanged);
  lcd.createChar(4, BaroDown);
  lcd.createChar(5, BaroDownDown);
  lcd.createChar(6, BaroSun);
  lcd.createChar(7, BaroChangeable);
  lcd.createChar(8, BaroRain);
}

