> ## Prologix\_GPIB\_USB Class ##

> A Device that emulates the functionality of the
> Prologix GPIB-USB Controller (prologix.biz)

**Initialization - Prologix\_GPIB\_USB()
> Does not take arguments, but is VERY important
> All classes that attempt to inherit this class,
> must call this initialization.**

> This creates a dictionary containing all the commands
> to be run. If this dictionary is not created, this class
> does nothing

**handleCMD(pty\_interface, command, arguments)
> See Device.handleCMD documentation**

> In Prologix\_GPIB\_USB, this function makes use of the
> map made in initialization to find the command and
> its associated handler, then call the handler and pass in
> the pty\_interface and the arguments

**version(pty, args)
> Returns the device version**

**addr(pty, args)
> If no arguments are given, returns the current address
> of the pty interface**

> if args are given, then an integer is parsed out of
> the first argument and set as the address. This ensures
> that a device exists at the following address

> Any errors return "ERROR"

**kill(pty, args)
> Stops the pty interface from running**

**addCMD(command, handler\_function)
> Adds a command to the dictionary
> Handler function must be of the form
> func(pty\_interface, arguments):**
