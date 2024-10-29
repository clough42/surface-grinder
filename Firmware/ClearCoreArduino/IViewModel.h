#ifndef IVIEWMODEL_H
#define IVIEWMODEL_H

#include <cstdint>
#include "CommonEnums.h"

// Model Interface for the View
//
// This interface defines the methods that the view can call on the model.
// These are separated out into a separate interface to make it harder for
// the view to accidentally call methods that it shouldn't.
class IViewModel {

public:
    virtual ~IViewModel() = default;
    virtual int32_t GetCurrentPositionNm(Axis axis) const = 0;
};

#endif // IVIEWMODEL_H
