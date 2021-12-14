# This bash script runs on MS Windows in an MSYS shell. 
gcc --version | grep gcc | awk '{print $1" "$7}'
gcc --version | awk '/gcc/ && ($7+0)==11.2{print "Version is correct"}'
windres -i rsc/icon.rc -O coff -o rsc/icon.o
windres -i rsc/info.rc -O coff -o rsc/info.o
gcc src/main.c rsc/icon.o rsc/info.o -o "side cutters.exe" `pkg-config --cflags --libs gtk+-3.0`
#gcc src/main.c -o "side cutters.exe" `pkg-config --cflags --libs gtk+-3.0`
echo Run: Double click 'side cutters.exe' - MS Windows executable 
echo Press any key. 
read
