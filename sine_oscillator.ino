#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>
#define CONTROL_PIN A0
#define CONTROL_RATE 128
Oscil <2048, AUDIO_RATE> aSin(SIN2048_DATA);

void setup(){
	startMozzi(CONTROL_RATE);
  pinMode(CONTROL_PIN, INPUT);
}

void updateControl(){
  int freqControl = analogRead(CONTROL_PIN);
  aSin.setFreq(440 + freqControl*5);
}

int updateAudio(){
	return aSin.next();
}

void loop(){
	audioHook();
}