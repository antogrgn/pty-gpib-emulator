#!/usr/bin/python

import FakePrologix
import PowerSupply

pty = FakePrologix.FakePrologix()
pty.addDevice(PowerSupply.PowerSupply(), 5)
pty.addDevice(PowerSupply.E3631A(), 3)

pty.printTTY()
pty.run()
      	 
