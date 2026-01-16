# Windows App SDK C++ WAP-Packaged Static Arm64EC Sample

This project demonstrates how to publish ARM64EC application binaries in a self-contained, packaged ARM64 app

build with a wapproj, and enabling remote debugging to the x64 msvsmon.exe on an ARM64 device, by overriding

the PackageArchitecture to neutral.



This is necessary in lieu of first-class Store support for ARM64EC apps.

Strategy:

* Create a self-contained WindowsAppSDK app, built for ARM64EC
* Target ARM64 in the appxmanifest.xml
* Ensure that all package dependencies are ARM64EC-compatible (such as VCLibs, which contains ARM64X binaries)

