// Copyright (c) 2004 James Clough (Clough42, LLC)
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

#ifndef MOCK_CLEARCORE_H
#define MOCK_CLEARCORE_H

class Connector {
public:
    enum ConnectorModes {
        INVALID_NONE,
        INPUT_ANALOG,
        INPUT_DIGITAL,
        OUTPUT_ANALOG,
        OUTPUT_DIGITAL,
        OUTPUT_H_BRIDGE,
        OUTPUT_PWM,
        OUTPUT_TONE,
        OUTPUT_WAVE,
        CPM_MODE_A_DIRECT_B_DIRECT,
        CPM_MODE_STEP_AND_DIR,
        CPM_MODE_A_DIRECT_B_PWM,
        CPM_MODE_A_PWM_B_PWM,
        TTL,
        RS232,
        SPI,
        CCIO,
        USB_CDC
    };

    enum ConnectorTypes {
        DIGITAL_IN_TYPE,
        DIGITAL_IN_OUT_TYPE,
        SHIFT_REG_TYPE,
        ANALOG_IN_DIGITAL_IN_TYPE,
        ANALOG_OUT_DIGITAL_IN_OUT_TYPE,
        H_BRIDGE_TYPE,
        CPM_TYPE,
        SERIAL_TYPE,
        SERIAL_USB_TYPE,
        CCIO_DIGITAL_IN_OUT_TYPE,
    };

    virtual ConnectorModes Mode() = 0;
    virtual bool Mode(ConnectorModes newMode) = 0;
    //virtual ConnectorTypes Type() = 0;
    //virtual bool IsWritable() = 0;
    //virtual void Refresh() = 0;
    //virtual void Initialize(ClearCorePins clearCorePin) = 0;
    //virtual int16_t State() = 0;
    //virtual bool State(int16_t newState) = 0;
    //virtual bool IsInHwFault() = 0;

    void Reinitialize() {}
    int32_t ConnectorIndex() { return 0; }
    uint32_t InputRegMask() { return 0; }
    virtual int8_t ExternalInterrupt() { return 0; }

    Connector() {}
};

class DigitalIn : public Connector {
};

class DigitalInAnalogIn : public DigitalIn {
public:
    static const uint16_t ANALOG_INPUT_FILTER_TC_MS_DEFAULT = 2;
    DigitalInAnalogIn() {}
    ConnectorModes Mode() override { return INPUT_ANALOG; }
    bool Mode(ConnectorModes newMode) override { return true; }
    virtual float AnalogVoltage() { return 0.0f; }
};

#endif // MOCK_CLEARCORE_H
