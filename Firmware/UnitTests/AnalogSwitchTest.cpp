#include "pch.h"
#include "CppUnitTest.h"

#include "ClearCore.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Mock class for DigitalInAnalogIn
class MockDigitalInAnalogIn : public DigitalInAnalogIn {
public:
    // Mock method for AnalogVoltage
    float AnalogVoltage() override {
        return mockAnalogVoltage;
    }

    // Mock method for Mode
    bool Mode(ConnectorModes newMode) override {
        return mockModeReturn;
    }

    // Mock values to be set in tests
    float mockAnalogVoltage;
    bool mockModeReturn;
};

#include "AnalogSwitch.h"

namespace AnalogSwitchTests
{
    TEST_CLASS(AnalogSwitchTests)
    {
    public:
        MockDigitalInAnalogIn mockAnalogInput;
        AnalogSwitch analogSwitch{ mockAnalogInput };

        TEST_METHOD_INITIALIZE(Initialize)
        {
            // Initialize the AnalogSwitch
            analogSwitch.Init();
        }

        TEST_METHOD(GetSwitchPosition_ReturnsNothing_WhenVoltageIs0)
        {
            mockAnalogInput.mockAnalogVoltage = 0.0f;

            Optional<int> position = analogSwitch.GetSwitchPosition();
            Assert::IsFalse(position.HasValue());
        }

        TEST_METHOD(GetSwitchPosition_Returns0_WhenVoltageIs2)
        {
            mockAnalogInput.mockAnalogVoltage = 2.0f;

            int position = analogSwitch.GetSwitchPosition();
            Assert::AreEqual(0, position);
        }

        TEST_METHOD(GetSwitchPosition_Returns1_WhenVoltageIs4)
        {
            mockAnalogInput.mockAnalogVoltage = 4.0f;

            int position = analogSwitch.GetSwitchPosition();
            Assert::AreEqual(1, position);
        }

        TEST_METHOD(GetSwitchPosition_Returns2_WhenVoltageIs6)
        {
            mockAnalogInput.mockAnalogVoltage = 6.0f;

            int position = analogSwitch.GetSwitchPosition();
            Assert::AreEqual(2, position);
        }

        TEST_METHOD(GetSwitchPosition_Returns3_WhenVoltageIs8)
        {
            mockAnalogInput.mockAnalogVoltage = 8.0f;

            int position = analogSwitch.GetSwitchPosition();
            Assert::AreEqual(3, position);
        }

        TEST_METHOD(GetSwitchPosition_ReturnsNothing_WhenVoltageIs10)
        {
            mockAnalogInput.mockAnalogVoltage = 10.0f;

            Optional<int> position = analogSwitch.GetSwitchPosition();
            Assert::IsFalse(position.HasValue());
        }

    };
}
