##
## ****  PTY_Interface Class ****
## by Aidan Macdonald (aidan.plenert.macdonald@gmail.com)
## 
## This class generates a pty device that emulates the
## tty device created by GPIB controllers such as
## Prologix GPIB-USB Controller (prologix.biz)
## 
## This class does NOT emulate the controller, but the
## controller must be attached to this PTY Interface
## 
## I may switch between the terms tty device and pty device.
## They refer to the same thing.
##


import os
import Device, Prologix

class Interface:

##%% Initialization - Interface(default_device, default_address)
## accepts arguments default_device and default_address
## the default_device will be connected at the default_address
## 
## If the Interface address (PTY_Interface.addr) is changed, the
## no longer have anything attached and will become functionless.
## UNLESS, the default device handles the address change and copies itself
## to the new address (Prologix_GPIB_USB does this, OR there is
## another device attached there.
##
## if no arguments are given at initialization, defaults are
## Device.Prologix_GPIB-USB at address 0
##
    def __init__(self,
                 default_device=Prologix.Prologix_GPIB_USB(),
                 default_address=0 ):
        self.m, self.s = os.openpty()
        self.devices = {default_address:default_device}
        self.addr = default_address

##%% printFilename()
## Prints the path to the PTY device generated (ie /dev/pts/2)
##
    def printFilename(self):
        name = os.ttyname(self.s) 
        print(name)
        return name

##%% run(readLen)
## Runs the emulator which will read all statements written from the outside
## to the pty device at the location given by self.printFilename(), then
## runs what was read through self.handleInput(tty_in) and writes output
## back to the pty device to be read from the outside
##
    def run(self, readLen=100):
        self.running = True
        while (self.running):
            tty_in = os.read(self.m, readLen)
            for tty_out in self.handleInput(tty_in):
                os.write(self.m, tty_out)


##%% handleInput(tty_in)
## Recieves raw input that was read from the pty device, and 
## breaks it up and send it to the device listed at the current
## address. That device must handle the command via dev.handleCMD(cmd, args)
##
    def handleInput(self, tty_in):
        tty_in = tty_in.strip()

        if tty_in != "" and self.addr in self.devices:
            dev = self.devices[self.addr]
            for cmd in tty_in.strip().split(";"):
                p = cmd.strip().split(" ")
                yield dev.handleCMD(self, p[0], p[1:]) + "\n"

        yield ""  # Must be a null string to prevent infinite loop

##%% addDevice(device, address)
## Preferred way of connecting a device to the interface
## at a given address
##
    def addDevice(self, dev, addr):
        self.devices[addr] = dev
        

