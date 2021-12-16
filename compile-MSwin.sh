# This bash script runs on MS Windows in an MSYS shell. 

# Find the documents folder
@echo off
for /f "skip=2 tokens=2*" %%c in ('reg query "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" /v "Personal"') do @set "Documents=%%d" && echo WIN XP - 10
# xcopy "C:\test.txt" "%docs%" /f /y
echo %docs%

Echo current users desktop
for /f "skip=2 tokens=2*" %%c in ('reg query "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" /v "Desktop"') do @set "Desktop=%%d"

Echo current users documents
for /f "skip=2 tokens=2*" %%c in ('reg query "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" /v "Personal"') do @set "Documents2=%%d"

Echo current user start menu
for /f "skip=2 tokens=3*" %%c in ('reg query "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" /v "Start Menu"') do @set "Start=%%d"

Echo current user startup
for /f "skip=2 tokens=2*" %%c in ('reg query "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" /v "Startup"') do @set "Startup=%%d"

Echo current users pictures
for /f "skip=2 tokens=3*" %%c in ('reg query "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" /v "My Pictures"') do @set "Pictures=%%d"

gcc --version | grep gcc | awk '{print $1" "$7}'
gcc --version | awk '/gcc/ && ($7+0)==11.2{print "Version is correct"}'
windres -i rsc/icon.rc -O coff -o rsc/icon.o
windres -i rsc/info.rc -O coff -o rsc/info.o
gcc src/main.c rsc/icon.o rsc/info.o -o "side cutters.exe" `pkg-config --cflags --libs gtk+-3.0`
echo Run: Double click 'side cutters.exe' - MS Windows executable 
echo Press any key. 
read
