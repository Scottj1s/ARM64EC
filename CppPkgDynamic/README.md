# Windows App SDK C++ Packaged Dynamic Arm64EC Sample

This project demonstrates how to dynamically load the Windows App Runtime (WAR)
in a packaged self-contained app, enabling switching between x64 and ARM64EC
payloads as appropriate for the device architecture. This is necessary in lieu 
of first-class Store support for ARM64EC apps.

Strategy:
* Reference two WAR self-contained projects, one for x64 and one for ARM64EC
* The app is self-contained, but does not itself binplace the WAR binaries
* The app only merges the resource PRI files from the WAR payload
* URFW auto-init is disabled by setting WindowsAppSdkUndockedRegFreeWinRTInitialize=false
* A custom AutoInitializer is instead used to determine architecture at runtime
* The env var MICROSOFT_WINDOWSAPPRUNTIME_BASE_DIRECTORY is set to load the appropriate WAR
