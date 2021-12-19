@echo off
gcc -v 1> gcc 2>&1
rem This creates a file called gcc containing the output of gcc -v, and we will delete it later.
find gcc "gcc version"
find gcc "gcc version 11.2.0" && echo gcc version 11.2.0 found. || echo Compiler gcc version 11.2.0 not found. && goto Einde
@echo on
gcc src/test/testpdf.c -o testpdf.exe
gcc src/test/testsound.c -o testsound.exe
windres rsc/icon.rc -O coff -o rsc/icon.res  
windres rsc/info.rc -O coff -o rsc/info.res  
gcc "src/side cutters.c" rsc/icon.res rsc/info.res -o "side cutters.exe"
:Einde
@echo off
del gcc
pause