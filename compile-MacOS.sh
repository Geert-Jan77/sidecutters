#!/bin/bash
gcc --version | grep gcc | awk '{print $1" "$5}'
gcc --version | awk '/gcc/ && ($5+0)==11.2{print "Version is correct"}'

mkdir "Side Cutters.app/Contents/MacOS"
cp -R rsc "Side Cutters.app/Contents/Resources"
filename="src/main_.c"
cp "src/main.c" ${filename}
search="config"
replace=$(pwd)
if [[ $search != "" && $replace != "" ]]; then sed -i "" "s|${search}|${replace}/Side Cutters.app/Contents/MacOS/config_|" ${filename}
fi
filename="src/config_"
cp "src/config" ${filename}
if [ -d "${HOME}/.Trash" ]; then sed -i "" "s|trashfolder|${HOME}/.Trash|" ${filename}
fi
search="rsc/"
replace=$(pwd)
sed -i "" "s|workingdirectory|${replace}|" ${filename}
if [ -d "/Applications" ]; then sed -i "" "s|appfolder|/Applications|" ${filename}
fi
if [ -d "${HOME}/Downloads" ]; then sed -i "" "s|downloadfolder|${HOME}/Downloads|" ${filename}
fi
if [ -d "${HOME}/Documents" ]; then sed -i "" "s|documentfolder|${HOME}/Documents|" ${filename}
fi
if [ -d "${HOME}/Desktop" ]; then sed -i "" "s|desktopfolder|${HOME}/Desktop|" ${filename}
fi
if [ -d "${HOME}/Pictures" ]; then sed -i "" "s|picturefolder|${HOME}/Pictures|" ${filename}
fi
echo "I'm going to replace '${search}' with '${replace}/Side Cutters.app/Contents/Resources/rsc/' in '${filename}'"
echo "And I replace 'testpdf.pdf' with '${replace}/testpdf.pdf' in '${filename}'"
if [[ $search != "" && $replace != "" ]]; then
    sed -i "" "s|${search}|${replace}/Side Cutters.app/Contents/Resources/rsc/|" ${filename}
    sed -i "" "s|testpdf.pdf|${replace}/testpdf.pdf|" ${filename}
fi
cp ${filename} "Side Cutters.app/Contents/MacOS/config_"
gcc src/main_.c -o "Side Cutters.app/Contents/MacOS/Side-Cutters" `pkg-config --cflags --libs gtk+-3.0`
chmod +x "Side Cutters.app"
echo Run: Double click 'Side Cutters.app' - Apple MacOS application
echo Press any key. 
read
