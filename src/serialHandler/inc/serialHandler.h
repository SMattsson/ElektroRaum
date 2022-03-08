#pragma once
#include "arduinoLib.h"
#include "dataHandlerIf.h"

class SerialHandler
{
public:
    SerialHandler(DataHandlerIf& dataHandlerIf);
    virtual void update();

protected:
    uint32_t getParameter() const;
    float getData() const;
    enum class CommandState {IDLE, PARAMETER, DATA};

private:
    DataHandlerIf& m_dataHandlerIf;
    CommandState m_commandState;
    uint32_t m_parameter;
    float m_data;
    static constexpr int32_t PARAM_LENGTH{4};
    static constexpr int32_t DATA_LENGTH{8};
};