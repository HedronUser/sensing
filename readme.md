# sensing kits

Made for/with the [PNCA Sensing the Environment Project](http://pnca.edu/makethinkcode/news/c/sensing_the_environment).

This is a sound recording and reporting kit. Right now, sound is recorded to an onboard SD card. 
Stage 1 will send this info over Wifi to a Python server on a host computer.

## software

For the Rpi:
- NOOBs or Debian Jessie/Wheezy TODO: link to image of everything configured
- [SoX](http://sox.sourceforge.net/) to convert audio. Recommend installing via Homebrew (`brew install sox`)
- 

For the computer:
- Python 2.*
- Virtualenv & virtualenvwrapper
- [pip](https://pip.pypa.io/en/stable/)

## hardware

You will need:
- Raspberry Pi 3
- [USB Audio Adapter](TODO:add link)
- [Electret microphone](https://www.adafruit.com/product/1064) (TODO: part number)
- microSD card (ours is 8GB)
- USB --> MicroUSB cable for connecting RPi to power
- 120VAC-->USB 5V 1.5A wall adapter
- SD card adaptor so microSD card can be flashed with computer
- OPTIONAL: HDMI cable, HDMI monitor, USB keyboard and mouse for setting up Pi

## installation

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


## references
- [microphone jack schematic](https://electronics.stackexchange.com/questions/307430/confusion-about-trrs-jack-and-mic-input)
- [microphone jack pic](https://cdn.instructables.com/ORIG/FHZ/YTV8/GAPUWXXX/FHZYTV8GAPUWXXX.jpg)
- [raspberry pi audio setup](http://www.g7smy.co.uk/2013/08/recording-sound-on-the-raspberry-pi/)
