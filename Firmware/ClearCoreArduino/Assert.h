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
