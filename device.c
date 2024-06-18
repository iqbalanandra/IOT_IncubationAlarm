// #define BLYNK_TEMPLATE_ID "TMPL64PCroLaO"
// #define BLYNK_TEMPLATE_NAME "IoT Garden Monitoring System"
// #define BLYNK_AUTH_TOKEN "rXyRWWBunZ95j7BEK7JZTVmWGiw9hJkK"
// #define BLYNK_PRINT Serial

#include <WiFiClient.h>
// #include <ESP8266WiFi.h>
// #include <BlynkSimpleEsp8266.h>
#include <WiFi.h>
#include <DHT.h>

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int pinledR = 15;
int pinledY = 13;
DHT dht(14, DHT22);
int buzz = 5;

int melody[] = {
  395, 330, 349, 395, 395, 330, 523, 523, 494, 523, 440, 395, 330, 395, 349, 330, 294, 262, 294,
  395, 330, 349, 395, 395, 330, 523, 523, 494, 523, 440, 395, 330, 349, 330, 294, 262, 294, 262,
  262, 294, 330, 262, 395, 330, 523, 440, 440, 395, 349, 395, 395, 523, 395, 587,
  395, 659, 587, 523, 494, 523, 494, 440, 395, 330, 349, 294, 330, 294, 262
};

int noteDurations[] = {
  485, 835, 350, 385, 885, 475, 410, 430, 425, 410, 490, 920, 435, 435, 365, 435, 460, 470, 1370,
  480, 900, 430, 405, 860, 495, 440, 410, 500, 425, 385, 1000, 400, 465, 450, 445, 455, 450, 1365,
  440, 875, 450, 465, 880, 440, 435, 420, 430, 405, 510, 1375, 405, 1420, 415, 1045,
  430, 400, 425, 455, 425, 1150, 475, 475, 415, 445, 450, 495, 1730, 1825, 1765
};

void playMelody() {
  int songLength = sizeof(melody) / sizeof(melody[0]);
  for (int thisNote = 0; thisNote < songLength; thisNote++) {
    tone(buzz, melody[thisNote]);
    delay(noteDurations[thisNote]);
    noTone(buzz);
    delay(50);
  }
}


void sendSensor(){
  float temp = dht.readTemperature();
  
  Serial.println(temp);
  if(temp <= 39 && temp >= 33){
      digitalWrite(pinledR, LOW);
      digitalWrite(pinledY, HIGH);
      noTone(buzz);
      Serial.println("Temperature Normal untuk Inkubasi");
      // Blynk.virtualWrite(V1, temp);
      // Blynk.virtualWrite(V0, 1);
      // Blynk.virtualWrite(V2, 0);
  }else{
      digitalWrite(pinledR, HIGH);
      digitalWrite(pinledY, LOW);
      Serial.println("Temperature tidak normal!");
      playMelody(); 
      // Blynk.virtualWrite(V1, temp);
      // Blynk.virtualWrite(V0, 0);
      // Blynk.virtualWrite(V2, 1);
  }

  // Blynk.virtualWrite(V3, temp);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Hello, ESP8266!");
  pinMode(pinledR, OUTPUT);
  pinMode(pinledY, OUTPUT);
  pinMode(buzz, OUTPUT);
  // Blynk.begin(auth, ssid, pass);
  dht.begin();
}

void loop() {
  delay(1000);
  // Blynk.run();
  sendSensor();
}
