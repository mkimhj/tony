#include <Servo.h>
#include <uspeech.h>

signal voice(A0);
int time;
bool first =  true, process = false;
syllable s;

void left(){
  Serial.println("left(): called");
}
void right(){
  Serial.println("right(): called");
}
void center(){
  Serial.println("center(): called");
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  voice.f_enabled = false;
  voice.minVolume = 8000;
  voice.fconstant = 330;
  voice.econstant = 2;
  voice.aconstant = 3;
  voice.vconstant = 4;
  voice.shconstant = 12;
  voice.calibrate();
}

void loop() {
  // put your main code here, to run repeatedly: 
  char c = voice.getPhoneme();
  
  if(c==' '){
    if(process){
      int sum = s.f+s.o+s.v+s.s+s.h;
      if(sum>30){
        //[F, E, O, V, H, S]
        s.debugPrint();
        Serial.println();
        if (s.e > 10 && s.o > 20 && s.e > s.v && s.o > s.v) {
          Serial.println("Tony!");
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
