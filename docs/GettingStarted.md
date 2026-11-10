# Getting Started With NetHost

## Overview

This is the getting started steps to assist you in getting setup, and running nethost to see the API documentation visit `/docs/NetHostAPI.md` for more detail about what each class contains.  

## Building

NetHost uses CMake and Ninja as the build pipeline. In order to build nethost you can call `cmake --preset default` to stage the environment from the command line. Then to actually build you need to call `cmake --build --preset release`.

The include headers can be found here (`/nethost/include/nethost`).  
You can also directly include nethost within your cmake project by adding a sub_directory()  

## Setting Up

In order to use nethost effectively you need to setup an NetHostApp domain, doing this is really simple and straight forward.  

To start you need to include `nethost/NetHostApp.h` to get access to the NetHostApp class.  

We then need to pass in the relative / absolute path to the `App.runtimeconfig.json`  
The `App.runtimeconfig.json` for this example looks like this:  

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

This runtime configuration basically just tells the net host context that we want to ensure to start up the environment running .NET 10 with these specific properties.  

Once the NetHostApp is pointed towards a configuration file, we then need to make sure that everything has loaded properly.  

For safety reasons make sure to call `myNetHostApp.isInitialized()` just to ensure that we did not run into any mishaps while creating our context.  

Then lets not forget that after all the work is done we need to shutdown the context. To do this call `myNetHostApp.shutdown()` at the end of the usage/function.  

```cpp
#include <nethost/NetHostApp.h>

#include <print>

int main()
{
    nethost::NetHostApp myNetHostApp("App.runtimeconfig.json"); // Create context
    if (!myNetHostApp.isInitialized()) // Check if initialization succeeded 
    {
        std::println("Failed to create nethost application context");
        return 1;
    }

    // Do work here

    myNetHostApp.shutdown(); // Shutdown the app context
    return 0;
}
```

Great now that we understand how to get a context loaded and the needed information for setting up the runtime domain.  

Its time to get into calling a function from our ***NetHostApp*** assemblies.  
First lets start with the ***managed*** sides of things.  

## Managed Target

Our managed target is a .NET 10 C# library assembly. The source files can be found here: `/examples/helloLib/managed`.  

To do this we need to create a new .NET 10 library assembly. This can be done via UI format within (Visual Studio, JetBrains Rider, etc.) but to ensure this guide is non dependent on specifics for editors we will be using the command line.  

To get started make a new directory called `DotNetLib` within Linux its done like this:  

```bash
mkdir DotNetLib
cd DotNetLib
```

Once we are in this directory we can create the .NET 10 class library.  

```bash
dotnet new classlib -n DotNetLib 
```

You will get the initial templated setup with `Class1.cs`. Once confirmed while outside that directory call:  

```bash
dotnet new sln -n DotNetLib
```

This will drop a new SLNX file into your directory.  
Now we need to link the `sln` to the `csproj` from the top level directory where the `sln` is created from the command line call:  

```bash
dotnet sln add DotNetLib/DotNetLib.csproj 
```

Now that we have linked to the *DotNetLib* class library. We can go load up the `DotNetLib` C# project within our desired IDE/Code Editor. I will be using VSCode and the ReSharper extension. Once opened within your desired editor, rename `Class1.cs` to `Lib.cs` from there we will build out our new static class.  

There is only 1 library we will need to include in order to interact with this example.  
That would be `InteropServices` - (i.e. `using System.Runtime.InteropServices`).  

Next define a namespace we will be using **DotNetLib** - (i.e. `namespace DotNetLib;`).  
Finally its time to define a class that we can target from our context, we will be naming it `Lib`.  

```csharp
using System.Runtime.InteropServices;

namespace DotNetLib;

public static class Lib
{
    private static byte _isWaiting = 0;

    [UnmanagedCallersOnly]
    public static void Main()
    {
        Console.WriteLine("Hello World");
        _isWaiting = 1;
    }

    [UnmanagedCallersOnly]
    public static byte IsWaiting() => _isWaiting;
}
```

This is what the `Lib.cs` file looks like. This is all (safe) dotnet compliant code. Just remember in order to build a native bridge you will need to go outside the safety of the managed .Net runtime. Ensure to add error checking, and do not blindly trust memory and data passed between boundaries.  

