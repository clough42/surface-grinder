// Copyright (c) 2024 James Clough (Clough42, LLC)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#ifndef ANALOG_SWITCH_H
#define ANALOG_SWITCH_H

#include "ClearCore.h"
#include "Optional.h"

class AnalogSwitch {
public:
    // Constructor that takes a reference to an analog input
    AnalogSwitch(DigitalInAnalogIn& analogInput) : m_analogInput(analogInput) {}

    void Init() {
        m_analogInput.Mode(Connector::INPUT_ANALOG);
    }

    // Method to get the current switch position
    Optional<int> GetSwitchPosition() {
        float voltage = m_analogInput.AnalogVoltage();
        if (voltage < 1) {
            return Optional<int>(); // no value
        } else if (voltage < 3) {
            return 0;
        } else if (voltage < 5) {
            return 1;
        } else if (voltage < 7) {
            return 2;
        } else if (voltage < 9) {
            return 3;
        }
        else {
            return Optional<int>(); // no value
        }
    }

private:
    DigitalInAnalogIn& m_analogInput;
};

#endif // ANALOG_SWITCH_H
