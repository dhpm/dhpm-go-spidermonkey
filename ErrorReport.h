#ifndef DHPM_ERRORREPORT_H
#define DHPM_ERRORREPORT_H

#include <jsapi.h>

class ErrorReport
{
    JSContext *context = nullptr;
    const char *message = nullptr;
    JSErrorReport *report = nullptr;

public:
    ErrorReport(JSContext*, const char*, JSErrorReport*);

    const char* GetStackTrace();
    bool IsException();
};

#endif
