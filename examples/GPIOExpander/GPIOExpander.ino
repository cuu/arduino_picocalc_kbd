#include <PCKeyboard.h>

#define CARD_DET 1

PCKeyboard keyboard;
int prevValue = LOW;

void setup()
{
  Serial.begin(9600);

  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();
  Wire.setClock(10000);

  keyboard.begin();
  keyboard.pinMode(CARD_DET, INPUT);
  keyboard.digitalWrite(CARD_DET, HIGH); // Enable pull-up
}

void loop()
{
  const int value = keyboard.digitalRead(CARD_DET);
  if (value == prevValue)
    return;

  Serial.printf("Card Detect: %d \r\n", value);

  prevValue = value;
}
