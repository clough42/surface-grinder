#ifndef COMMON_ENUMS_H
#define COMMON_ENUMS_H

// Direction of an axis or a DRO
enum class Direction {
	NORMAL = 1,		// up/default
	REVERSE = -1	// down/reverse
};

enum class Units {
	MILLIMETERS,
	INCHES
};

enum class Axis {
	X = 0,
	Y = 1,
	Z = 2,
	NONE = -1
};




#endif // COMMON_ENUMS_H