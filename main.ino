#include "DigiKeyboard.h"


#define button_pin 0
#define AI_pin 2

bool flag = false;
bool statusBut;
unsigned long last_press = 0;
unsigned long x = 0;

const uint8_t size_array = 80;

char simbols[size_array] = {
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    'z', 'x', 'c', 'v', 'b', 'n', 'm',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M',
    '!', '@', '#', '$', '%', '^', '&', '*', '_', '-', '=', '+', '.', ',', '<', '>', ':', ';'};

void setup()
{
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.update();
  pinMode(button_pin, INPUT_PULLUP);
 
}

unsigned long number(unsigned long time, unsigned long time_press)
{
  unsigned long result;
  uint16_t ai = analogRead(AI_pin);
  if (ai < 255)
  {
    result = time + time_press;
  }
  else if (ai > 255 && ai < 510)
  {
    result = (unsigned long)abs((time / ai) + time_press);
  }
  else if (ai > 510 && ai < 765)
  {
    result = (unsigned long)abs(time + (time_press / ai));
  }
  else if (ai > 765)
  {
    result = abs(time - time_press);
  }

  return result;
}

void generate_password(unsigned long time, unsigned long time_press)
{
  // number(time, time_press);
  randomSeed(number(time, time_press));

  for (uint8_t i = 0; i < 8; i++)
  {
    DigiKeyboard.print(simbols[random(0, size_array - 1)]);
  }
  DigiKeyboard.println();
}

void loop()
{

  statusBut = digitalRead(button_pin);

  if (statusBut == false)
  { // && flag == false && millis() - last_press > 50)
    {
      flag = true;
      x++;
    }
  }

  if (statusBut == true && flag == true)
  {
    flag = false;
    // Serial.print("время нажатия: ");
    // Serial.println(x);
    // Serial.print("время работы: ");
    // Serial.println(millis());
    // Serial.println();
    generate_password(millis(), x);
    x = 0;
  }
}
