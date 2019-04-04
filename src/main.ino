#include <Arduino.h>
#include <TM1637Display.h>

const uint8_t SEG_BEEP[] = {
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, // B
    SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,                 // E
    SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,                 // E
    SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,                 // P
};

const int PlusbuttonPin = 12;
const int MinusbuttonPin = 11;
const int ToggleTimerbuttonPin = 10;
const int OvenLEDPin = 9;

const int CLK = 8;
const int DIO = 7;

int buttonPushCounter = 0;

int PlusbuttonState = 0;
int PluslastButtonState = 0;

int MinusbuttonState = 0;
int MinuslastButtonState = 0;

int ToggleTimerbuttonState = 0;
int ToggleTimerlastButtonState = 0;

unsigned long previousMillis = 0;  

bool isTimerEnabled = false;

TM1637Display display(CLK, DIO);

void setup() {
  pinMode(PlusbuttonPin, INPUT_PULLUP);
  pinMode(MinusbuttonPin, INPUT_PULLUP);
  pinMode(ToggleTimerbuttonPin, INPUT_PULLUP);


  pinMode(OvenLEDPin, OUTPUT);

  display.setBrightness(0x0a); 

  Serial.begin(9600);
}


void ShowBeep(void)
{ 
  for(int i=0; i < 5; i++) {
    display.setSegments(SEG_BEEP);
    delay(1000);
    display.clear();
    delay(500);
  }
}



void loop() {
  PlusbuttonState = digitalRead(PlusbuttonPin);
  MinusbuttonState = digitalRead(MinusbuttonPin);
  ToggleTimerbuttonState = digitalRead(ToggleTimerbuttonPin);


  if (PlusbuttonState != PluslastButtonState && PlusbuttonState == LOW) {
    buttonPushCounter++;
  }
  PluslastButtonState = PlusbuttonState;


  if (MinusbuttonState != MinuslastButtonState && MinusbuttonState == LOW) {
    buttonPushCounter--;
  }
  MinuslastButtonState = MinusbuttonState;


  if (ToggleTimerbuttonState != ToggleTimerlastButtonState && ToggleTimerbuttonState == LOW) {
    isTimerEnabled = !isTimerEnabled;
  }
  ToggleTimerlastButtonState = ToggleTimerbuttonState;


  if(millis() - previousMillis > 1000) {
    previousMillis = millis();

    if (isTimerEnabled) {
      buttonPushCounter--;
    }

    if (buttonPushCounter == 0 && isTimerEnabled) {
      ShowBeep();
    }

    if (buttonPushCounter == 0) {
      isTimerEnabled = false;
    }
  }


  display.showNumberDecEx(buttonPushCounter, 0b01000000, true);
}
