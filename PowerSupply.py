##
## <<<< Powersupply Emulators >>>>
## by Aidan Macdonald (aidan.plenert.macdonald@gmail.com)
## 
## Contains classes that emulate powersupplies by
## building off the Device framework
## 

import Device, Prologix

## **** Power Supply class ****
## by Aidan Macdonald (aidan.plenert.macdonald@gmail.com) 
##
## General model of a basic Power Supply
## 

class PowerSupply(Prologix.Prologix_GPIB_USB):

##%% Initialization PowerSupply(volt, current)
## Creates a framework for a Powersupply, but only binds
## a reset call to "RST?". All other functions have been
## left unbound so that children can bind them to respective
## commands
##
## voltage and current default to 10
##
    def __init__(self, volt=10, cur=10):
        Prologix.Prologix_GPIB_USB.__init__(self)
        self.addCMD("RST?", self.reset)

        self.voltage = volt
        self.current = cur

##%% reset(pty, args)
## returns that the device has been reset
##
    def reset(self, fpl, args=[]):
        return "Power Supply has been reset"

##%% version(pty, args)
## overrides the version function from superclass
## left unbound here, because it was bound in the
## superclass.
##
    def version(self, fpl, args=[]):
        return "Power Supply Version 1.GEN"

##%% on(pty, args)
## turns power supply on
##
    def on(self, fpl, args=[]):
        return self.version(fpl, args) + " in now ON"
##%% off(pty, args)
## turns power supply off
##
    def off(self, fpl, args=[]):
        return self.version(fpl, args) + " in now OFF"

##%% getVoltage(pty, args)
## returns voltage
##
    def getVoltage(self, fpl, args=[]):
        return self.voltage

##%% getCurrent(pty, args)
## returns current
##
    def getCurrent(self, fpl, args=[]):
        return self.current


##%% setVoltage(pty, args)
## sets voltage
##
    def setVoltage(self, fpl, args=[]):
        try:
            self.voltage = float(args[0])
            return ""
        except:
            return "ERROR"
##%% setCurrent(pty, args)
## sets current
##
    def setCurrent(self, fpl, args=[]):
        try:
            self.current = float(args[0])
            return ""
        except:
            return "ERROR"


##
## **** E3631A Power Supply Class ****
## by Aidan Macdonald (aidan.plenert.macdonald@gmail.com)
## 
## Emulates the E3631A Power Supply
## 
    
class E3631A(PowerSupply):
##%% Initialization - E3631A(voltage, current)
## see PowerSupply.PowerSupply documentation
## 
## adds bindings for all of the PowerSupply functions
##
    def __init__(self, volt=10, cur=10):
        PowerSupply.__init__(self, volt, cur)

        self.addCMD("OUTP", self.outp)
        self.addCMD("MEAS:VOLT:DC", self.getVoltage)
        self.addCMD("MEAS:CURR:DC", self.getCurrent)
        self.addCMD("SET:VOLT:DC", self.setVoltage)
        self.addCMD("SET:CURR:DC", self.setCurrent)

##%% version(pty, args)
## returns version
##
    def version(self, fpl, args=[]):
        return "E3631A Power Supply"

##%% outp(pty, args)
## function binding for the "OUTP" command
## Used to turn the device on and off
##
    def outp(self, fpl, args=[]):
        if args[0] == "ON":
            return self.on(fpl, args)
        elif args[0] == "OFF":
            return self.off(fpl, args)
        return ""
