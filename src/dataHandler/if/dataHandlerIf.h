#pragma once

#include <stdint.h>
#include <optional>
#include "soundEngineDefs.h"

class DataHandlerIf
{
public:
    virtual ~DataHandlerIf(){};
    virtual void setParameter(const Parameter parameter, const float data) = 0;
    virtual std::optional<float> getParameter(const Parameter parameter) = 0;
};
