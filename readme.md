# Interactive Lights
Das interaktive Schild wird von einem Raspberry PI mithilfe eines Fadecandy angesteuert.

**Inhalt**

* [Ansteuerung des Schildes](https://github.com/reddoHackathon/Boilermake_Material#ansteuerung-des-schildes)
* [Interactive Light Server selbst einrichten](https://github.com/reddoHackathon/Boilermake_Material#interactive-light-server-selbst-einrichten)
* [Workshop Boilermake - Arduino](https://github.com/reddoHackathon/Boilermake_Material#workshop-boilermake---arduino)


## Ansteuerung des Schildes
Generell kann das Schild per TCP über das [Open Pixel Control](http://openpixelcontrol.org/) Protokoll angesprochen werden. 

Der Server kommuniziert auf `Port 11999` mit der entsprechenden IP des PI (siehe DHCP).

### Beispielsoftware openFrameworks
Im Repository existieren Beispiele für [openFrameworks](http://openframeworks.cc/). OpenFrameworks kann unter [http://openframeworks.cc/download/]() für etliche Plattformen herunter geladen werden.

Um die Beispiele zu starten wird der Ordner `ofxOPC` im Repository in `openFrameworks` nach `[of-Verzeichnis]/addons` kopiert. In `ofxOPC/examples` befinden sich Beispiele. Um diese auszuführen muss man ein Projekt im Projektgenerator erstellen und folgende Addons hinzufügen:

* ofxOPC
* ofxNetwork

### Andere Entwicklungsumgebungen
Da der Server das OPC Protokoll implementiert, kann er von beliebigen Platformen angesprochen werden. Eine Menge Beispiele für andere Entwicklungsumgungen (Processing, ..) befinden sich im [Fadecandy Repository](https://github.com/scanlime/fadecandy).

Das Herz hat ein eigenes Mapping, welches separat implementiert werden muss:

```javascript
/*
x0y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  
x1y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  
x2y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  
x3y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  
x4y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  
x5y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  
x6y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  
x7y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  
x8y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  
x9y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19 
x10y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19 
x11y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19 
x12y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19 
x13y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19 
x14y0 	1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19
*/

//mapping zum index der LED auf Steifen, 255 bedeutet Pixel nicht vorhanden
const u_int8_t coordinate2index[] = {  
255, 255, 255, 41,  42,  43, 44,  45, 46,   47, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255,  40,  39, 38,  37,  36, 35,  34, 33,   32,  31, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
 18,  19,  20, 21,  22,  23, 24,  25, 26,   27,  28,  29,  30, 255, 255, 255, 255, 255, 255, 255, 
 17,  16,  15, 14,  13,  12, 11, 255, 24,   23,  22,  21,  20,  19, 255, 255, 255, 255, 255, 255,  
  6,   7,   8,  9,  10, 255, 10,  11, 12,   13,  14,  15,  16,  17,  18, 255, 255, 255, 255, 255,
  5,   4,   3,  2, 255, 255,  9,   8,  7,    6,   5,   4,   3,   2, 255,   1,   0, 255, 255, 255, 
255,   1,   0,  0, 255,   3,  2,   1,  0,  255,   1,   0, 255,   2,   3,   4,   5,   6,   7, 255, 
255, 255,   2,  1, 255,   4,  5,   6,  7,    8,   9, 255,  15,  14,  13,  12,  11,  10,   9,   8, 
255,   1,   0,  3, 255,  13, 12,  11,  10, 255,   1,   0, 255,  16,  17,  18,  19,  20,  21, 255, 
  5,   4,   3,  2, 255, 255,  9,   8,   7,   6,   5,   4,   3,   2, 255,  23,  22, 255, 255, 255,  
  6,   7,   8,  9,  10, 255, 10,  11,  12,  13,  14,  15,  16,  17,  18, 255, 255, 255, 255, 255, 
 17,  16,  15, 14,  13,  12, 11, 255,  24,  23,  22,  21,  20,  19, 255, 255, 255, 255, 255, 255, 
 18,  19,  20, 21,  22,  23, 24,  25,  26,  27,  28,  29,  30, 255, 255, 255, 255, 255, 255, 255, 
255,  40,  39, 38,  37,  36, 35,  34,  33,  32,  31, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
255, 255, 255, 41, 42, 43, 44, 45, 46, 47, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
};

//mapping der LED zum jeweiligen Streifen, 255 bedeutet Pixel nicht vorhanden
const u_int8_t coordinate2sector[] ={  
255,255,255,  5,  5,  5,  5,  5,  5,  5,255,255,255,255,255,255,255,255,255,255, 
255,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,255,255,255,255,255,255,255,255,255,  
  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,255,255,255,255,255,255,255,
  5,  5,  5,  5,  5,  5,  5,255,  2,  2,  2,  2,  2,  2,255,255,255,255,255,255,
  5,  5,  5,  5,  5,255,  2,  2,  2,  2,  2,  2,  2,  2,  2,255,255,255,255,255,  
  5,  5,  5,  5,255,255,  2,  2,  2,  2,  2,  2,  2,  2,255,  4,  4,255,255,255,
255,  5,  5,  7,255,  0,  0,  0,  0,255,  2,  2,255,  4,  4,  4,  4,  4,  4,255,
255,255,  7,  7,255,  0,  0,  0,  0,  0,  0,255,  4,  4,  4,  4,  4,  4,  4,  4,
255,  6,  6,  7,255,  0,  0,  0,  0,255,  3,  3,255,  4,  4,  4,  4,  4,  4,255,
  6,  6,  6,  6,255,255,  3,  3,  3,  3,  3,  3,  3,  3,255,  4,  4,255,255,255, 
  6,  6,  6,  6,  6,255,  3,  3,  3,  3,  3,  3,  3,  3,  3,255,255,255,255,255, 
  6,  6,  6,  6,  6,  6,  6,255,  3,  3,  3,  3,  3,  3,255,255,255,255,255,255, 
  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,255,255,255,255,255,255,255,
255,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,255,255,255,255,255,255,255,255,255,
255,255,255,  6,  6,  6,  6,  6,  6,  6,255,255,255,255,255,255,255,255,255,255
};
```
 


## Interactive Light Server selbst einrichten
Die Anleitung zum aufsetzen eines eigenen Interactive Light Servers

### Raspbian installieren
[https://www.raspberrypi.org/documentation/installation/installing-images/]()

### Interactive Lights Server installieren
Server runterladen und ins home-Verzeichnis entpacken

```
git clone https://github.com/reddoHackathon/Boilermake_Material.git
cd Boilermake_Material/server/
unzip piServer.zip -d ~/
```

### Fadecandy Server installieren
Fadecandy server runterladen, kompilieren und ins home-Verzeichnis kopieren

```
git clone git://github.com/scanlime/fadecandy
cd fadecandy/server
make submodules
make
sudo mv fcserver ~/
```

### Autostart aktivieren
Autostart Skript ins home-Verzeichnis kopieren

```
git clone https://github.com/reddoHackathon/Boilermake_Material.git
cd Boilermake_Material/server/
mv autostart_fcserver.sh ~/
```

Skript in rc.local hinzufügen `sudo nano /etc/rc.local`

In Zeile vor `exit 0` folgendes eintragen [(siehe Link)](http://www.netzmafia.de/skripten/hardware/RasPi/RasPi_Auto.html) 

```
sh /home/pi/autostart_fcserver.sh
```


### Selbst kompilieren
Alternativ kann man den Server auch selbst kompilieren.

openFrameworks installieren.
[http://openframeworks.cc/setup/raspberrypi/raspberry-pi-getting-started/]()

Kompilieren mit 4 Kernen aktivieren. Dazu ``sudo nano ~/.profile`` öffnen. Und in die letzte Zeile ``export MAKEFLAGS=-j4`` eintragen [(Link)](https://forum.openframeworks.cc/t/raspberry-pi-2-setup-guide-0-8-4/18690).

Der Servercode befindet sich im Repository.

```
git clone https://github.com/reddoHackathon/Boilermake_Material.git
cd Boilermake_Material/openFrameworks/
mv ofxOPC ~/[ofPfad]/addons
cd ~/[ofPfad]/addons/ofxOPC
mv examples ~/[ofPfad]/apps
cd ~/[ofPfad]/apps/examples/client_idle_animation
make
make RunRelease
```


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
