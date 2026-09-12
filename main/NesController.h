#pragma once

#include <Arduino.h>
#include "NesButtons.h"

namespace
{
    constexpr uint8_t LatchPin = 2;
    constexpr uint8_t ClockPin = 3;
    constexpr uint8_t DataPin  = 4;

    // Latch pulse timing in ms
    constexpr unsigned int LatchPulseTime = 12;
    constexpr unsigned int ClockPulseTime = LatchPulseTime / 2;
}


class NesController
{
    public:
    void begin() const
    {
        pinMode(LatchPin, OUTPUT);
        pinMode(ClockPin, OUTPUT);
        pinMode(DataPin, INPUT);
        digitalWrite(LatchPin, LOW);
        digitalWrite(ClockPin, LOW);
    }


    NesButtons read() const
    {
        bool pressed[NesButtons::Count];

        digitalWrite(LatchPin, HIGH);
        delayMicroseconds(LatchPulseTime);
        digitalWrite(LatchPin, LOW);

        for (uint8_t i = 0; i < NesButtons::Count; ++i)
        {
            pressed[i] = (digitalRead(DataPin) == LOW);

            delayMicroseconds(ClockPulseTime);
            digitalWrite(ClockPin, HIGH);
            delayMicroseconds(ClockPulseTime);
            digitalWrite(ClockPin, LOW);
        }

        NesButtons buttons(pressed);

        return buttons;
    }
};