With that said lets break down what DotNetLib is doing. If you have not written much .NET, or are unfamiliar with using it in this way. We first mark the class as static, by doing this we are claiming the *Lib* class as our bootstrapper, or entry point into the managed context.  

From here we create a new **byte** object that is named `_isWaiting` this byte is simply here as a flag the same way `bool` would work. We use this as a way to test against our call to main. The question that we are asking is "did we get information back from the hosts context?" this will provide us with a way to test that and ensure that it's working as expected.  

Create a new public static void called *Main()* this is our entry point into the context. We will call this function and get a hello world message, which will also set the _isWaiting byte to 1.  

Now as for what `[UnmanagedCallersOnly]` does, this attribute directly marks the decorated method as a native export. Allowing you to call it from outside the managed context. This is especially useful when you know that the only caller will be the native bootstrapper. It is suggested against doing it if you plan to use the same function within your managed runtime. If that were to be the case create a wrapper around the function and open it up to unmanaged callers, rather than marking the original as such.  

Finally let's build our .Net assembly from the command line or your IDE's interface.
From command line we input `dotnet build` either in the top level folder where the `slnx` is or where the `csproj` has been placed.  

Back to the C++ side of things it is time to wire up our function calls and map out managed assembly into the host context.  
Now let's take a look at the steps required to load the assembly and call our managed functions. This will be displayed below with the code example from last time.  

```cpp
// TODO 1: #include <nethost/Assembly.h>
#include <nethost/NetHostApp.h>

#include <print>

int main()
{
    nethost::NetHostApp myNetHostApp("App.runtimeconfig.json"); // Create context
    if (!myNetHostApp.isInitialized()) // Check if initialization succeeded 
    {
        std::println("Failed to create nethost application context");
        return 1;
    }

    // TODO 2: Create the dotnetLib assembly

    // TODO 3: Create void delegate function pointer to Main

    // TODO 4: Create char delegate function pointer to IsWaiting

    // TODO 5: Call isWaiting to check the value and display it

    // TODO 6: Call Main and see if Hello World prints in the console

    // TODO 7: Call isWaiting() again and print out the new value

    myNetHostApp.shutdown(); // Shutdown the app context
    return 0;
}
```

Let's start filling in the details lets stage, and load our dotnet assembly. First we need to include a new header `#include <nethost/Assembly.h>` this class wraps and holds onto the assembly handle, while giving access to some helper functions.  

At the top of your c++ main file include `nethost/Assembly.h`:  

```cpp
#include <nethost/Assembly.h>
#include <nethost/NetHostApp.h>
```

> Note this example takes assumes that your managed dll is sitting in the same folder as the native executable.

Let's define the `nethost::Assembly` instance pointed at our target app host:  

```cpp
// TODO 2: Create the dotnetLib assembly
nethost::Assembly dotnetLib(myNetHostApp, "DotNetLib.dll", "DotNetLib");
```

*nethost::Assembly* takes 3 parameters, the target host app, DLL path, and the library name.  
Since the library is loaded into our app host we can get a pointer to our fist delegate function!  

```cpp
// TODO 3: Create void delegate function pointer to Main
using MainEntryFn     = void(NETHOST_DELEGATE_CALLTYPE*)();
MainEntryFn mainEntry = dotnetLib.getFunc<MainEntryFn>("Main", "DotNetLib", "Lib");
```

The ***using MainEntryFn*** defines the delegate shape that we want to invoke, You will see a macro called `NETHOST_DELEGATE_CALLTYPE` this macro ensures parity in calls between different OS's making it easier on the consumers implementation.  

***MainEntryFn mainEntry*** delegate definition for our Main() function, with the target of (methodName = `Main`, nameSpace = `DotNetLib`, targetClass = `Lib`) this input information gives the context all it needs to resolve the assembly method, assuming its visible to the assembly.  

We should not just blindly trust that we resolved this function pointer so we should check to ensure that we are not trying to access a nullptr.  

```cpp
if (mainEntry == nullptr)
{
    std::println("Hello failed to be resolved");
    return 1;
}
```

This will stop us in our tracks before calling a nullptr, resulting in undefined behavior.  

> Note ensure to check your functions/delegates properly resolved.

Now we have resolved the Main function delegate into our host context.  
We just need to resolve IsWaiting() and call the functions.  

