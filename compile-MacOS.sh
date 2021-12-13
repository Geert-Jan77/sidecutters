gcc --version
mkdir "Side Cutters.app/Contents/MacOS"
cp -R rsc "Side Cutters.app/Contents/MacOS/rsc"
gcc src/main.c -o "Side Cutters.app/Contents/MacOS/Side-Cutters" `pkg-config --cflags --libs gtk+-3.0`
chmod +x "Side Cutters.app"
echo Run: Double click 'Side Cutters.app' - Apple MacOS application
echo Press any key. 
read
