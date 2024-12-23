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

#ifndef LIMITER_H
#define LIMITER_H

template <typename T>
class Limiter {
    
public:
    Limiter(T limit1, T limit2) :
        m_lowerLimit(Limiter::_min(limit1, limit2)),
        m_upperLimit(Limiter::_max(limit1, limit2)) {}

    T Clamp(T value) const {
        if (value < m_lowerLimit) {
            return m_lowerLimit;
        }
        if (value > m_upperLimit) {
            return m_upperLimit;
        }
        return value;
    }

private:
    T m_lowerLimit;
    T m_upperLimit;

    T _min(T a, T b) const {
        return (a < b) ? a : b;
    }

    T _max(T a, T b) const {
        return (a > b) ? a : b;
    }

};

#endif // LIMITER_H