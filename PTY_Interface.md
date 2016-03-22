> ## PTY\_Interface Class ##
> by Aidan Macdonald (aidan.plenert.macdonald@gmail.com)

> This class generates a pty device that emulates the
> tty device created by GPIB controllers such as
> Prologix GPIB-USB Controller (prologix.biz)

> This class does NOT emulate the controller, but the
> controller must be attached to this PTY Interface

> I may switch between the terms tty device and pty device.
> They refer to the same thing.

**Initialization - Interface(default\_device, default\_address)
> accepts arguments default\_device and default\_address
> the default\_device will be connected at the default\_address**

> If the Interface address (PTY\_Interface.addr) is changed, the
> no longer have anything attached and will become functionless.
> UNLESS, the default device handles the address change and copies itself
> to the new address (Prologix\_GPIB\_USB does this, OR there is
> another device attached there.

> if no arguments are given at initialization, defaults are
> Device.Prologix\_GPIB-USB at address 0

**printFilename()
> Prints the path to the PTY device generated (ie /dev/pts/2)**

**run(readLen)
> Runs the emulator which will read all statements written from the outside
> to the pty device at the location given by self.printFilename(), then
> runs what was read through self.handleInput(tty\_in) and writes output
> back to the pty device to be read from the outside**

**handleInput(tty\_in)
> Recieves raw input that was read from the pty device, and
> breaks it up and send it to the device listed at the current
> address. That device must handle the command via dev.handleCMD(cmd, args)**

