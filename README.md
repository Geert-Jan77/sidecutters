# Side Cutters 
CAD Software
                                                                                                                                                   
<img src="/rsc/icon.png" alt="a screenshot of the program so far"/>   

**Free CAD Software**

*The millimetre you see is the millimetre you get*                                     
                                                                                                                                                             
## Aim
This software should be free. The aim of this project is to create a multi platform app while starting from a windows platform.
It should create electrical drawings automatically and export them as bookmarked portable datafile (pdf). We only use SI units for the drawings. Even the fontheight will be given in millimetre instead of points (1/72 inch).We define our quality standard now in four points:

- The choice of the Side Cutter icon is not a coincidence, a wiring diagram should include the length of all wires because someone in your organisation has to cut them.
- The electrical drawings are easy to read: The wiring diagram has pages and columns, wires continue from one page to another.
- Wires are drawn in the real color they have due to color coding.
- It should take no longer than a few minutes to draw a complete system. Automatic drawing and easy sketching are of key importance.

## How?
The software is licensed GPL/LGPL version 2. The Compiler is gcc 11.2.0, not Microsoft Visual Studio and the project is written in C, not in C#. 
Windows operating system functionality is never used, and the application is not on the Windows API but the GTK 3 API. Even the GTK 3 backbone will barely be used, and the focus is on the Cairo drawing surface. This project will have no build system other than a simple *batch* or *bash* file. Its only dependency will be GTK 3. 

## A table
The user of the program will select components and edit the connections between them. This is done in a **table** 
He will press the *Generate* button with the *Side Cutter* icon and all the drawing's pages are generated automatically.

## I want this software!

It's not ready yet, but you should compile it and contribute to the project. Read the [*doc*](/doc) folder on how to compile for MacOS or MS Windows.

<img src="/doc/pica10a.png" alt="a screenshot of the program so far" width="50%"/><img src="/doc/pica11a.png" alt="a screenshot of the program so far" width="50%"/>
