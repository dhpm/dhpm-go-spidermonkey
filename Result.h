#ifndef DHPM_RESULT_H
#define DHPM_RESULT_H

#include <jsapi.h>

class Result
{
    const char *value;
    JSErrorReport *report;

public:
    const char* GetValue();
    Result(const char *value, JSErrorReport *report);
};

#endif
