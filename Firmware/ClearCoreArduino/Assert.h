#ifndef ASSERT_H
#define ASSERT_H

#ifndef _UNIT_TEST
#include <Arduino.h>

class Assert {
public:
    // Method to check a condition and print an error message if the condition is false
    static void Check(bool condition, const char* message, const char* file, int line) {
        if (!condition) {
            Serial.print("Assertion failed: ");
            Serial.print(message);
            Serial.print(" in file ");
            Serial.print(file);
            Serial.print(" at line ");
            Serial.println(line);
            // Optionally, you can halt the program execution
            while (true) {}
        }
    }
};

// Macro to simplify the usage of the assert class
#define ASSERT(condition) Assert::Check((condition), #condition, __FILE__, __LINE__)
#else // _UNIT_TEST

#define ASSERT(condition) ;

#endif // _UNIT_TEST


#endif // ASSERT_H
