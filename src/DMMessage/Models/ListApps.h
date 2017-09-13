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
#include "IRequestIResponse.h"
#include "SerializationHelper.h"
#include "DMMessageKind.h"
#include "StatusCodeResponse.h"
#include "Blob.h"

#include <collection.h>

using namespace Platform;
using namespace Platform::Metadata;
using namespace Platform::Collections;
using namespace Windows::Data::Json;
using namespace Windows::Foundation::Collections;

#define INSERT_STRING_PROPERTY_INTO_JSON(json, info, propName) json->Insert(#propName, JsonValue::CreateStringValue(info->##propName))
#define SET_STRING_PROPERTY_FROM_JSON(json, info, propName) info->##propName = json->GetNamedString(#propName)

namespace Microsoft { namespace Devices { namespace Management { namespace Message
{
    public ref class AppInfo sealed
    {
    public:
        AppInfo() {}
    
    internal:
        AppInfo(JsonObject^ jsonApp)
        {
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, AppSource);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, Architecture);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, InstallDate);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, InstallLocation);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, IsBundle);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, IsFramework);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, IsProvisioned);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, Name);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, PackageFamilyName);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, PackageStatus);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, Publisher);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, RequiresReinstall);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, ResourceID);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, Users);
            SET_STRING_PROPERTY_FROM_JSON(jsonApp, this, Version);

            // Macros cannot be used with the casting easily.
            StartUp = static_cast<StartUpType>(static_cast<int>(jsonApp->Lookup("StartUp")->GetNumber()));
        }
        JsonObject^ ToJson()
        {
            auto jsonApp = ref new JsonObject();
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, AppSource);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, Architecture);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, InstallDate);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, InstallLocation);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, IsBundle);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, IsFramework);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, IsProvisioned);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, Name);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, PackageFamilyName);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, PackageStatus);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, Publisher);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, RequiresReinstall);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, ResourceID);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, Users);
            INSERT_STRING_PROPERTY_INTO_JSON(jsonApp, this, Version);

            // Macros cannot be used with the casting easily.
            jsonApp->Insert("StartUp", JsonValue::CreateNumberValue(static_cast<int>(StartUp)));

            return jsonApp;
        }

    public:
        property String^ AppSource;
        property String^ Architecture;
        property String^ InstallDate;
        property String^ InstallLocation;
        property String^ IsBundle;
        property String^ IsFramework;
        property String^ IsProvisioned;
        property String^ Name;
        property String^ PackageFamilyName;
        property String^ PackageStatus;
        property String^ Publisher;
        property String^ RequiresReinstall;
        property String^ ResourceID;
        property String^ Users;
        property String^ Version;
        property StartUpType StartUp;
    };

    public ref class ListAppsResponse sealed : public IResponse
    {
    private:
        ResponseStatus status;
        IMap<String^, AppInfo^>^ apps;

    public:
        ListAppsResponse(ResponseStatus status, IMap<String^, AppInfo^>^ apps) : status(status), apps(apps) {}

    internal:
        ListAppsResponse(ResponseStatus status, JsonObject^ appsJson) : status(status) 
        {
            apps = ref new Map<String^, AppInfo^>();
            for each (auto pair in appsJson)
            {
                auto pfn = pair->Key;
                auto properties = appsJson->GetNamedObject(pfn);
                apps->Insert(pfn, ref new AppInfo(properties));
            }
        }

    public:
        virtual Blob^ Serialize() {
            auto jsonObject = ref new JsonObject();
            jsonObject->Insert("Status", JsonValue::CreateNumberValue((uint32_t)status));
            auto jsonApps = ref new JsonObject();
            for each (auto app in apps) 
            {
                auto pfn = app->Key;
                auto properties = app->Value;
                jsonApps->Insert(pfn, properties->ToJson());
            }
            jsonObject->Insert("Apps", jsonApps);
            return SerializationHelper::CreateBlobFromJson((uint32_t)Tag, jsonObject);
        }

        static IDataPayload^ Deserialize(Blob^ bytes) {
            auto str = SerializationHelper::GetStringFromBlob(bytes);
            auto jsonObject = JsonObject::Parse(str);
            auto status = (ResponseStatus)(uint32_t)jsonObject->GetNamedNumber("Status");
            auto appDictionary = jsonObject->GetNamedObject("Apps");
            return ref new ListAppsResponse(status, appDictionary);
        }

        virtual property DMMessageKind Tag {
            DMMessageKind get();
        }

        virtual property ResponseStatus Status {
            ResponseStatus get() { return status; }
        }

        property IMap<String^, AppInfo^>^ Apps {
            IMap<String^, AppInfo^>^ get() { return apps; }
        }
    };
}}}}
