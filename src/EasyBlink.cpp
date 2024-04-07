#include <Arduino.h>
#include "EasyBlink.h"

/*
 * Resets all timers and state
 */
void EasyBlink::reset()
{
  m_blinkTime = 0UL;
  m_onForTime = -1;
  m_offForTime = -1;
  m_blinkState = BLINK_OFF;
  m_resolution = 20;
  m_blinkCount = -1;
  m_isBlinking = false;
}

/*
 * Constructor. Only needs to know what pin to blink.
 */
EasyBlink::EasyBlink(int pin)
{
  m_pin = pin;
  reset();
}

/*
 * Returns blinking state
 */
bool EasyBlink::isBlinking()
{
  return m_isBlinking;
}

/*
 * Sets amount of blink cycles
 */
void EasyBlink::setBlinkCount(int count)
{
  m_blinkCount = count;
}

/*
 * Sets the blink time ON
 */
void EasyBlink::setOnTime(int ms)
{
  if (ms > 0)
  { // no=op if ms is <= 0
    m_onForTime = ms;
    if (m_offForTime > 0)
    {
      m_resolution = min(m_onForTime, m_offForTime) / 10;
    }
  }
}

/*
 * Sets the blink time OFF
 */
void EasyBlink::setOffTime(int ms)
{
  if (ms > 0)
  { // no=op if ms is <= 0
    m_offForTime = ms;
    if (m_onForTime > 0)
    {
      m_resolution = min(m_onForTime, m_offForTime) / 10;
    }
  }
}

/*
 * Sets the blink state ON or OFF
 */
void EasyBlink::setBlinkState(blink_t state)
{
  digitalWrite(m_pin, (state == BLINK_ON) ? HIGH : LOW);
  m_blinkState = state;
  m_blinkTime = millis();
}

/*
 * Executes the blink. It allows to specify new on and off times. Use negative
 * values if you don't want to change what is already set.
 */

void EasyBlink::blink(int on_for, int off_for)
{
  m_isBlinking = true;
  setOnTime(on_for);
  setOffTime(off_for);
}

/*
 * Call often to blink.
 */
void EasyBlink::loop()
{
  if (m_blinkCount == 0 || !m_isBlinking)
  {
    return;
  }

  unsigned long ct = millis();
  if (m_blinkTime == 0UL)
    m_blinkTime = ct;
  unsigned long diff = abs((long long)ct - m_blinkTime);
  if (m_blinkState == BLINK_OFF)
  {
    if (m_offForTime > 0 && diff > m_offForTime)
    {
      setBlinkState(BLINK_ON);
    }
  }
  else
  {
    if (m_onForTime > 0 && diff > m_onForTime)
    {
      setBlinkState(BLINK_OFF);
      if (m_blinkCount > 0)
      {
        m_blinkCount--;
      }
    }
  }

  if (m_blinkCount == 0)
  {
    blinkOff();
  }
}

/*
 * Equivalent to delay(d), but updates the blink.
 */
void EasyBlink::blinkSync(int delayMs)
{
  unsigned long start = millis();
  while (millis() - start < delayMs)
  {
    Serial.println(m_blinkState);
    loop();
    delay(m_resolution);
  }
}

/*
 * Blink sync until count runs out
 */
void EasyBlink::blinkSync()
{
  if (m_blinkCount <= 0)
  {
    return;
  }
  while (m_blinkCount > 0)
  {
    loop();
    delay(m_resolution);
  }
}

/*
 * Turns off the blink.
 */
void EasyBlink::blinkOff()
{
  reset();
  digitalWrite(m_pin, LOW);
}
