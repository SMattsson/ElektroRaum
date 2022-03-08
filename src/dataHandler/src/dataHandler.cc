#include "dataHandler.h"

std::unordered_map<Parameter, float> DataHandler::m_dataHandlerMap;
ErrorLog DataHandler::m_errorLog;
bool DataHandler::m_initialized{false};

DataHandler::DataHandler()
{
}

void DataHandler::init()
{
    if(!m_initialized)
    {     
        m_dataHandlerMap.reserve(100);
        m_dataHandlerMap.insert(std::pair<Parameter, float>(Parameter::OSCILLATOR_0_WAVEFORM, static_cast<float>(Waveform::PULSE)));
        m_dataHandlerMap.insert(std::pair<Parameter, float>(Parameter::OSCILLATOR_0_PITCH, 0.0f));
        m_initialized = true;
    }
}

DataHandler::~DataHandler()
{

}

void DataHandler::setParameter(const Parameter parameter, const float data)
{
    init();
    auto it = m_dataHandlerMap.find(parameter);
    if (it != m_dataHandlerMap.end())
    {
        it->second = data;
        return;    
    }
    m_errorLog.printError("Parameter", parameter, "not in map by initialization!");
}

std::optional<float> DataHandler::getParameter(const Parameter parameter)
{
    init();
    auto it = m_dataHandlerMap.find(parameter);
    if (it != m_dataHandlerMap.end())
    {
        return it->second;
    }
    m_errorLog.printError("Parameter", parameter, "not found in map!");
    return {};
}
