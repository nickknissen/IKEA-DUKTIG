#include <Arduino.h>
#include <TM1637Display.h>

const int PlusbuttonPin = 12;
const int MinusbuttonPin = 11;
const int LightbuttonPin = 10;
const int OvenLEDPin = 9;

const int CLK = 8;
const int DIO = 7;

int buttonPushCounter = 0;

int PlusbuttonState = 0;
int PluslastButtonState = 0;

int MinusbuttonState = 0;
int MinuslastButtonState = 0;

int LightbuttonState = 0;
int LightlastButtonState = 0;


TM1637Display display(CLK, DIO);

void setup() {
  pinMode(PlusbuttonPin, INPUT_PULLUP);
  pinMode(MinusbuttonPin, INPUT_PULLUP);
  pinMode(LightbuttonPin, INPUT_PULLUP);


  pinMode(OvenLEDPin, OUTPUT);

  display.setBrightness(0x0a); 

  Serial.begin(9600);
}



void loop() {
  PlusbuttonState = digitalRead(PlusbuttonPin);
  MinusbuttonState = digitalRead(MinusbuttonPin);
  LightbuttonState = digitalRead(LightbuttonPin);


  if (PlusbuttonState != PluslastButtonState && PlusbuttonState == LOW) {
    buttonPushCounter++;
  }
  
  PluslastButtonState = PlusbuttonState;


  if (MinusbuttonState != MinuslastButtonState && MinusbuttonState == LOW) {
    buttonPushCounter--;
  }
  MinuslastButtonState = MinusbuttonState;


  if (LightbuttonState != LightlastButtonState && LightbuttonState == LOW) {
    digitalWrite(OvenLEDPin, HIGH);
    delay(1000);
    digitalWrite(OvenLEDPin, LOW);
  }
  LightlastButtonState = LightbuttonState;


  display.showNumberDec(buttonPushCounter);
}