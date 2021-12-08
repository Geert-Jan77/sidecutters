
# Compile Side Cutters

How to compile on MacOS

## Install Xcode Command Line Tools

Xcode requires MacOS 10.12.6 or later. 
1. Open the Mac App Store and install Xcode for free.

2. Open Xcode, go to Xcode menu (on the menu bar) > Preferences > Downloads, and install Command Line Tools.

### Earlier MacOS versions than 10.12.6

Whenever you go to download Xcode from the App Store, it tells you "Xcode can’t be installed on “Macintosh HD” because MacOS version 10.12.6 or later is required". There is another way of installing a GCC compiler.

1. Sign up for a "Free" Developer account
<https://developer.apple.com/register/index.action>

2. Then go to
<https://developer.apple.com/download/more>
and get a version of Xcode that works on your system. Xcode 4.2 may work, if not, get an older version.

Also get the command line tools.

### Install Brew and GCC 11.2.0

Apple does not include the actual GNU C/C++ compiler in the command-line tool for Xcode. The **gcc** "compatibility" command is a special build of clang/clang++ that is using older gcc compatibility. It is gcc 4.2.1 at the time of writing.
To get the real GNU C/C++ package (and its libraries) installed into the /usr/local tree:
1. Install Homebrew package manager
        
        % git -C /usr/local/Homebrew/Library/Taps/homebrew/homebrew-core fetch --unshallow
        % brew update
        % brew upgrade
        
2. Require the required right compiler version
        
        % brew install gcc@11
        
3. Free up disk space
        
        % brew cleanup
        
4. Check if the system still uses the gcc from Xcode
        
        % which gcc
        /usr/bin/gcc
        
5. Check if /usr/local/bin/ is before /usr/bin in your path system variable.  
        
        % echo $PATH
        /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/share/dotnet
        
6. Make a new symbolic link to gcc. Homebrew links gcc under /usr/local/bin/gcc-<version> for compatibility. So, doing
        
        % ln -sf /usr/local/bin/gcc-11 /usr/local/bin/gcc
        
   will point a /usr/local/bin/gcc symlink to gcc-11 installed by Homebrew. This overrides the gcc from /usr/bin

7. Quit Xcode and the terminal, start a new terminal and check       
 
        % which gcc
        /usr/local/bin/gcc
        
8. Check the compiler version
        
        % gcc -v
        gcc version 11.2.0 (Homebrew GCC 11.2.0_3) 
        
## Install GTK
        
        % brew install gtk+3
        

## Compile and run tests

1.  Open the terminal and run the command ‘gcc -v’ to check if you have the compiler version 11.2.0
2.  Download the zipped code from https://github.com/Geert-Jan77/sidecutters green *code* button, https://github.com/Geert-Jan77/sidecutters/archive/refs/heads/main.zip and unzip. Find the "sidecutters-main" folder.
3.  Run the command <code>chmod +x compile.sh</code>
4.  <code>./compile.sh</code>
5.  <code>chmod +x "Side Cutters.app"</code>
6.  Double click the application *Side Cutters*. It is blocked from running because it is not downloaded from the App  Store.
7.  Choose Apple menu > System Preferences, click Security & Privacy, then click General.
8.  Click the lock icon to unlock the settings, then enter an administrator name and password.
9.  Click the [Open Anyway] button. It is right from the message *"Side Cutters" was blocked from use because it is not from an identified developer.*
10.  Run the application *Side Cutters*. This runs a minimal GTK user interface, our own forms will be created in there.
 
