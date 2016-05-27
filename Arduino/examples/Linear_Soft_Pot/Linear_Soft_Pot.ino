
// Anschlüsse
// Sensor    Arduino
// Schwarz   G
// Weiß      A2
// Grau      D5

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

  sensorValue = analogRead(sensorPinA);
  Serial.print(sensorValue);  // Ausgabe des eingelesenen Wertes an den PC
  
  if (sensorValue>1000) {
    sensorValue=0;
  }
  
  sensorValue = map(sensorValue,0,1000,0,255);

  Serial.print(' ');
  Serial.println(sensorValue);  // Ausgabe des gemappten Wertes an den PC

  if (sensorValue) {
    color.v=LED_BRIGHTNESS;
  }
  else {
    color.v=0;    
  }
  
    
  
  color.h=sensorValue;  // hue Wert der LEDs setzen (sollte zwischen 0 und 255 liegen)
  set_display_color_hsv();

  // Diese Zeile auskommentieren wenn an das große Schild gesendet werden soll
  //ET.sendData(); 

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

