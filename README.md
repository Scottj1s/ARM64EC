# Windows App SDK ARM64EC Samples

Windows App SDK 1.7 introduced experimental support for building ARM64EC apps, subject to several constraints.

* For managed apps, ARM64EC optimization is limited to the Windows App Runtime, as .NET does not yet support it.
* Direct support is currently limited to Self-Contained Unpackaged apps.  These two limitations are both related
and due to the fact that the Windows Store does not yet support ARM64EC as a first-class architecture.  So the app 
must not be packaged, as the app appxmanifest.xml has no ARM64EC support; and it must be self-contained, 
as the Windows App Runtime framework package has no ARM64EC support.
* However, it is possible to create a Packaged ARM64EC app by dynamically loading the appropriate Windows App Runtime.
This strategy, while not directly supported by the Windows App SDK, is demonstrated in the C++ Packaged sample. 
This sample contains two projects that build self-contained Windows App Runtime payloads, one for x64 and one for ARM64EC.
The app then detects the target architecture at runtime and loads the appropriate payload.
