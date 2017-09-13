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

using namespace Platform;
using namespace Platform::Metadata;
using namespace Windows::Data::Json;

namespace Microsoft { namespace Devices { namespace Management { namespace Message
{
    public ref class WindowsTelemetryData sealed
    {
    public:
        property String^ level;

        Blob^ Serialize(uint32_t tag) {
            JsonObject^ jsonObject = ref new JsonObject();

            jsonObject->Insert("level", JsonValue::CreateStringValue(level));

            return SerializationHelper::CreateBlobFromJson((uint32_t)tag, jsonObject);
        }

        static WindowsTelemetryData^ Deserialize(Blob^ blob) {
            String^ str = SerializationHelper::GetStringFromBlob(blob);
            JsonObject^ jsonObject = JsonObject::Parse(str);
            auto result = ref new WindowsTelemetryData();

            result->level = jsonObject->Lookup("level")->GetString();

            return result;
        }
    };

    public ref class SetWindowsTelemetryRequest sealed : public IRequest
    {
    public:
        property WindowsTelemetryData^ data;

        SetWindowsTelemetryRequest(WindowsTelemetryData^ d)
        {
            data = d;
        }

        virtual Blob^ Serialize() {
            return data->Serialize((uint32_t)Tag);
        }

        static IDataPayload^ Deserialize(Blob^ blob) {
            WindowsTelemetryData^ d = WindowsTelemetryData::Deserialize(blob);
            return ref new SetWindowsTelemetryRequest(d);
        }

        virtual property DMMessageKind Tag {
            DMMessageKind get();
        }
    };

    public ref class GetWindowsTelemetryRequest sealed : public IRequest
    {
    public:
        virtual Blob^ Serialize() {
            return SerializationHelper::CreateEmptyBlob((uint32_t)Tag);
        }

        static IDataPayload^ Deserialize(Blob^ bytes) {
            return ref new GetWindowsTelemetryRequest();
        }

        virtual property DMMessageKind Tag {
            DMMessageKind get();
        }
    };

    public ref class GetWindowsTelemetryResponse sealed : public IResponse
    {
        StatusCodeResponse statusCodeResponse;

    public:
        property WindowsTelemetryData^ data;

        GetWindowsTelemetryResponse(ResponseStatus status, WindowsTelemetryData^ d) : statusCodeResponse(status, this->Tag)
        {
            data = d;
        }

        virtual Blob^ Serialize() {
            return data->Serialize((uint32_t)Tag);
        }

        static IDataPayload^ Deserialize(Blob^ blob) {
            WindowsTelemetryData^ d = WindowsTelemetryData::Deserialize(blob);
            return ref new GetWindowsTelemetryResponse(ResponseStatus::Success, d);
        }

        virtual property ResponseStatus Status {
            ResponseStatus get() { return statusCodeResponse.Status; }
        }

        virtual property DMMessageKind Tag {
            DMMessageKind get();
        }
    };
}
}}}
