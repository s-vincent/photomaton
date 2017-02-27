# photomaton
Photomaton-like application for parties.

The application shows camera streams and is able to take series of three
pictures with countdown.

It is typically to be used in weddings, parties, and other fun place to have
good souvenirs of you guests!

It is up to you to combine this project with another to put in form the
pictures and print it!

## Pre-requisites

Qt 5 must be installed to run the application.

Qt 5 development files is need for compiling.

## Taking pictures

To launch the procedure of taking pictures, simply press any keys.

The pictures will be written in the images/ directory of the current path.

When the three pictures are done, the application writes a file called
dummy.dmy in the images/ directory and wait for its deletion to again be able
to take pictures. This mechanism can be useful so that another script can
put in form the three pictures and launch printing!

## Cheat codes

To be able to survive a party, the application should not be shutdown, camera
should not be changed... To achieve that, the application has some limitations
such as clicking on cross/ALT-F4 do not quit the application.

However application propose a set of cheat codes to perform some actions :
- Holds shift and type AK84: exit the application and remove dummy.dmy;
- Holds shift and type AK85: reset timers / counters and remove dummy.dmy;
- Holds shift and type AK86: use the next camera.
- Holds shift and type AK87: go in fullscreen mode;
- Holds shift and type AK88: exit fullscreen mode.

## License

The code is based on camera example from Qt Multimedia and thus source code is
under BSD-3 license.

