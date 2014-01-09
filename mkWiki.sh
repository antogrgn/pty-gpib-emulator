#!/bin/bash

NAME=`echo $1 | awk -F'.' '{ print $1 }'`

cat $1 | grep "##" | sed s/"##"//g | sed s/"\*\*"/"="/g | sed s/"<<<<"/"="/g | sed s/">>>>"/"="/g | sed s/"%%"/"*"/g > $2
