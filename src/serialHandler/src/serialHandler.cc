#include "serialHandler.h"

SerialHandler::SerialHandler(DataHandlerIf& dataHandlerIf) : m_dataHandlerIf(dataHandlerIf), m_commandState(CommandState::IDLE)
{
    //Baudrate doesn't matter as it's "emulated serial" trough USB,
    //and always runs at USB speeds (up to 480Mbits/s).
    Serial.begin(115200);
}

void SerialHandler::update()
{
    if (m_commandState == CommandState::IDLE)
    {
        while (Serial.available() > 0)
        {
            if (Serial.read() == '_')
            {
                Serial.read();
                m_commandState = CommandState::PARAMETER;
                break;
            }
        }
    }

    if (m_commandState == CommandState::PARAMETER)
    {
        if (Serial.available() >= PARAM_LENGTH)
        {
            m_parameter = getParameter();
            m_commandState = CommandState::DATA;
        }
    }

    if (m_commandState == CommandState::DATA)
    {
        if (Serial.available() >= DATA_LENGTH)
        {
            m_data = getData();
            m_dataHandlerIf.setParameter(static_cast<Parameter>(m_parameter), m_data);
            m_commandState = CommandState::IDLE;
        }
    }
}

uint32_t SerialHandler::getParameter() const
{
    char buffer[PARAM_LENGTH];
    Serial.readBytes(buffer, PARAM_LENGTH);
    return std::stoul(buffer);
}

float SerialHandler::getData() const
{
    char buffer[DATA_LENGTH];
    Serial.readBytes(buffer, DATA_LENGTH);
    return std::stof(buffer);
}
