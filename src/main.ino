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


  if (PlusbuttonState != PluslastButtonState) {
    if (PlusbuttonState == LOW) {
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      Serial.println("off");
    }
    delay(100);
  }
  
  PluslastButtonState = PlusbuttonState;

  if (MinusbuttonState != MinuslastButtonState) {
    if (MinusbuttonState == LOW) {
      buttonPushCounter--;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      Serial.println("off");
    }
    delay(100);
  }
  MinuslastButtonState = MinusbuttonState;


  if (LightbuttonState != LightlastButtonState) {
    if (LightbuttonState == LOW) {
      digitalWrite(OvenLEDPin, HIGH);
      delay(1000);
      digitalWrite(OvenLEDPin, LOW);
    } else {
      Serial.println("off");
    }
    delay(100);
  }
  LightlastButtonState = LightbuttonState;


  display.showNumberDec(buttonPushCounter);
  
  if (buttonPushCounter % 4 == 0) {
    Serial.print(buttonPushCounter); 
    Serial.println("LED ON");
  } 

}