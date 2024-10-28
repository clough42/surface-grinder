// GrinderViewModel.h

#ifndef GRINDERVIEWMODEL_H
#define GRINDERVIEWMODEL_H

#include <cstdint>

class GrinderViewModel {

public:
	enum Axis {
		X,
		Y,
		Z
	};

    virtual ~GrinderViewModel() = default;
    virtual int32_t GetCurrentPositionNm(Axis axis) const = 0;
};

#endif // GRINDERVIEWMODEL_H
