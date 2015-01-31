#ifndef DHPM_RESULT_H
#define DHPM_RESULT_H

#include <jsapi.h>
#include <map>

#include "ErrorReport.h"

using std::map;
using std::pair;

class Result
{
    static map<JSContext*, Result*> errorHandleMap;
    const char *value = nullptr;
    ErrorReport *report = nullptr;

public:
    static Result* GetErrorReporter(JSContext*);
    static void SetErrorReporter(JSContext*, Result*);

    Result(const char *value);

    JSErrorReporter BeErrorReporter(JSContext*);
    ErrorReport* GetReport();
    const char* GetValue();
    void HandleError(JSContext*, const char*, JSErrorReport*);
    bool HasReport();
    void SetReport(ErrorReport*);
    void SetValue(const char*);
};

#endif
