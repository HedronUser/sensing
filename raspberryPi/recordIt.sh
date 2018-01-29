#!/bin/bash 

#1/28/2018
#just for testing

myDate=$(date +%Y-%m-%d-%H-%M)

cd ~/Desktop/myBirds

arecord -f S16_LE -t wav --r=22000 -Dplug:default  --max-file-time 30 --duration=90 $myDate.wav 

