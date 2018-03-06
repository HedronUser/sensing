#!/bin/bash 

#1/29/2018

#runs on Raspberry Pi 3B, other platforms may require myMacAddress to use wlan0
#since not every Pi has wired ethernet

#realistic values for arecord duration and max-file-time
#1hour per file (max-file-time 3600 seconds)
#12hours total  (duration 43200 seconds/12hours)
#Start recording 7:00PM  stop at 7:00PM based on earliest sunset and latest sunrise 
#from 4/1/2018 - 5/12/2018

#unique is mac address - colons in filenames confuse the OS so replace : with .
myMacAddress=$(cat /sys/class/net/eth0/address | sed 's/:/./g')

#date
myDate=$(date +%Y-%m-%d-%H-%M)

recordName="$myMacAddress.$myDate"

#recording is no longer triggered by login so we need to choose a better location.
#it will likely be removable media located in /media/pi/somewhere
cd ~/Desktop/myBirds

arecord -f S16_LE -t wav --r=22000 -Dplug:default  --max-file-time 30 --duration=90 $recordName.wav 
