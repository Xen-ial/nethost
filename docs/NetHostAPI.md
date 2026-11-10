# NetHost API

## Overview

This document will be going over the details for `/nethost/include/nethost/Assembly.h` and `/nethost/include/nethost/NetHostApp.h`  
As these are the most important parts of NetHost.  

## NetHostApp

NetHostApp contains the abstractions away from setting up and resolving the .net App host yourself. NetHost app gives access to resolved .net runtime function pointers, and initializing/shutting down the app host itself.  

### Public API

```cpp
NetHostApp(const std::string& runtimeConfigPath);
```

This constructor points towards the .net runtime configuration for the host app to resolve its target runtime version and properties.  

A basic default runtime configuration would look something like this:

```json
{
  "runtimeOptions": {
    "tfm": "net10.0",
    "rollForward": "LatestMinor",
    "framework": {
      "name": "Microsoft.NETCore.App",
      "version": "10.0.0"
    },
    "configProperties": {
      "System.Runtime.Serialization.EnableUnsafeBinaryFormatterSerialization": false
    }
  }
}
```

You can find the runtime config here `/examples/resources/Default.runtimeconfig.json`.  

```cpp
void NetHostApp::shutdown();
bool NetHostApp::isInititalized() const;
```

These 2 functions are quite self explanatory, `shutdown()` call the cleanup routine for the net host app then shuts down the .net context running within your program. Where as `isInitialized()` ensures that the app host has been properly initialized this is recommended to call before trying to access any data members.  

## Protected API

NetHost has a few resolved functions for you to use if you either inherit from or the consumer is a friend class.  

```cpp
Func getFunc(const std::string& name, const std::string& nameSpace, const std::string& targetClass, const std::string& targetLib) const;

void getFuncDelegate(void** delegate, const std::string& name, const std::string& nameSpace, const std::string& targetClass, const std::string& targetLib);
```

`getFunc` and `getFuncDelegate` are helpers that allow ease of access for resolving, C# function delegates.  

You can see use of both within `nethost::Assembly` they directly call these 2 functions.  

`getFunc` usage example:  

```cpp
auto helloWorld = getFunc("funcName", "targetNameSpace", "targetClass");
if (helloWorld != nullptr)
    helloWorld();
```

`getFuncDelegate` usage example:  

```cpp
FuncType getNumber = nullptr;
nethostApp.getFuncDelegate(reinterpret_cast<void**>(&getNumber), methodName, nameSpace, targetClass, libName);

if (getNumber != nullptr)
    auto number = getNumber();
```

### .NET functions

```cpp
HostContext              getHostContext() const;
InitForRuntimeConfigFunc getInitForRuntimeConfig() const;
GetRuntimeDelegateFunc   getRuntimeDelegate() const;
CloseFunc                getCloseFunc() const;
LoadAssemblyFunc         getLoadAssembly() const;
GetFunctionPointerFunc   getFunction() const;
```

`getHostContext`: The current net host loaded app host.  
`getInitForRuntimeConfig`: The initialization function pointer for loading the .net environment.  
`getRuntimeDelegate`: Allows us to load function delegate pointers from the .net library.  
`getCloseFunc`: Closes the current .net host FXR.  
`getLoadAssembly`: Loads the .net assembly into the targeted NetHostApp layer.
`getFunctionPointerFunc`: Gives access to loading function pointers from C# into C++.  

## Assembly

Assembly gives you direct access for resolving and calling function pointers from C#.  

> NOTE `BorrowedRef<T>` is an alias for (`std::reference_wrapper<T>`)

```cpp
Assembly(BorrowedRef<NetHostApp> nethostApp, const std::string& assemblyPath, std::string libName);
```

Assembly constructor takes in the target `NetHostApp`, the path to the managed dll, and the library name.  

```cpp
Func getFunc(const std::string& methodName, const std::string& nameSpace, const std::string& targetClass);

template <typename T>
T getFunc(const std::string& methodName, const std::string& nameSpace, const std::string& targetClass);
```

`getFunc`: Resolves a function pointer from the loaded assembly.  
`getFunct<T>`: Resolves a delegate function pointer from the loaded assembly.  
