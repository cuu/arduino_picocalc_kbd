#include <PCKeyboard.h>

PCKeyboard keyboard;
volatile bool dataReady = false;

const int interruptPin = 5;

void KeyIsr(void)
{
  dataReady = true;
}

void setup()
{
  Serial.begin(9600);
  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();
  Wire.setClock(10000);

  keyboard.begin();
  keyboard.attachInterrupt(interruptPin, KeyIsr);
  keyboard.setBacklight(0.5f);
}

void loop()
{
  if (!dataReady)
    return;

  const PCKeyboard::KeyEvent key = keyboard.keyEvent();
  String state = "pressed";
  if (key.state == PCKeyboard::StateLongPress)
    state = "held down";
  else if (key.state == PCKeyboard::StateRelease)
    state = "released";

  Serial.printf("key: '%c' (dec %d, hex %02x) %s\r\n", key.key, key.key, key.key, state.c_str());

  // pressing 'b' turns off the backlight and pressing Shift+b turns it on
  if (key.state == PCKeyboard::StatePress) {
    if (key.key == 'b') {
      keyboard.setBacklight(0);
    } else if (key.key == 'B') {
      keyboard.setBacklight(1.0);
    }
  }

  keyboard.clearInterruptStatus();
  dataReady = false;
}
