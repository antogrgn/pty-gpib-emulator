#
# Device Class
#

import FakePrologix

class Device:
    def handleCMD(self, fpl, cmd, args=[]):
        return ""

class PrologixAdapter(Device):
    def __init__(self):
        self.cmds = { "++ver":self.version,
                      "++addr":self.addr,
                      "++kill":self.kill}

    def handleCMD(self, fpl, cmd, args=[]):
        out = Device.handleCMD(self, fpl, cmd, args)
        if out != "":
            return out
        elif cmd in self.cmds:
            return self.cmds[cmd](fpl, args)
        else:
            return ""

    def version(self, fpl, args=[]):
        return "Prologix Version 1.1 Simulator"

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
    
    def kill(self, fpl, args=[]):
        fpl.running = False
        return ""

    def addCMD(self, cmd, func):
        self.cmds[cmd] = func

