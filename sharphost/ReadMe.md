# SharpHost

## Overview

SharpHost is a NetHost extension library built directly ontop of NetHost it simplifies interactions with Managed handles. Allowing you to write and interact with the managed scripting host a lot easier. SharpHost comes with extended features, reflection caching, reflection invoking, attribute searching, function delegate compiling (speeds up general calls to managed functions), and much more. SharpHost runs in the .NET 10 ecosystem. SharpHost aims for a simple library design, while bringing advanced features to your fingertips.  

What is SharpHosts main features?  

* Reflection Cache / Maps (To speed up calls, and searching with in assemblies)
* Easier invocation of functions
* Instance creation of classes, and structs.
* Access to attribute searching, this feature is huge in terms of scripting support for [Serializable], [DoNotDestroy], and other attribute attachments.
* Property value getters, and setters, SharpHost brings you freedom to Get and Set values for properties at free will.
* AssemblyContexts custom assembly domains for each assembly / assemblies so its as simple as unloading and loading them again for hot-reload.
* Enum mapping, extract information from enums both their enumerator name, and value.

These are just a few of the features that SharpHost delivers to you. To read more see `/docs/SharpHost/`  

### NetHost And SharpHost Differences

NetHost is a wrapper around the native Host FXR library that abstracts some pain points away allowing easier usage of nethost, while sharphost goes a step beyond that allowing direct access to a managed host living inside the .NET eco-system. While NetHost does make things easier it still requires a good bit of boiler plate to get setup and messing around with script hosting. So SharpHost is here to simplify that even further so access is direct plug and play so you can focus on getting scripting integrated with in your native context.  

### Who is SharpHost For?

SharpHost is for anyone who wants to use C# scripting, or the features of C# directly within their native (C++) context. This primarly stands for Game Engines, Plugin Support, Modding support, and lots of other areas.  
