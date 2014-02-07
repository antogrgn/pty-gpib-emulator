##
## <<<< Source Measurement Unit Emulators >>>>
## by Aidan Macdonald (aidan.plenert.macdonald@gmail.com)
##
## Contains classes that emulate Source Measurement Units
##

import Device, Prologix

## **** Source Measurement Class ****
## by Aidan Macdonald (aidan.plenert.macdonald@gmail.com)
##
## General model of a basic Source Measurement Unit
##

class SourceMeasurement(Prologix.Prologix_GPIB_USB):
    
##%% Initialization SourceMeasurement()
## Creates the framework
##

    def __init__(self):
        Prologix.Prologix_GPIB_USB.__init__(self)



## **** Keithley 2400 Class ****
## by Aidan Macdonald
## 
## Support given for some commands
##

from random import uniform as rand

class Keithley_2400(SourceMeasurement):

##%% Initialization - Keithley_2400()
## Loads commands
##

def __init__(self):
    SourceMeasurement.__init__(self)
    self.addCMD("IDN?", self.version)
    self.addCMD("*RST", self.noth)
    self.addCMD("*CLS", self.noth)
    self.addCMD("ABOR", self.noth)
    self.addCMD("*CLS", self.noth)
    self.addCMD("SYST:BEEP:STAT", self.noth)
    self.addCMD("SOURCE:CLEAR:AUTO", self.noth)
    self.addCMD("FORM:ELEM", self.noth)
    self.addCMD(":SOUR:FUNC", self.noth)
    self.addCMD("read?", self.randFloats)

## noth(pty, args)
## Does nothing
##
def noth(self, fpl, args):
    pass # Do nothing


def version(self, fpl, args):
    return 'KEITHLEY INSTRUMENTS INC.,MODEL 2400.EMULATOR'

## randFloats(pty, args)
## returns a string of random floats
##
def randFloats(self, fpl, args):
    return str(rand(0, 2)) + ", " str(rand(0, 2))

## handleCMD(fpl, cmd, args)
## Modified to be case insensitive
##
def handleCMD(self, fpl, cmd, args):
    SourceMeasurement.handleCMD(self, fpl, cmd.upper(), args)


    
