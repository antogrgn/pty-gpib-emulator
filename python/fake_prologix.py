#!/usr/bin/python

import PTY_Interface
import PowerSupply

pty = PTY_Interface.Interface()
pty.addDevice(PowerSupply.PowerSupply(), 5)
pty.addDevice(PowerSupply.E3631A(), 3)

pty.printFilename()
pty.run()
      	 
