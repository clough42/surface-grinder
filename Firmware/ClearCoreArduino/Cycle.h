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

#ifndef CYCLE_H
#define CYCLE_H

#include "CommonEnums.h"

class Cycle {
public:
	Cycle(Mode forMode) : m_forMode(forMode) {}

	bool IsForMode(Mode mode) {
		return m_forMode == mode;
	}

    /// <summary>
    /// Reset the cycle and get it ready to start again
    /// </summary>
    virtual void Reset() = 0;

    /// <summary>
	/// Call repeatedly to perform the cycle's operation
    /// </summary>
    /// <returns>true if more steps remain (cycle is not done)</returns>
    virtual bool Update() = 0;

	/// <summary>
	/// Returns true if the cycle is in an error state
	/// </summary>
	virtual bool IsInError() = 0;

private:
    Mode m_forMode;

};

#endif // CYCLE_H