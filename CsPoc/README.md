# Windows App SDK C# Arm64EC Unpackaged Sample

This project demonstrates how to create an Unpackaged ARM64EC Windows App SDK app.

Steps:

1. Create a self-contained, unpackaged C# Windows App SDK app, per [these instructions](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/deploy-unpackaged-apps#use-the-windows-app-sdk-runtime). Make sure to set the following properties in your .vcxproj file:

    ```MSBuild
        <PropertyGroup>
            <WindowsAppSdkSelfContained>true</WindowsAppSdkSelfContained>
            <WindowsPackageType>None</WindowsPackageType>
        </PropertyGroup>
    ```

1. Edit the Platforms property to add an ARM64EC Platform and ensure it maps to the x64 underlying platform architecture:

    ```MSBuild
        <PropertyGroup>
            <Platforms>x86;x64;ARM64;ARM64EC</Platforms>
            <PlatformTarget Condition=" '$(Platform)' == 'ARM64EC' ">x64</PlatformTarget>
        </PropertyGroup>
    ```

1. Create an ARM64EC Solution Platform and map it to the new ARM64EC Project Platform.

1. Build the project for the new ARM64EC Platform.  Verify x64 build of app (ARM64EC is not yet supported in .NET)
and ARM64EC deployment of WinAppSDK self-contained binaries:

    ```shell
    >cd bin\ARM64EC\Debug\net8.0-windows10.0.19041.0
    >for /f "delims=" %i in ('dir /b/s *.exe *.dll') do @echo %i & dumpbin /headers %i | findstr machine
    C:\git\ARM64EC\CsPoc\bin\ARM64EC\Debug\net8.0-windows10.0.19041.0\CsPoc.exe
            8664 machine (x64)
    ...
    C:\git\ARM64EC\CsPoc\bin\ARM64EC\Debug\net8.0-windows10.0.19041.0\Microsoft.ui.xaml.dll
            8664 machine (x64) (ARM64X)
    ...
    ```

1. Run/debug the app on an ARM64 device.
