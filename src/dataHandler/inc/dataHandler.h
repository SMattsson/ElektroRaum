#pragma once

#include <unordered_map>
#include "dataHandlerIf.h"
#include "soundEngineDefs.h"
#include "errorLog.h"

class DataHandler : public DataHandlerIf
{
public:
    DataHandler();
    virtual ~DataHandler();
    virtual void setParameter(const Parameter parameter, const float data);
    virtual std::optional<float> getParameter(const Parameter parameter);
    

private:
    static void init();
    static std::unordered_map<Parameter, float> m_dataHandlerMap;
    static ErrorLog m_errorLog;
    static bool m_initialized;
};
