#include <SPI.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "LowPower.h"

// Set up nRF24L01 radio on SPI bus plus pins 7 & 8
RF24 radio(8, 7);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

//Zähler für Watchdog pausen
int zaehler = 0;

//Baro
#include <Wire.h>
#include <Adafruit_MPL115A2.h>
Adafruit_MPL115A2 mpl115a2;

//TempFeuchte
#include <Arduino.h>
#include "Adafruit_SHT31.h"
Adafruit_SHT31 sht31 = Adafruit_SHT31();


//Sensoren Array
float sens[5];
//={Volt,BaroC,BaroKPA,Temp,Feuchte};

void setup() {

  //Stromsparoptionen
  ADCSRA = 0; // disable ADC
  power_adc_disable(); // ADC converter
  //power_spi_disable(); // SPI
  power_usart0_disable();// Serial (USART)
  //power_timer0_disable();// Timer 0
  power_timer1_disable();// Timer 1
  power_timer2_disable();// Timer 2
  //power_twi_disable(); // TWI (I2C)

  //Serial.begin(115200);
  //Für nrf23 config dump
  //printf_begin();

  //Nicht benötigte auf INPUT und LOW
  pinMode (2, INPUT);
  digitalWrite (2, LOW);
  pinMode (3, INPUT);
  digitalWrite (3, LOW);
  pinMode (4, INPUT);
  digitalWrite (4, LOW);
  pinMode (5, INPUT);
  digitalWrite (5, LOW);
  pinMode (10, INPUT);
  digitalWrite (10, LOW);
  pinMode (11, INPUT);
  digitalWrite (11, LOW);
  //Temp, Baro starten / Pin 6 ist für on/off
  pinMode (6, INPUT);
  digitalWrite (6, LOW);


  // Setup and configure rf radio
  radio.begin();
  radio.setChannel(25);
  //Datenrate senken
  radio.setDataRate(RF24_250KBPS);

  //Sendeleistung
  radio.setPALevel(RF24_PA_MAX);

  // Ensure autoACK is enabled
  radio.setAutoAck(1);
  //radio.setRetries(2,2);                  // (Pause*250,Wiederholungen)

  // Open pipes to other nodes for communication
  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)
  //  radio.openWritingPipe(pipes[0]); Empfänger
  //  radio.openReadingPipe(1,pipes[1]);Empfänger
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);

  // Start listening
  radio.startListening();

  // Dump the configuration of the rf unit for debugging
  //radio.printDetails();
}

void loop() {

  //Temp, Baro ausschalten  digitalWrite(6, LOW);
  radio.powerDown();

  //Daten erst nach x druchläufen senden zum Stromsparen
  if (zaehler > 31) {
    zaehler = 0;

    //Temp, Baro einschalten
    digitalWrite(6, HIGH);
    pinMode (6, OUTPUT);


    mpl115a2.begin();

    //sens[0] = getVolt();
    //Serial.print("Spannung (V): ");Serial.print (sens[0], 4); Serial.println(" V");

    sens[2] = mpl115a2.getPressure();
    //Serial.print("Pressure (kPa): "); Serial.print(sens[2], 4); Serial.println(" kPa");

    sens[1] = mpl115a2.getTemperature();
    //Serial.print("Temp (*C): "); Serial.print(sens[1], 1); Serial.println(" *C");

    
    
    sht31.begin(0x44);
    
    sens[3] = sht31.readTemperature();
    //Serial.print("Temp (*C): "); Serial.print(sens[3], 1); Serial.println(" *C");

    sens[4] = sht31.readHumidity();
    //Serial.print("Feuchte (%F): "); Serial.print(sens[4], 1); Serial.println(" %F");

    //Temp, Baro ausschalten
    //digitalWrite(6, LOW);
    pinMode (6, INPUT);
    digitalWrite (6, LOW);

    //Starte Sender
    radio.powerUp();                                // Power up the radio after sleeping
    radio.stopListening();                          // First, stop listening so we can talk.

    //unsigned long time = 1234;                  // Take the time, and send it.      millis()
    //Serial.print(F("Now sending... "));
    //Serial.println(sens[1]);
    //Serial.println(sens[2]);
    //radio.printDetails();
    radio.write( &sens, sizeof(sens) );


    radio.startListening();                         // Now, continue listening

    // Shut down the system
    delay(100);                     // Experiment with some delay here to see if it has an effect
    // Power down the radio.
    radio.powerDown();              // NOTE: The radio MUST be powered back up again manually

  }

  zaehler = zaehler + 1;


  // Sleep the MCU.
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}


const long InternalReferenceVoltage = 1062;  // Adjust this value to your board's specific internal BG voltage

// Code courtesy of "Coding Badly" and "Retrolefty" from the Arduino forum
// results are Vcc * 100
// So for example, 5V would be 500.
float getVolt ()
{
  power_adc_enable(); // ADC converter
  // REFS0 : Selects AVcc external reference
  // MUX3 MUX2 MUX1 : Selects 1.1V (VBG)
  ADMUX = bit (REFS0) | bit (MUX3) | bit (MUX2) | bit (MUX1);
  ADCSRA |= bit( ADSC );  // start conversion
  while (ADCSRA & bit (ADSC))
  { }  // wait for conversion to complete
  float results1 = (((InternalReferenceVoltage * 1024) / ADC) + 5);
  float results = results1 / 1000.0;
  power_adc_disable(); // ADC converter
  return results;
} // end of getBandgap
