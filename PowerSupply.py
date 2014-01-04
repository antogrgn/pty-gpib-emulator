#
# Powersupply Emulator
#

import Device

class PowerSupply(Device.PrologixAdapter):
    def __init__(self, volt=10, cur=10):
        Device.PrologixAdapter.__init__(self)
        self.addCMD("RST?", self.reset)

        self.voltage = volt
        self.current = cur

    def reset(self, fpl, args=[]):
        return "Power Supply has been reset"

    def version(self, fpl, args=[]):
        return "Power Supply Version 1.GEN"

    def on(self, fpl, args=[]):
        return self.version(fpl, args) + " in now ON"

    def off(self, fpl, args=[]):
        return self.version(fpl, args) + " in now OFF"

    def getVoltage(self, fpl, args=[]):
        return self.voltage

    def getCurrent(self, fpl, args=[]):
        return self.current

    def setVoltage(self, fpl, args=[]):
        try:
            self.voltage = float(args[0])
            return ""
        except:
            return "ERROR"

    def setCurrent(self, fpl, args=[]):
        try:
            self.current = float(args[0])
            return ""
        except:
            return "ERROR"

    
class E3631A(PowerSupply):
    def __init__(self, volt=10, cur=10):
        PowerSupply.__init__(self, volt, cur)

        self.addCMD("OUTP", self.outp)
        self.addCMD("MEAS:VOLT:DC", self.getVoltage)
        self.addCMD("MEAS:CURR:DC", self.getCurrent)
        self.addCMD("SET:VOLT:DC", self.setVoltage)
        self.addCMD("SET:CURR:DC", self.setCurrent)

    def version(self, fpl, args=[]):
        return "E3631A Power Supply"

    def outp(self, fpl, args=[]):
        if args[0] == "ON":
            return self.on(fpl, args)
        elif args[0] == "OFF":
            return self.off(fpl, args)
        return ""
