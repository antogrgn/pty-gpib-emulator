##
## **** Device Class ****
## by Aidan Macdonald (aidan.plenert.macdonald@gmail.com)
##
## Standard framework for the a Device that is attached
## to the PTY_Interface
##


class Device:
##
##%% No initialization
##

##%% handleCMD(pty_interface, command, arguments)
## A device attached to a PTY_Interface will handle commands
## passed to it from the PTY_Interface by a call made to
## this function.
##
## pty_interface will be a referance to the interface that called
## this function
##
## command will be a string with the text of the command read
## from the pty device
##
## arguments is an array of the arguments to said command read
## from the pty device
##
## The string returned by this function will be written to
## the pty device
##
    def handleCMD(self, fpl, cmd, args=[]):
        return ""
