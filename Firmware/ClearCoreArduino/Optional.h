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

#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <utility>
#include "Assert.h"

template <typename T>
class Optional {
public:
    // Default constructor
    Optional() : m_hasValue(false), m_value(T()) {}

    // Constructor with m_value
    Optional(const T& value) : m_hasValue(true), m_value(value) {}

    // Move constructor
    Optional(Optional&& other) noexcept : m_hasValue(other.m_hasValue), m_value(std::move(other.m_value)) {
        other.m_hasValue = false; // Set the source object to have no m_value
    }

    // Copy constructor
    Optional(const Optional& other) : m_hasValue(other.m_hasValue), m_value(other.m_value) {}

    // Assignment operator
    Optional& operator=(const T& value) {
        this->m_value = value;
        this->m_hasValue = true;
        return *this;
    }

    // Copy assignment operator
    Optional& operator=(const Optional& other) {
        if (this != &other) {
            m_hasValue = other.m_hasValue;
            m_value = other.m_value;
        }
        return *this;
    }

    // Move assignment operator
    Optional& operator=(Optional&& other) noexcept {
        if (this != &other) {
            m_hasValue = other.m_hasValue;
            m_value = std::move(other.m_value);
            other.m_hasValue = false; // Set the source object to have no m_value
        }
        return *this;
    }

    // Equality operator
    bool operator==(const Optional& other) const {
        if (m_hasValue != other.m_hasValue) {
            return false;
        }
        if (!m_hasValue) {
            return true;
        }
        return m_value == other.m_value;
    }

    // Inequality operator
    bool operator!=(const Optional& other) const {
        return !(*this == other);
    }

    // Reset method
    void Reset() {
        m_hasValue = false;
    }

    // Check if the Optional has a m_value
    bool HasValue() const {
        return m_hasValue;
    }

    // Get the m_value
    T Value() const {
		ASSERT(m_hasValue);
        return m_value;
    }

    // Conversion operator to automatically cast to the template type
    operator T() const {
		ASSERT(m_hasValue);
        return m_value;
    }

private:
    bool m_hasValue;
    T m_value;
};


#endif // OPTIONAL_H
