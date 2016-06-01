# Interactive Lights
Das interaktive Schild wird von einem Raspberry PI mithilfe eines Fadecandy angesteuert.

## Ansteuerung des Schildes

## Installation des Servers auf dem PI
### Raspbian installieren
[https://www.raspberrypi.org/documentation/installation/installing-images/]()

### openFrameworks installieren
[http://openframeworks.cc/setup/raspberrypi/raspberry-pi-getting-started/]()

Kompilieren mit 4 Kernen aktivieren. Dazu ``sudo nano ~/.profile`` öffnen. Und in die letzte Zeile ``export MAKEFLAGS=-j4`` eintragen [(Link)](https://forum.openframeworks.cc/t/raspberry-pi-2-setup-guide-0-8-4/18690).

### Interactive Lights Server installieren


### Fadecandy Server installieren
```
git clone git://github.com/scanlime/fadecandy
cd fadecandy/server
make submodules
make
sudo mv fcserver ~/
```

### Autostart aktivieren

### Beispiele ausprobieren


## Workshop Hinweise 

### Software installieren
* Arduino Software von [https://www.arduino.cc/]() runterladen und installieren
* Workshop Repository runterladen [https://github.com/reddoHackathon/Boilermake_Material]() 
* Libraries von `Repository-Ordner/Arduino/libraries` in `Systembenutzerordner/Dokumente/Arduino/libraries` kopieren

### Beispiele ausprobieren


## Workshop Boilermake - Arduino

### Software installieren
* Arduino Software von [https://www.arduino.cc/]() runterladen und installieren
* Workshop Repository runterladen [https://github.com/reddoHackathon/Boilermake_Material]() 
* Libraries von `Repository-Ordner/Arduino/libraries` in `Systembenutzerordner/Dokumente/Arduino/libraries` kopieren


### Beispiele ausprobieren
Beispiele befinden sich in `Repository-Ordner/Arduino/examples` für die jeweiligen Sensortypen. Oben im Beispiel ist beschrieben wie der Sensor und das Herz an den Arduino angeschlossen werden.

#### LEDs ansteuern
Helligkeitswerte für rot, grün und blau (RGB) für jeden Pixel werden seriell in den LED Kreis geschickt. Prinzip Schieberegister. Jeder Pixel erzeugt die Signale für die LEDs.

Die Farbe der LEDs wird über drei Werte für RGB (jeweils Wert zwischen 0 und 255) definiert. Z.B. erreicht man gelb durch rot und grün gleicher Anteile:

```c
color_rgb.r=255; 
color_rgb.g=255; 
color_rgb.b=0;
```

Alternativ kann hue (Farbwert), saturation (Sättigung) und value (Helligkeit), [HSV](https://de.wikipedia.org/wiki/HSV-Farbraum) definiert werden und dann in RGB umgerechnet werden. Eignet sich gut für organische Fades zwischen Farben.

![alt text](https://github.com/reddoHackathon/Boilermake_Material/blob/master/pics/hsv.jpg "HSV")

#### Sensor auslesen
Analogen Eingang lesen (wird als 10 bit Wert ausgelesen)

`sensorValue = analogRead(A2);`

 
Wert weiterverarbeiten. 10 bit Zahl um 2 Stellen nach rechts verschieben → 8 bit Zahl

`sensorValue=sensorValue>>2;`

Die 8 bit Zahl (Werte zwischen 0 und 255) kann nun als Farbwert für den LED Streifen verwendet werden.  

```c
color.h=sensorValue;  // hue Wert der LEDs setzen (muss zwischen 0 und 255 liegen)
set_display_color_hsv();
```

#### Weitere hilfreiche Funktionen
Wertebereich auf neuen Wertebereich abbilden. Z.B. liefert das lesen eines analogen Eingangs am Arduino Werte zwischen 0 und 1023. Diese kann man z.B. auf Werte zwischen 100 und 200 mappen.

```c
sensorValue = map(sensorValue,0,1023,100,200);
```

If else Anweisung. Frage und Entscheidung. Wenn der Wert des Sensors größer ist als 100 tue etwas. Sonst tue etwas anderes. 

```c
if(sensorvalue > 100){
	//do something great
}else{
	//do something very awesome
}
```

Faden eines Pixels von schwarz zu blau mit Schleife. Die Pixel werden mit dem Array leds gesetzt. Dabei ist `leds[0]` der erste Pixel. Die Ausgabe an den LED Kreis erfolgt mit dem Befehl 
`FastLED.show();`

```c
for (int ct_fade = 0; ct_fade < 255; ct_fade++) {
  leds[0].b=ct_fade;
}
FastLED.show();  
```
