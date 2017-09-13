/*
Copyright 2017 Microsoft
Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once

#include <string>
#include <windows.h>
#include "Models\TimeInfo.h"
#include "Models\TimeService.h"

class TimeCfg
{
    struct TimeInfo
    {
        std::wstring localTime;
        std::wstring ntpServer;
        TIME_ZONE_INFORMATION timeZoneInformation;
    };

public:
    static Microsoft::Devices::Management::Message::GetTimeInfoResponse^ Get();
    static void Set(Microsoft::Devices::Management::Message::SetTimeInfoRequest^ request);

private:
    static void Get(TimeInfo& info);
    static void SetNtpServer(const std::wstring& ntpServer);
};

class TimeService
{
public:
    static Microsoft::Devices::Management::Message::TimeServiceData^ GetState();
    static void SetState(Microsoft::Devices::Management::Message::TimeServiceData^ request);

private:
    static void SaveState(Microsoft::Devices::Management::Message::TimeServiceData^ data);
    static Microsoft::Devices::Management::Message::TimeServiceData^ GetActiveDesiredState();
};
