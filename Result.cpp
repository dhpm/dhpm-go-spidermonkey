#include "Result.h"

const char* Result::GetValue()
{
    return this->value;
}

Result::Result(const char *value, JSErrorReport *report)
{
    this->report = report;
    this->value = value;
}
