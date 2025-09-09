# Windows App SDK ARM64EC Samples

Windows App SDK 1.7 introduced experimental support for building ARM64EC apps, subject to several constraints:

* Support is currently limited to Self-Contained Unpackaged apps.  These two limitations are both related to the
fact that the Windows Store does not yet support ARM64EC as a first-class architecture.  So the app must not be
packaged, as the app appxmanifest.xml has no ARM64EC support; and it must be self-contained, as the Windows App
Runtime framework package has no ARM64EC support.
* For managed apps, ARM64EC optimization is limited to the Windows App Runtime, as .NET does not yet support it.
