﻿/*
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

using Newtonsoft.Json.Linq;
using System;
using System.Text;

namespace Microsoft.Devices.Management.DMDataContract
{
    public class TimeServiceDataContract
    {
        public const string NotFound = "<not found>";
        public const string SectionName = "timeService";

        public const string JsonEnabled = "enabled";
        public const string JsonStartup = "startup";
        public const string JsonStarted = "started";

        public const string JsonSourcePriority = "sourcePriority";

        public const string JsonYes = "yes";
        public const string JsonNo = "no";
        public const string JsonAuto = "auto";
        public const string JsonManual = "manual";

        public class DesiredProperties
        {
            public string enabled;
            public string startup;
            public string started;
            public string sourcePriority;

            public void LoadFrom(JObject timeServiceObject)
            {
                enabled = Utils.GetString(timeServiceObject, JsonEnabled, NotFound);
                startup = Utils.GetString(timeServiceObject, JsonStartup, NotFound);
                started = Utils.GetString(timeServiceObject, JsonStarted, NotFound);
                sourcePriority = Utils.GetString(timeServiceObject, JsonSourcePriority, NotFound);
            }

            public string ToJson()
            {
                StringBuilder sb = new StringBuilder();
                sb.Append("\"" + SectionName + "\" : {\n");
                sb.Append("\"" + JsonEnabled + "\" : \"" + enabled + "\",\n");
                sb.Append("\"" + JsonStartup + "\" : \"" + startup + "\",\n");
                sb.Append("\"" + JsonStarted + "\" : \"" + started + "\",\n");
                sb.Append("\"" + JsonSourcePriority + "\" : \"" + sourcePriority + "\",\n");
                sb.Append("}");
                return sb.ToString();
            }
        }

        public class ReportedProperties
        {
            public string enabled;
            public string startup;
            public string started;
            public string sourcePriority;

            public void LoadFrom(JObject json)
            {
                enabled = Utils.GetString(json, JsonEnabled, NotFound);
                startup = Utils.GetString(json, JsonStartup, NotFound);
                started = Utils.GetString(json, JsonStarted, NotFound);
                sourcePriority = Utils.GetString(json, JsonSourcePriority, NotFound);
            }
        }
    }
}