```cpp
// TODO 4: Create char delegate function pointer to IsWaiting
using IsWaitingFn     = unsigned char(NETHOST_DELEGATE_CALLTYPE*)();
IsWaitingFn isWaiting = dotnetLib.getFunc<IsWaitingFn>("IsWaiting", "DotNetLib", "Lib");

if (isWaiting == nullptr)
{
    std::println(("failed to resolve isWaiting"));
    return 1;
}
```

This setup is very similar to how the Main function delegate is called. The biggest difference is that we are setting the return type instead of void we are using unsigned char (or byte in C#) to receive a small information flag (1 or 0).  

Since we resolved both of our function delegate pointers, its time to call them in our native application.  

```cpp
// TODO 5: Call isWaiting to check the value and display it
auto isWaitingValue = isWaiting();
std::println("IsWaiting: {}", isWaitingValue == 1);

// TODO 6: Call Main and see if Hello World prints in the console
mainEntry();

// TODO 7: Call isWaiting() again and print out the new value
isWaitingValue = isWaiting();
std::println("IsWaiting: {}", isWaitingValue == 1);
```

In order to use the isWaiting value we need to create a variable to store it, so lets first create an isWaitingValue then call isWaiting() to get data from the managed side, from there print out the value to the console, if its 1 then display **true**, else display **false**.  

After that call mainEntry(), you should see it printing out hello world, and behind the scenes it is setting _isWaiting's byte to 1.  

Main():  

```csharp
Console.WriteLine("Hello World");
_isWaiting = 1;
```

After calling Main print out isWaiting to the console again, It should have now gone from 0 to 1. Resulting in a success (no errors).  

### Full Example

```cpp
// TODO 1: #include <nethost/Assembly.h>
#include <nethost/Assembly.h>
#include <nethost/NetHostApp.h>

#include <print>

int main()
{
    nethost::NetHostApp myNetHostApp("App.runtimeconfig.json"); // Create context
    if (!myNetHostApp.isInitialized()) // Check if initialization succeeded 
    {
        std::println("Failed to create nethost application context");
        return 1;
    }

    // TODO 2: Create the dotnetLib assembly
    nethost::Assembly dotnetLib(myNetHostApp, "DotNetLib.dll", "DotNetLib");

    // TODO 3: Create void delegate function pointer to Main
    using MainEntryFn     = void(NETHOST_DELEGATE_CALLTYPE*)();
    MainEntryFn mainEntry = dotnetLib.getFunc<MainEntryFn>("Main", "DotNetLib", "Lib");

    if (mainEntry == nullptr)
    {
        std::println("Hello failed to be resolved");
        return 1;
    }

    // TODO 4: Create char delegate function pointer to IsWaiting
    using IsWaitingFn     = unsigned char(NETHOST_DELEGATE_CALLTYPE*)();
    IsWaitingFn isWaiting = dotnetLib.getFunc<IsWaitingFn>("IsWaiting", "DotNetLib", "Lib");

    if (isWaiting == nullptr)
    {
        std::println(("failed to resolve isWaiting"));
        return 1;
    }

   // TODO 5: Call isWaiting to check the value and display it
    auto isWaitingValue = isWaiting();
    std::println("IsWaiting: {}", isWaitingValue == 1);

    // TODO 6: Call Main and see if Hello World prints in the console
    mainEntry();

    // TODO 7: Call isWaiting() again and print out the new value
    isWaitingValue = isWaiting();
    std::println("IsWaiting: {}", isWaitingValue == 1);

    if (isWaitingValue != 1)
        std::println("isWaiting value has returned false");

    myNetHostApp.shutdown(); // Shutdown the app context
    return 0;
}
```

> Note remember that before you run the example you have created within this guide, build, and place `DotNetLib.dll` in the directory your native application is right next to the executable.  

This has concluded the basics of interacting with nethost and loaded assemblies inside the context. For a more advanced example visit `/examples/helloScripting` to see how this would be used in real world context aimed towards game engines.  

## Final Notes

Due to the way NetHost works for there are limitations to what you can, and can not do. There are available workarounds for the majority of the use cases, you just need to think outside the box.  

Reminder that the Managed DLL needs to be built before you can use it, if you are looking for a runtime script execution library this is not a direct fit, in order for this library to be used as a runtime on the fly exeuction engine, you will need to create a bridge to the C# Roslyn compiler. I have plans to extend this library further and give that as an option.  

With all this said, I hope you enjoy!  
