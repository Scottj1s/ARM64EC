========================================================================
    Arm64ECTest Project Overview
========================================================================

This project demonstrates how to create an ARM64EC Windows App SDK app.
Support is currently limited to C++, Self-Contained, Unpackaged apps.

Steps:
1. Create a self-contained, unpackaged C++ Windows App SDK app,
   per the instructions here:
   https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/deploy-unpackaged-apps#use-the-windows-app-sdk-runtime
   Make sure to set the following properties in your .vcxproj file:
    <PropertyGroup>
      <WindowsAppSdkSelfContained>true</WindowsAppSdkSelfContained>
      <WindowsPackageType>None</WindowsPackageType>
    </PropertyGroup>

2. Create an ARM64EC Platform from x64, per:
https://learn.microsoft.com/en-us/windows/arm/arm64ec-build#msbuild-projects

3. Build the project for the new ARM64EC platform.

4. Run/debug the app on an ARM64 device.
