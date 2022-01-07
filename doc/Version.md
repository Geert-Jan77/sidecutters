## Version

All GPU and all monitors in `doc/Display.md`, the `english` language, and the device architecture `x86_64` are supported.
The version is in this project `Side Cutters.app/Contents/Info.plist` and `rsc/info.rc`

A version is fully debugged and tested, defined as 

`va.b` 

where `a` is the OS supported 
1. {MS windows x64, MacOS} 
2. {MS windows x64, MacOS, Ubuntu} 
3. {MS windows x64, MacOS, Ubuntu, Fedora} 
4. {MS windows x64, MacOS, Ubuntu, Fedora, FreeBSD}
5. {MS windows x64, MacOS, Ubuntu, Fedora, FreeBSD, OpenBSD}
6. {MS windows x64, MacOS, Ubuntu, Fedora, FreeBSD, OpenBSD, NetBSD}
7. {MS windows x64, MacOS, Ubuntu, Fedora, FreeBSD, OpenBSD, NetBSD, Solaris}

`b` is the functionality that is tested **OKAY** on all supported platforms
1. Draw all defined objects on display *doc/Drawobjects.md*         
2. Draw all objects on Pdf surface      
3. Import Dxf drawing
4. Add drawing templates for all defined rail-mounted electric devices *doc/Drawdevices.md*              
5. Create *Side Cutters Project* - auto-generate electrical drawing by pressing the *Side Cutters* button  
6. Display the app in a webbrowser. Android and iOS platforms can use a server running Side Cutters online.

