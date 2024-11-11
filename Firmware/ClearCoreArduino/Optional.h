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

template <typename T>
class Optional {
public:
    Optional() : m_hasValue(false) {}
    Optional(const T& value) : m_value(value), m_hasValue(true) {}
    Optional(T&& value) : m_value(std::move(value)), m_hasValue(true) {}

    // Auto cast to the template type
    operator T() const {
        return m_value;
    }

    // Auto cast from the template type
    Optional& operator=(const T& value) {
        m_value = value;
        m_hasValue = true;
        return *this;
    }

    Optional& operator=(T&& value) {
        m_value = std::move(value);
        m_hasValue = true;
        return *this;
    }

    // Implicit cast to bool to check if a value is present
    operator bool() const {
        return m_hasValue;
    }

    // Implicit conversion to the stored value
    operator T&() {
        return m_value;
    }

    // Implicit conversion to the stored value (const version)
    operator const T&() const {
        return m_value;
    }

    void reset() {
        m_hasValue = false;
    }

private:
    T m_value;
    bool m_hasValue;
};

#endif // OPTIONAL_H
