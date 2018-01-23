# sensing kits

Made for/with the [PNCA Sensing the Environment Project](http://pnca.edu/makethinkcode/news/c/sensing_the_environment).

This is a sound recording and reporting kit. Right now, sound is recorded to an onboard SD card. 
Stage 1 will send this info over Wifi to a Python server on a host computer.

## objectives
- record bird songs at night for as long as possible (1-2weeks)
- transmit bird songs to cloud server after recording is finished (during the day)
- connect to cloud server to download recorded data
- make a recording device that is cheap and easy to setup and maintain

## software

For the Rpi:
- Image of RPi_sensing (TODO: make and post image of pi with everything configured proper) 

For the computer:
- Python 2.*
- Virtualenv & virtualenvwrapper
- [pip](https://pip.pypa.io/en/stable/)

## hardware

You will need:
- Raspberry Pi 3
- [Sabrent USB Audio Adapter](https://www.google.com/shopping/product/2306321428961959764?lsf=seller:6136318,store:15060907829491788201&prds=oid:7203634167783694949&q=usb+audio+adapter+sabrent+robotshop&hl=en&ei=m95mWrKnLcXQjwPul4DoAg&lsft=gclid:Cj0KCQiAtJbTBRDkARIsAIA0a5MivhP0sNqjmVP4I1P3m8pjSyolc1Mo8ve7HlB34PsM0rWNyHSgObgaAirHEALw_wcB)
- [Electret microphone](https://www.adafruit.com/product/1064) (TODO: part number)
- Wireless dongle w/ removable 5dB antennae (optional) (enhancement) (larger range) (TODO: link)
- microSD card (ours is 8GB)
- USB --> MicroUSB cable for connecting RPi to power
- 120VAC-->USB 5V 1.5A wall adapter
- SD card adaptor so microSD card can be flashed with computer
- OPTIONAL: HDMI cable, HDMI monitor, USB keyboard and mouse for setting up Pi

## installation

On the raspberry pi, follow the setup on [raspberry pi audio setup](http://www.g7smy.co.uk/2013/08/recording-sound-on-the-raspberry-pi/) 

then test recording with:

arecord -f S16_LE --r=22000 -D plughw:1 --duration=10 -vv ~/rectest11.wav





On the host computer, in the project directory, run the following commands to set up your Python environment:

```
mkvirtualenv sensing
pip install -r requirements.txt
```

This should install `pyserial` locally in your `sensing` virtual environment.

run `brew install sox` to get SoX on your computer.


### virtualenvs

To work in your virtualenv, run the command `workon sensing`. To leave, run `deactivate`.

## project structure

- `/teensy` stores Teensy sketches for microcontroller based sensing module (legacy)
- `/RPi` will store "base station code"; i.e., the client with the microphone sensing unit that reports data back to server and a basic frontend to confirm that communication is working.
- `/docs` a place to store all documentation for this project 
- `/enclosure` a place to store all things enclosure related - design files, 

## development
Slack
- Hackathon: Sensing the Environment
- Workspace URL: sensingtheenvironment.slack.com 

## building from source
- download latest version of NOOBs or Debian Jessie/Wheezy 
- update software 
- configure keyboard, locale, and timezone as US.
- clone this repo 
- run python script as a bash script on startup
- follow [raspberry pi audio setup](http://www.g7smy.co.uk/2013/08/recording-sound-on-the-raspberry-pi/) to make sure you can record with your setup



## references
- [microphone jack schematic](https://electronics.stackexchange.com/questions/307430/confusion-about-trrs-jack-and-mic-input)
- [microphone jack pic](https://cdn.instructables.com/ORIG/FHZ/YTV8/GAPUWXXX/FHZYTV8GAPUWXXX.jpg)
- [raspberry pi audio setup](http://www.g7smy.co.uk/2013/08/recording-sound-on-the-raspberry-pi/)

## credits
Nandini
Violet Pena
Trace Harris
Richard
Dylan Mcnamee
Chris Eykamp
Candace Hazelwood
Jesse Jenkins