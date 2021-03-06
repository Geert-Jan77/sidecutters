# This bash script runs on MS Windows in an MSYS shell. 

docs=$(reg query "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" | grep Personal | awk '{print $3}')
docs="${docs//\\//}"
docs="${docs/C/c}"
echo "Document folder ${docs}"
desktop=$(reg query "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" | grep Desktop | awk '{print $3}')
desktop="${desktop//\\//}"
desktop="${desktop/C/c}"
echo "Desktop folder ${desktop}"
pictures=$(reg query "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" | grep 'My Pictures' | awk '{print $4}')
pictures="${pictures//\\//}"
pictures="${pictures/C/c}"  
echo "Pictures ${pictures}"
secondString="Downloads"
downloads="${desktop/Desktop/"$secondString"}"  
echo "Downloads ${downloads}"
sids=$(wmic useraccount get sid | awk '{print $0}')
dollar="$"
for f in $sids; 
do 
if [[ ${#f} -gt '40' ]]; then
if [ -d "c:\\${dollar}Recycle.Bin\\${f}" ]; then 
trash="c:\\${dollar}Recycle.Bin\\${f}"
fi
fi
done
trash="${trash//\\//}"
echo "Trash ${trash}"
startm=$(reg query "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" | grep 'Common Programs' | awk '{print $4 " " $5}')
startm="${startm//\\//}"
startm="${startm/C/c}"  
echo "Startmenu ${startm}"
filename="config"
cp "src/config" ${filename}
sed -i "s|trashfolder|${trash}|" ${filename}
workdir=$(pwd -W)
workdir="${workdir//\\//}"
workdir="${workdir/C/c}"
workdir="${workdir/D/d}"
sed -i "s|workingdirectory|${workdir}|" ${filename}
if [ -d "c:/Program Files" ]; then sed -i "s|appfolder|c:/Program Files|" ${filename}
fi
if [ -d "${downloads}" ]; then sed -i "s|downloadfolder|${downloads}|" ${filename}
fi
sed -i "s|documentfolder|${docs}|" ${filename}
sed -i "s|desktopfolder|${desktop}|" ${filename}
sed -i "s|picturefolder|${pictures}|" ${filename}
gcc --version | grep gcc | awk '{print $1" "$7}'
gcc --version | awk '/gcc/ && ($7+0)==11.2{print "Version is correct"}'
windres -i rsc/icon.rc -O coff -o rsc/icon.o
windres -i rsc/info.rc -O coff -o rsc/info.o
gcc src/main.c rsc/icon.o rsc/info.o -o "side cutters.exe" `pkg-config --cflags --libs gtk+-3.0`
echo Run: Double click 'side cutters.exe' - MS Windows executable 
apppath=$(pwd -W)
appname="Side Cutters"
shortcutdestinationpath=$startm
shortcutdestinationpath="${shortcutdestinationpath///\\}"
shortcutdestinationpath="${shortcutdestinationpath/c/C}"
printf "Set oWS = WScript.CreateObject(\"WScript.Shell\")\n" > CreateShortcut.vbs
echo "sLinkFile = \"${shortcutdestinationpath}/${appname}.lnk\"" >> CreateShortcut.vbs
echo "Set oLink = oWS.CreateShortcut(sLinkFile)" >> CreateShortcut.vbs
echo "oLink.TargetPath = \"${apppath}/${appname}.exe\"" >> CreateShortcut.vbs
echo "oLink.WorkingDirectory = \"${apppath}\"" >> CreateShortcut.vbs
echo "oLink.Description = \"${appname}\"" >> CreateShortcut.vbs
echo "oLink.IconLocation = \"${apppath}/rsc/${appname}.ico\"" >> CreateShortcut.vbs
echo "oLink.Save" >> CreateShortcut.vbs
cscript -nologo CreateShortcut.vbs
rm CreateShortcut.vbs
echo Press any key. 
read
