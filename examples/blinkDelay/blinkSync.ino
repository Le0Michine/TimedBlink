/*
 * EasyBlink blink delay sample
 *
 * Makes the built-in LED blink. 200ms ON and 100ms OFF.
 *
 * created January 14, 2017
 * by Lorenzo Pasqualis
 *
 * This example code is in the public domain.
 */

#include <EasyBlink.h>

EasyBlink monitor(LED_BUILTIN);

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  monitor.blink(100, 300);
  monitor.setBlinkCount(5);
  Serial.println("Blink 5 times when setup is doen");
  monitor.blinkSync();
}

void loop()
{
  Serial.println("Waiting 3 seconds and blinking the LED at the same time...");
  monitor.blinkSync(3000);
}
