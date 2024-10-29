// GrinderViewModel.h

#ifndef GRINDERVIEWMODEL_H
#define GRINDERVIEWMODEL_H

#include <cstdint>
#include "CommonEnums.h"

class GrinderViewModel {

public:
    virtual ~GrinderViewModel() = default;
    virtual int32_t GetCurrentPositionNm(Axis axis) const = 0;
};

#endif // GRINDERVIEWMODEL_H
