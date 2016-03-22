# Introduction #

The goal of this tutorial is to teach how to connect devices to the emulator to use.


# Details #

Take a look at the fake\_prologix.py code

```
#!/usr/bin/python

import PTY_Interface
import PowerSupply

pty = PTY_Interface.Interface()
pty.addDevice(PowerSupply.PowerSupply(), 5)
pty.addDevice(PowerSupply.E3631A(), 3)

pty.printFilename()
pty.run()
```

In order to add another device (or remove one), one must modify the lines that say: "pty.addDevice( ... )". These lines cause the PTY\_Interface to add another device. All of this must be done before calling "pty.run()" as that will cause the emulator to run without having connected the device. See PTY\_Interface for more information

For example:

adding the following lines before a run call will add a Keithley 2400 at port 7
```
import SourceMeasurement
pty.addDevice(SourceMeasurement.Keithley_2400(), 7)
```