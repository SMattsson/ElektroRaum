#include "errorLog.h"
#include "arduinoLib.h"
#include "soundEngineDefs.h"

void ErrorLog::printError(std::string msg)
{
    Serial.print(" ");
    Serial.println(msg.c_str());
}

void ErrorLog::printError(std::string msg, uint32_t value, std::string msg2)
{
    Serial.print(msg.c_str());
    Serial.print(" ");
    Serial.print(value);
    Serial.print(" ");
    Serial.println(msg2.c_str());
}

void ErrorLog::printError(std::string msg, int32_t value, std::string msg2)
{
    Serial.print(msg.c_str());
    Serial.print(" ");
    Serial.print(value);
    Serial.print(" ");
    Serial.println(msg2.c_str());
}

void ErrorLog::printError(std::string msg, double value, std::string msg2)
{
    Serial.print(msg.c_str());
    Serial.print(" ");
    Serial.print(value);
    Serial.print(" ");
    Serial.println(msg2.c_str());
}

void ErrorLog::printError(std::string msg, Parameter value, std::string msg2)
{
    Serial.print(msg.c_str());
    Serial.print(" ");
    Serial.print(static_cast<uint32_t>(value));
    Serial.print(" ");
    Serial.println(msg2.c_str());
}
