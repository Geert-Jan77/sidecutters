gcc src/test/testpdf.c -o testpdf.exe
windres rsc/icon.rc -O coff -o rsc/icon.res  
windres rsc/info.rc -O coff -o rsc/info.res  
gcc "src/side cutters.c" rsc/icon.res rsc/info.res -o "side cutters.exe"
pause