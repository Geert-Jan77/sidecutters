#!/bin/bash
gcc --version | grep gcc | awk '{print $1" "$5}'
gcc --version | awk '/gcc/ && ($5+0)==11.2{print "Version is correct"}'
mkdir "Side Cutters.app/Contents/MacOS"
cp -R rsc "Side Cutters.app/Contents/Resources"
filename="src/main_.c"
cp src/main.c $filename
search="rsc/"
replace=$(pwd)
echo "I'm going to replace '${search}' with '${replace}/Side Cutters.app/Contents/Resources/rsc/' in '${filename}'"
if [[ $search != "" && $replace != "" ]]; then
sed -i "" "s|${search}|${replace}/Side Cutters.app/Contents/Resources/rsc/|" $filename
fi
gcc src/main_.c -o "Side Cutters.app/Contents/MacOS/Side-Cutters" `pkg-config --cflags --libs gtk+-3.0`
chmod +x "Side Cutters.app"
echo Run: Double click 'Side Cutters.app' - Apple MacOS application
echo Press any key. 
read
