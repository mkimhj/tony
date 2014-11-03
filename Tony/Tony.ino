#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <uspeech.h>

signal voice(A0);
int time;
bool first =  true, process = false;
syllable s;
bool areLightsOn = false;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 2, NEO_GRB + NEO_KHZ800);

void lightsOn() {
  for (int i =0; i < 16; i++) {
    strip.setPixelColor(i, strip.Color(255,255,255));
  }
  strip.show();
}

void lightsOff() {
  for (int i = 0; i < 16; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  voice.f_enabled = false;
  voice.minVolume = 5000;
  voice.fconstant = 330;
  voice.econstant = 3;
  voice.aconstant = 6;
  voice.vconstant = 5;
  voice.shconstant = 12;
  voice.calibrate();
  
  strip.begin();
  strip.show();
}

void loop() {
  // put your main code here, to run repeatedly: 
  char c = voice.getPhoneme();
//  Serial.println(c);
  if(c==' '){
    if(process){
      int sum = s.o+s.v+s.s+s.h+s.e;
      if(sum>30){
        //[F, E, O, V, H, S]
        s.debugPrint();
        if (s.o > s.e && s.e > 10 && s.e < 20 && s.f < s.e && s.v < s.e && s.h < s.e && s.s < s.e) {
          if (!areLightsOn) {
            lightsOn();
            areLightsOn = true;
           } else {
             lightsOff();
             areLightsOn = false;
           }
        }
      }
      s.f = 0;
      s.e = 0;
      s.o = 0;
      s.v = 0;
      s.s = 0;
      s.h = 0;
      process = false;
      
    }
  }
  else{
    if(first){
      time = millis();
    }
    else{
      
    }
    s.classify(c);
    process = true;
  }
}
