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
#include "AppInfo.h"

class AppCfg
{
public:
    static void StartApp(const std::wstring& appId) { StartStopApp(appId, true); }
    static void StopApp(const std::wstring& appId) { StartStopApp(appId, false); }

    static ApplicationInfo InstallApp(
        const std::wstring& packageFamilyName,
        const std::wstring& appxLocalPath,
        const std::vector<std::wstring>& dependentPackages,
        const std::wstring& certFileName,
        const std::wstring& certStore,
        bool isDMSelfUpdate);

    static ApplicationInfo UninstallApp(const std::wstring& packageFamilyName);


private:
    static bool IsAppRunning(
        const std::wstring& packageFamilyName);

    static ApplicationInfo InstallAppInternal(
        const std::wstring& packageFamilyName,
        const std::wstring& appxLocalPath,
        const std::vector<std::wstring>& dependentPackages,
        const std::wstring& certFileName,
        const std::wstring& certStore);

    static ApplicationInfo GetAppInfo(Windows::ApplicationModel::Package^ package);
    static void StartStopApp(const std::wstring& appId, bool start);

    static Windows::ApplicationModel::Package^ FindApp(const std::wstring& packageFamilyName);
    static ApplicationInfo BuildOperationResult(const std::wstring& packageFamilyName);
};
