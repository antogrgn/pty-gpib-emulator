PTY-GPIB-Emulator


A GPIB Instrument Emulator written to receive and respond to commands given
to a generated PTY device under a Unix Environment. The goal of this emulator
is to emulate the functions of the Controller. It does so by taking advantage
of pty (man pty) and openpty (man openpty) in Python.

Originally developed to emulate commands given to a Prologix GPIB-USB Controller
(prologix.biz) and return the sample responses.

Written in Python, it can, and will be, extended to emulate many different
devices that accessed via GPIB. This project is written completely in Python,
so make sure you have it installed. The default Python install should include
the functions needed to run this project.


If you would like to have support added for a specific device, please contact me
and I would be happy to add support for your device.

 HOW TO RUN THE PROGRAM 

$ ./fake\_prologix.py
# This should print something like the line below
/dev/pts/2

# That is where the pts device is at. Once you have done this, you can follow the
# instructions as "http://heliosoph.mit-links.info/gpib-on-debian-linux-the-easy-way/"
# replacing /dev/ttyUSB0 with /dev/pts/2 (or whatever you got from the above instructions)

# Namely in another terminal run
$ cat < /dev/pts/2

# In yet another terminal, test the emulator by echoing in commands

$ echo "++ver" > /dev/pts/2
$ echo "++addr" > /dev/pts/2
$ echo "++addr 12" > /dev/pts/2
$ echo "++ver; ++addr" > /dev/pts/2


 Alternative, in one terminal 

# Do simultaneous processes
$ ./fake\_prologix.py &
$ cat < /dev/pts/2 &

# Commands