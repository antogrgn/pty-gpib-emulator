#
# Prologix Simulator Class
#


import os
import Device

class FakePrologix:
    def __init__(self):
        self.m, self.s = os.openpty()
        self.devices = {0:Device.PrologixAdapter()}
        self.addr = 0
        
    def printTTY(self):
        print(os.ttyname(self.s))
        
    def run(self, readLen=100):
        self.running = True
        while (self.running):
            tty_in = os.read(self.m, readLen)
            for tty_out in self.handleInput(tty_in):
                os.write(self.m, tty_out)

    def handleInput(self, tty_in):
        tty_in = tty_in.strip()

        if tty_in != "" and self.addr in self.devices:
            dev = self.devices[self.addr]
            for cmd in tty_in.strip().split(";"):
                p = cmd.strip().split(" ")
                yield dev.handleCMD(self, p[0], p[1:]) + "\n"

        yield ""  # Must be a null string to prevent infinite loop

    def handleCMDs(self, cmd, args=[]):
        return True

    def addDevice(self, dev, addr):
        self.devices[addr] = dev
        
