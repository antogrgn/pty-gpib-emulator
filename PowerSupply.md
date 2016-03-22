> # Powersupply Emulators #
> by Aidan Macdonald (aidan.plenert.macdonald@gmail.com)

> Contains classes that emulate powersupplies by
> building off the Device framework

> ## Power Supply class ##
> by Aidan Macdonald (aidan.plenert.macdonald@gmail.com)

> General model of a basic Power Supply

**Initialization PowerSupply(volt, current)
> Creates a framework for a Powersupply, but only binds
> a reset call to "RST?". All other functions have been
> left unbound so that children can bind them to respective
> commands**

> voltage and current default to 10

**reset(pty, args)
> returns that the device has been reset**

**version(pty, args)
> overrides the version function from superclass
> left unbound here, because it was bound in the
> superclass.**

**on(pty, args)
> turns power supply on**

**off(pty, args)
> turns power supply off**

**getVoltage(pty, args)
> returns voltage**

**getCurrent(pty, args)
> returns current**

**setVoltage(pty, args)
> sets voltage**

**setCurrent(pty, args)
> sets current**


> ## E3631A Power Supply Class ##
> by Aidan Macdonald (aidan.plenert.macdonald@gmail.com)

> Emulates the E3631A Power Supply

**Initialization - E3631A(voltage, current)
> see PowerSupply.PowerSupply documentation**

> adds bindings for all of the PowerSupply functions

**version(pty, args)
> returns version**

**outp(pty, args)
> function binding for the "OUTP" command
> Used to turn the device on and off**
