# Side Cutters 
CAD Software
                                                                                                                                                   
<img src="/rsc/icon.png" alt="a screenshot of the program so far"/>   

**Free CAD Software**

*The millimetre you see is the millimetre you get*                                     
                                                                                                                                                             
## Aim
This software should be free. The aim of this project is to create a multi platform app while starting from a windows platform.
It should create electrical drawings automatically and export them as bookmarked portable datafile (pdf). We only use SI units for the drawings. Even the fontheight will be given in millimetre instead of points (1/72 inch).

## How?
The software is licensed GPL/LGPL version 2. The Compiler is gcc, not Microsoft Visual Studio and the project is written in C, not in C#. 
If Windows operating system functionality is used, we import the operating system's dynamical linked library. Windows forms will not be used, we create our own forms instead. This project will have no dependencies.

The software is licensed GPL/LGPL version 2. The Compiler is gcc 11.2.0, not Microsoft Visual Studio and the project is written in C, not in C#. 
Windows operating system functionality is never used, and the application is not on the Windows API but the GTK 3 API. Even the GTK 3 backbone will barely be used, and the focus is on the Cairo drawing surface. This project will have no build system other than a simple *batch* or *bash* file. Its only dependency will be GTK 3. 

## A table
The user of the program will select components and edit the connections between them. This is done in a **table** 
He will press the *Generate* button with the *Side Cutter* icon and all the drawing's pages are generated automatically.

## I want this software!

Then maybe you should help program it. Start by compiling the source on your pc. Read the *doc* folder on how to compile.
It's not ready yet, but you should compile it contribute to the project. Read the *doc* folder on how to compile for MacOS or MS Windows.

<img src="/doc/pica1.png" alt="a screenshot of the program so far" width="50%"/><img src="/doc/pica2.png" alt="a screenshot of the program so far" width="50%"/>
