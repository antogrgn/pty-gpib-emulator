##
## **** Prologix_GPIB_USB Class ****
##
## A Device that emulates the functionality of the
## Prologix GPIB-USB Controller (prologix.biz)
## 


import Device, PTY_Interface

class Prologix_GPIB_USB(Device.Device):

##%% Initialization - Prologix_GPIB_USB()
## Does not take arguments, but is VERY important
## All classes that attempt to inherit this class,
## must call this initialization.
##
## This creates a dictionary containing all the commands
## to be run. If this dictionary is not created, this class
## does nothing
##
    def __init__(self):
        self.cmds = { "++ver":self.version, # "COMMAND":HANDLER
                      "++addr":self.addr,
                      "++kill":self.kill}

##%% handleCMD(pty_interface, command, arguments)
## See Device.handleCMD documentation
##
## In Prologix_GPIB_USB, this function makes use of the
## map made in initialization to find the command and
## its associated handler, then call the handler and pass in
## the pty_interface and the arguments
##
    def handleCMD(self, fpl, cmd, args=[]):
        out = Device.Device.handleCMD(self, fpl, cmd, args)
        if out != "":
            return out
        elif cmd in self.cmds:
            return self.cmds[cmd](fpl, args)
        else:
            return ""

##%% version(pty, args)
## Returns the device version
##
    def version(self, fpl, args=[]):
        return "Prologix Version 1.1 Simulator (Python)"

##%% addr(pty, args)
## If no arguments are given, returns the current address
## of the pty interface
##
## if args are given, then an integer is parsed out of
## the first argument and set as the address. This ensures
## that a device exists at the following address
##
## Any errors return "ERROR"
##
    def addr(self, fpl, args=[]):
        if args == []:
            return str(fpl.addr)
        else:
            try:
                fpl.addr = int(args[0])
                if not fpl.addr in fpl.devices:
                    fpl.addDevice(PrologixAdapter(), fpl.addr)
                return ""
            except:
                return "ERROR"
##%% kill(pty, args)
## Stops the pty interface from running
##     
    def kill(self, fpl, args=[]):
        fpl.running = False
        return ""

##%% addCMD(command, handler_function)
## Adds a command to the dictionary
## Handler function must be of the form
## func(pty_interface, arguments):
##
    def addCMD(self, cmd, func):
        self.cmds[cmd] = func

