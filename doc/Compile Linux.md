( This doc is a work in progress )<br>
# Compile Side Cutters
How to compile on Fedora or Ubuntu linux

## Fedora

In Fedora 19, GTK+ has been built with Wayland and X11 support, so all you need to try it is a Wayland compositor. Weston, the reference Wayland compositor, is available in the weston package.

    $ yum install weston
    $ weston &

This will run weston as an X client. clicking on the terminal icon in the weston panel will give you a terminal window. Inside there, you can run GTK+ applications like this:

    $ GDK_BACKEND=wayland
    $ export GDK_BACKEND
    $ side-cutters

## Ubuntu

## Slackware
