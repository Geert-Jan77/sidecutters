#!/bin/bash
gcc --version
mkdir "Side Cutters.app/Contents/MacOS"
cp -R rsc "Side Cutters.app/Contents/Resources"
filename="src/main.c"
search="rsc/"
replace=$(pwd)
echo "I'm going to replace '${search}' with '${replace}/Side Cutters.app/Contents/Resources/rsc/' in '${filename}'"
if [[ $search != "" && $replace != "" ]]; then
sed -i "" "s|${search}|${replace}/Side Cutters.app/Contents/Resources/rsc/|" $filename
fi
gcc src/main.c -o "Side Cutters.app/Contents/MacOS/Side-Cutters" `pkg-config --cflags --libs gtk+-3.0`
chmod +x "Side Cutters.app"
echo Run: Double click 'Side Cutters.app' - Apple MacOS application
echo Press any key. 
read
