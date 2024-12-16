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

#ifndef COMMON_ENUMS_H
#define COMMON_ENUMS_H

// Direction of an axis or a DRO
enum class Direction {
	POSITIVE = 1,	// up/default
	NEGATIVE = -1	// down/reverse
};

enum class Units {
	MILLIMETERS,
	INCHES
};

enum class Axis {
	X, // 0
	Y, // 1
	Z, // 2
	COUNT
};
#define AXIS_X static_cast<int>(Axis::X)
#define AXIS_Y static_cast<int>(Axis::Y)
#define AXIS_Z static_cast<int>(Axis::Z)
#define AXIS_COUNT static_cast<int>(Axis::COUNT)

enum class Mode {
	SETUP,		// 0
	FLAT,		// 1
	SIDE,		// 2
	END,		// 3
	CYLINDER,	// 4	
	DRESS,		// 5		
	COUNT
};
#define MODE_COUNT static_cast<int>(Mode::COUNT)

enum class Status {
	IDLE,		// 0
	RUN,		// 1
	HOLD,		// 2
	ESTOP,		// 3
	COUNT
};
#define STATUS_COUNT static_cast<int>(Status::COUNT)

#endif // COMMON_ENUMS_H