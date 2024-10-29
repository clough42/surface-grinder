#ifndef IVIEWMODEL_H
#define IVIEWMODEL_H

#include <cstdint>
#include "CommonEnums.h"

class IViewModel {

public:
    virtual ~IViewModel() = default;
    virtual int32_t GetCurrentPositionNm(Axis axis) const = 0;
};

#endif // IVIEWMODEL_H
