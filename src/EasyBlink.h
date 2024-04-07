#ifndef __EasyBlink__H__
#define __EasyBlink__H__

#include <Arduino.h>

enum blink_t {BLINK_ON, BLINK_OFF};

class EasyBlink {
  private:
    unsigned long m_blinkTime;
    int m_onForTime;
    int m_offForTime;
    blink_t m_blinkState;
    short m_pin;
    int m_resolution;
    int m_blinkCount;
    bool m_isBlinking;

    void reset();

  public:

    EasyBlink(int pin);
    void blink(int on_for, int off_for);
    void loop();
    void setBlinkCount(int count);
    void setOnTime(int ms);
    void setOffTime(int ms);
    void setBlinkState(blink_t state);
    void blinkSync(int delayMs);
    void blinkSync();
    void blinkOff();
    bool isBlinking();
};

#endif // __EasyBlink__H__
