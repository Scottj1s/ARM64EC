# Windows App SDK C++ Arm64EC Unpackaged Sample

This project demonstrates how to create an Unpackaged ARM64EC Windows App SDK app.

Steps:

1. Create a self-contained, unpackaged C++ Windows App SDK app, per [these instructions](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/deploy-unpackaged-apps#use-the-windows-app-sdk-runtime). Make sure to set the following properties in your .vcxproj file:

    ```MSBuild
        <PropertyGroup>
            <WindowsAppSdkSelfContained>true</WindowsAppSdkSelfContained>
            <WindowsPackageType>None</WindowsPackageType>
        </PropertyGroup>
    ```

1. Create ARM64EC Solution and Project Platforms from x64, per [these instructions](https://learn.microsoft.com/en-us/windows/arm/arm64ec-build#msbuild-projects).

1. Build the project for the new ARM64EC platform.  Verify ARM64EC build of app and deployment of WinAppSDK self-contained binaries:

    ```shell
    >cd ARM64EC\Debug\CppUnpackaged
    >for /f "delims=" %i in ('dir /b/s *.exe *.dll') do @echo %i & dumpbin /headers %i | findstr machine
    C:\git\ARM64EC\CppPoc\ARM64EC\Debug\CppUnpackaged\CppUnpackaged.exe
            8664 machine (x64) (ARM64X)
    ...
    C:\git\ARM64EC\CppPoc\ARM64EC\Debug\CppUnpackaged\Microsoft.ui.xaml.dll
            8664 machine (x64) (ARM64X)
    ...
    ```

1. Run/debug the app on an ARM64 device.
