#ifndef DHPM_RESULT_H
#define DHPM_RESULT_H

#include <jsapi.h>
#include <map>

using std::map;

class Result
{
    map<JSContext*, function<void(JSContext*, const char*, JSErrorReport*)>> errorHandleMap;
    const char *value;
    JSErrorReport *report;

public:
    Result(const char *value, JSErrorReport *report);

    const char* GetValue();
    void SetValue(const char*);

    JSErrorReport* GetReport();
    bool HasReport();
    void SetReport(JSErrorReport*);

    void HandleError(JSContext*, const char*, JSErrorReport*);
};

#endif
