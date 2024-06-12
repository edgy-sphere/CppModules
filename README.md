# Cpp Modules

This small example project tries to use C++ modules in an Unreal project.

## Using

- Windows 11 22621.3593
- Unreal Engine 5.4.2
- > bundled DotNet SDK version: 6.0.302
- Visual Studio Version 17.6.4
- Visual Studio 2022 14.36.32535 toolchain
- Windows 10.0.22621.0 SDK

## Steps taken

A new Unreal project was created.

The Target files (`/Source/CppModules.Target.cs` and `/Source/CppModulesEditor.Target.cs`) have been changed to `bEnableCppModules = true` and the Build file (`/Source/CppModules/CppModules.Build.cs`) to `CppStandard = CppStandardVersion.Latest`.

The source files `City/city.ixx`, `City/district.ixx` and `Country/country.ixx` have been added, alongside a test `Country/country_test.ixx` (which cannot be run as the compilation does not succeed).

The Visual Studio solution was regenerated.

## `import <vector>` error

Using `import <vector>` (in `Country/country.ixx`) does not compile: 

```
1>[1/6] Compile [x64] country.ixx
1>D:\Unreal\CppModules\Source\CppModules\Country\country.ixx(6): error C7612: could not find header unit for 'C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.36.32532\INCLUDE\vector'
1>D:\Unreal\CppModules\Source\CppModules\Country\country.ixx(12): error C2039: 'vector': is not a member of 'std'
1>C:\Program Files\Epic Games\UE_5.4\Engine\Source\predefined C++ types (compiler internal)(347): note: see declaration of 'std'
1>D:\Unreal\CppModules\Source\CppModules\Country\country.ixx(12): error C7621: module partition 'district' for module unit 'city' was not found
1>D:\Unreal\CppModules\Source\CppModules\Country\country.ixx(12): fatal error C1199: missing reference to IFC file to resolve an import-declaration; please ensure the proper value for a '/reference' or '/headerUnit' option is provided
```

Therefore `#include <vector>` (in the [global module fragment](https://en.cppreference.com/w/cpp/language/modules#Global_module_fragment)) is used instead.

## Module partition IFC error

UnrealBuildTool fails to compile this updated project (without `import <vector>`) with the following errors:

```
1>[1/6] Compile [x64] country.ixx
1>D:\Unreal\CppModules\Source\CppModules\Country\country.ixx(12): error C7621: module partition 'district' for module unit 'city' was not found
1>D:\Unreal\CppModules\Source\CppModules\Country\country.ixx(12): fatal error C1199: missing reference to IFC file to resolve an import-declaration; please ensure the proper value for a '/reference' or '/headerUnit' option is provided
```

An IFC file is, in fact, created under `/Intermediate/Build/Win64/x64/UnrealEditor/Development/CppModules/Ifc/district.ifc` &ndash; if that is the actual cause of the failure.

## Finally

An Unreal-free build succeeds (see at `Standalone`) for both issues, which makes it less likely that I did use the C++ modules in a wrong way.

It may also be of interest that the generated Visual Studio project (`/Intermediate/ProjectFiles/CppModules.vcxproj`) lists `.ixx` files as e.g. `<None Include="..\..\Source\CppModules\City\city.ixx"/>`, whereas the Unreal-free project lists them as e.g. `<ClCompile Include="..\..\Source\CppModules\City\city.ixx" />`, though manually changing this did not benefit me.

I'm certainly no expert on MSVC or UBT workings, so I apologise for not being able to provide any additional information.


