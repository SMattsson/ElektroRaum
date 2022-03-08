#pragma once

#include <string>

enum class Parameter;

class ErrorLog
{
public:
    ErrorLog(){};
    void printError(std::string msg);
    void printError(std::string msg, int32_t value, std::string msg2 = "");
    void printError(std::string msg, uint32_t value, std::string msg2 = "");
    void printError(std::string msg, double value, std::string msg2 = "");
    void printError(std::string msg, Parameter value, std::string msg2 = "");
};
