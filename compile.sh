gcc --version
mkdir "Side Cutters.app/Contents/MacOS"
gcc src/main.c -o "Side Cutters.app/Contents/MacOS/Side-Cutters" `pkg-config --cflags --libs gtk+-3.0`
chmod +x "Side Cutters.app"
echo Run: Double click Side Cutters app
