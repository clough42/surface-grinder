#ifndef COMMON_ENUMS_H
#define COMMON_ENUMS_H

// Direction of an axis or a DRO
enum Direction {
	NORMAL = 1,		// up/default
	REVERSE = -1	// down/reverse
};

enum Units {
	MILLIMETERS,
	INCHES
};

enum Axis {
	X,
	Y,
	Z
};


#endif // COMMON_ENUMS_H