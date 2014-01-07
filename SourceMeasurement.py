##
## <<<< Source Measurement Unit Emulators >>>>
## by Aidan Macdonald (aidan.plenert.macdonald@gmail.com)
##
## Contains classes that emulate Source Measurement Units
##

import Device, Prologix

## **** Source Measurement Class ****
## by Aidan Macdonald (aidan.plenert.macdonald@gmail.com)
##
## General model of a basic Source Measurement Unit
##

class SourceMeasurement(Prologix.Prologix_GPIB_USB):
    
##%% Initialization SourceMeasurement()
## Creates the framework
##

    def __init__(self):
        Prologix.Prologix_GPIB_USB.__init__(self)



