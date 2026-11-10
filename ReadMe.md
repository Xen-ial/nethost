# NetHost

## Overview

NetHost is an .net host CLR wrapper, meant to make integrating scripting more simple.  
This project uses C++23, CMake, and targets .net 10 with examples.  

NetHost supplies a simplified light wrapper around nethost native. While providing simple CMake integrations, for both Windows & Linux.  
It is planned in the future to also supply bindings, and a public interface for the Roslyn compiler for runtime script execution.  

To view all examples, visit `/examples/` the most basic example is within `/examples/helloLib/` and docs are under `/docs/` use these to assist you getting used to NetHost API.  

## Building

To build nethost run `cmake --preset default` then `cmake --build --preset release` once completed you will get NetHost as a static or dynamic library.  
Linking is simple include nethost as a sub directory, or add the static/dynamic library within your cpp project and link against `nethost`  

## Examples

There are currently 2 examples.  

### Example 01: HelloLib

This example is as simple as it gets, setting up a .net app host, loading a .net assembly, then calling a function from .net directly in C++.  

### Example 02: HelloScripting

This example shows you how to integrate NetHost as a proper scripting library. Showing function calls from C# in C++, passing native functions and calling them within C#.  
With a simulated game loop to show the details of embedding and interacting with NetHost in your project.  

## Docs

To view and read the public API for NetHost in detail visit `/docs/GettingStarted.md` then follow the initial setup guide, and view the API at `/docs/NetHostAPI.md`
