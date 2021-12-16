#!/bin/bash
gcc --version | grep gcc | awk '{print $1" "$5}'
gcc --version | awk '/gcc/ && ($5+0)==11.2{print "Version is correct"}'
if [ -d "~/.Trash" ]; then thrash="~/.Trash"
fi
mkdir "Side Cutters.app/Contents/MacOS"
cp -R rsc "Side Cutters.app/Contents/Resources"
filename="src/config"
search="rsc/"
replace=$(pwd)
echo "I'm going to replace '${search}' with '${replace}/Side Cutters.app/Contents/Resources/rsc/' in '${filename}'"
echo "And I replace 'testpdf.pdf' with '${replace}/testpdf.pdf' in '${filename}'"
if [[ $search != "" && $replace != "" ]]; then
    sed -i "" "s|${search}|${replace}/Side Cutters.app/Contents/Resources/rsc/|" $filename
    sed -i "" "s|testpdf.pdf|${replace}/testpdf.pdf|" $filename
fi
cp $filename "Side Cutters.app/Contents/MacOS/config"
gcc src/main.c -o "Side Cutters.app/Contents/MacOS/Side-Cutters" `pkg-config --cflags --libs gtk+-3.0`
chmod +x "Side Cutters.app"
echo Run: Double click 'Side Cutters.app' - Apple MacOS application
echo Press any key. 
read
