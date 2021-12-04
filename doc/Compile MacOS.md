
# Compile Side Cutters

How to compile on MacOS

## Install Xcode Command Line Tools

Xcode requires MacOS 10.12.6 or later. First, open the Mac App Store and install Xcode for free.
Then, open Xcode, go to Xcode menu (on the menu bar) > Preferences > Downloads, and install Command Line Tools.

### Earlier MacOS versions than 10.12.6

Whenever you go to download Xcode from the App Store, it tells you "Xcode can’t be installed on “Macintosh HD” because MacOS version 10.12.6 or later is required". There is another way of installing a GCC compiler.

1. Sign up for a "Free" Developer account
<https://developer.apple.com/register/index.action>

2. Then go to
<https://developer.apple.com/download/more>
and get a version of Xcode that works on your system. Xcode 4.2 may work, if not, get an older version.

Also get the command line tools.

### Optional

Apple does not include the actual GNU C/C++ compiler in the command-line tool for Xcode, or Xcode itself. The **gcc** "compatibility" command is a special build of clang/clang++ that is using older gcc compatibility.
To get the real GNU C/C++ package (and its libraries) installed into the /usr/local tree:

        Install Homebrew package manager
        $ brew update
        $ brew upgrade
        $ brew search gcc    # this will show several versions of it
        $ brew info gcc      # specific information on the current compiler including dependencies
        $ brew install gcc   # your MacBook Air on the charger
        $ brew cleanup       # free up disk space. Only run after brew upgrade has installed newer versions

## Compile and run tests

1.  Open the terminal and run the command ‘gcc -v’ to check if you have the compiler installed.
2.  Download the zipped code from https://github.com/Geert-Jan77/sidecutters green *code* button, https://github.com/Geert-Jan77/sidecutters/archive/refs/heads/main.zip and unzip. Find the "sidecutters-main" folder.
3.  Run the command <code>chmod +x compile.sh</code>
4.  <code>./compile.sh</code>
5.  <code>chmod +x "Side Cutters.app"</code>
6.  Double click the application *Side Cutters*. It is blocked from running because it is not downloaded from the App  Store.
7.  Choose Apple menu > System Preferences, click Security & Privacy, then click General.
8.  Click the lock icon to unlock the settings, then enter an administrator name and password.
9.  Click the [Open Anyway] button. It is right from the message *"Side Cutters" was blocked from use because it is not from an identified developer.*
10.  Run the application <code>"Side Cutters"</code> This runs a minimal Cocao application, our own forms will be created in there.
 
