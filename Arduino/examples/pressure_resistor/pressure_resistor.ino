
// Anschlüsse
// Sensor    Arduino
// Braun     GND
// Rot      A2
// Orange    D5

// Für die LEDs rot an 5V, schwarz an GND, grün an Digital Pin D3


///////////////////////////////////////////////////////////
//// Voreinstellungen
///////////////////////////////////////////////////////////

#include "FastLED.h"
#include "math.h"
#define NUM_LEDS 12  // LED Anzahl
#define LED_BRIGHTNESS 255  // globale Helligkeit
#define DATA_PIN 3
CRGB leds[NUM_LEDS];
CHSV color;

#include <EasyTransfer.h>
struct RBG_SEND{
 byte r;
 byte g;
 byte b;
};
RBG_SEND mydata;
EasyTransfer ET;


// Hier Voreinstellungen für den Sensor einfügen


#define powerPin 5    // über diesen Pin bekommt der Sensor seinen Strom
#define sensorPinA A2 // Analoger Eingangspin an dem die Sensorspannung gemessen wird



///////////////////////////////////////////////////////////
// Setup wird nur einmal ausgeführt
///////////////////////////////////////////////////////////

void setup() {
 
  Serial.begin(9600); // Startet die serielle Verbindung zum PC
  ET.begin(details(mydata), &Serial);  // Serielle Verbindung zum großen Schild
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS); // LEDs initialisieren
  clear_display();  // alle LEDs ausmachen
  FastLED.show();   // Ausgabe an die LEDs

  color.s = 255;    // Sättigung erstmal auf voll
  color.v = LED_BRIGHTNESS; // Helligkeit auf den globalen Wert der oben definiert wurde
  
  // Hier setup für den Sensor einfügen

  pinMode(powerPin,OUTPUT);
  digitalWrite(powerPin,HIGH);


  
}


///////////////////////////////////////////////////////////
//// Hauptprogramm
///////////////////////////////////////////////////////////

void loop() {
  
  // Hier das Hauptprogramm des Sensors einfügen
  


  int sensorValue = 0;  // variable to store the value coming from the sensor

  // Sensor auslesen und über 10 Werte glätten
  int averages=10;
  sensorValue = analogRead(sensorPinA);
  for(int ct_av=1;ct_av<averages;ct_av++) {
    sensorValue = sensorValue+analogRead(sensorPinA);
  }
  sensorValue=sensorValue/40; // aufbereiten der Daten für die Ausgabe als Farbwert
  
  Serial.print(sensorValue); // Ausgabe an den PC
  Serial.print(' '); // Ausgabe an den PC
  Serial.println(sensorValue); // Ausgabe an den PC
  
  color.h=sensorValue;  // hue Wert der LEDs setzen (sollte zwischen 0 und 255 liegen)
  set_display_color_hsv();


  // Diese Zeile auskommentieren wenn an das große Schild gesendet werden soll
  // ET.sendData(); 

  
}


// Hier Funktionen des Sensors einfügen







///////////////////////////////////////////////////////////
//// Vorbereitete Funktionen
///////////////////////////////////////////////////////////

void clear_display()
{
  int ct_led;

  for (int ct_x = 0; ct_x < NUM_LEDS; ct_x++)
  {
    leds[ct_x] = CRGB::Black;
  }
}

void set_display_color_hsv() 
{
  //hsv2rgb_rainbow(color,mydata.color);
  for (int ct_x = 0; ct_x < NUM_LEDS; ct_x++)
  {
    hsv2rgb_rainbow(color,leds[ct_x]);
  }
  mydata.r = leds[5].r;
  mydata.g = leds[5].g;
  mydata.b = leds[5].b;
  FastLED.show();
}

