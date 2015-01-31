#ifndef DHPM_RESULT_H
#define DHPM_RESULT_H

#include <jsapi.h>
#include <map>

using std::map;
using std::pair;

class Result
{
    static map<JSContext*, Result*> errorHandleMap;
    const char *value;
    JSErrorReport *report;

public:
    static Result* GetErrorReporter(JSContext*);
    static void SetErrorReporter(JSContext*, Result*);

    Result(const char *value, JSErrorReport *report);

    JSErrorReporter BeErrorReporter(JSContext*);
    JSErrorReport* GetReport();
    const char* GetValue();
    void HandleError(JSContext*, const char*, JSErrorReport*);
    bool HasReport();
    void SetReport(JSErrorReport*);
    void SetValue(const char*);
};

#endif
