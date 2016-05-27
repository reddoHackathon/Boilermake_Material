
// Anschlüsse
// Sensor  Arduino
// Vin     D3
// GND     G
// LED     D9

// Für die LEDs rot an 5V, schwarz an GND, grün an Digital Pin D3


///////////////////////////////////////////////////////////
//// Voreinstellungen
///////////////////////////////////////////////////////////

#include "FastLED.h"
#include "math.h"
#include "color_sensor.h"
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


#include <Wire.h>
#include "Adafruit_TCS34725.h"
#define powerPin 5    // über diesen Pin bekommt der Sensor seinen Strom
#define LED_PIN 9 // define D0 Sensor Interface
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
byte gammatable[256];
CRGB old_color, new_color;



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
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN,LOW); // LED off
  tcs.begin();

  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    gammatable[i] = x;      
  }

  
}


///////////////////////////////////////////////////////////
//// Hauptprogramm
///////////////////////////////////////////////////////////

void loop() {
  
  // Hier das Hauptprogramm des Sensors einfügen
  
  read_color();

  set_display_color();
  FastLED.show();
  


  
}


// Hier Funktionen des Sensors einfügen


void read_color()
{
  
  RGB_sensor_val sensor_reading_off, sensor_reading_on;
  
  float r, g, b;
  uint16_t max_val;

  Serial.println("read_color");

  digitalWrite(LED_PIN,LOW); // LED off

  sensor_reading_off=read_sensor_value(500);
  
  digitalWrite(LED_PIN,HIGH); // LED on  

  sensor_reading_on=read_sensor_value(500);

  digitalWrite(LED_PIN,LOW); // LED off
  
   Serial.println(sensor_reading_on.c);
   Serial.println(sensor_reading_off.c);

  if ((sensor_reading_off.c>sensor_reading_on.c)||(sensor_reading_on.c-sensor_reading_off.c<1000)) {
    new_color.r=0;
    new_color.g=0;
    new_color.b=0;
  }
  else {
    if (sensor_reading_on.r>sensor_reading_on.g) {
      max_val=sensor_reading_on.r;
    }
    else {
      max_val=sensor_reading_on.g;
    }
    if (sensor_reading_on.b>max_val) {
      max_val=sensor_reading_on.b;
    }
    
    r = sensor_reading_on.r; r /= max_val;
    g = sensor_reading_on.g; g /= max_val;
    b = sensor_reading_on.b; b /= max_val;
    r *= 255; g *= 255; b *= 255;
    
    new_color.r = gammatable[(int)r];
    new_color.g = gammatable[(int)g];
    new_color.b = gammatable[(int)b];
    
    Serial.print(new_color.r);
    Serial.print(' ');
    Serial.print(new_color.g);
    Serial.print(' ');
    Serial.println(new_color.b);
    
  }
}

RGB_sensor_val read_sensor_value(uint16_t delay_time)
{
  
uint16_t  red, green, blue, clear_val;
RGB_sensor_val sensor_struct;

  delay(delay_time);  // takes min 50ms to read 
  tcs.getRawData(&red, &green, &blue, &clear_val);
  sensor_struct.r=red;
  sensor_struct.g=green;
  sensor_struct.b=blue;
  sensor_struct.c=clear_val;
  
  return sensor_struct;
}


void set_display_color()
{
  for (int ct_x = 0; ct_x < NUM_LEDS; ct_x++)
  {
    leds[ct_x]=new_color;
  }
  mydata.r = leds[5].r;
  mydata.g = leds[5].g;
  mydata.b = leds[5].b;
  FastLED.show();
}



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
