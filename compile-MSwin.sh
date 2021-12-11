# This bashfile will run on Windows in an MSYS console.
gcc --version
gcc src/main.c -o "side cutters.exe" `pkg-config --cflags --libs gtk+-3.0`
echo Run: Double click 'side cutters.exe' - MS Windows executable 
echo Press any key. 
read
