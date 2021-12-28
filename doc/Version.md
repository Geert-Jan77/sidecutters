## Version

A version is defined as 
`va.b` 

where a is the OS supported 
1. {MS windows x64, MacOS} 
2. {MS windows x64, MacOS, Linux} 
3. {MS windows x64, MacOS, Linux, FreeBSD}
4. {MS windows x64, MacOS, Linux, FreeBSD, OpenBSD}
5. {MS windows x64, MacOS, Linux, FreeBSD, OpenBSD, NetBSD}
6. {MS windows x64, MacOS, Linux, FreeBSD, OpenBSD, NetBSD, AIX}
7. {MS windows x64, MacOS, Linux, FreeBSD, OpenBSD, NetBSD, AIX, Solaris}
8. {MS windows x64, MacOS, Linux, FreeBSD, OpenBSD, NetBSD, AIX, Solaris, HP-UX}

where `b` is the functionality that is tested **OKAY** on all operating systems defined in `a`
1. Draw all defined objects on display *doc/Drawobjects.md*         
2. Draw all objects on Pdf surface      
3. Import Dxf drawing
4. Add drawing templates for all defined rail-mounted electric devices *doc/Drawdevices.md*              
5. Create *Side Cutters Project* - auto-generate electrical drawing by pressing the *Side Cutters* button  
