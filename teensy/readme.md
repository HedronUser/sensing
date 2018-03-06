# sensing kits

Made for/with the [PNCA Sensing the Environment Project](http://pnca.edu/makethinkcode/news/c/sensing_the_environment).

This is a sound recording and reporting kit. Right now, sound is recorded to an onboard SD card. Stage 0 will send this info over USB Serial to a Python server on a host computer.

## software

For the Teensy:
- [Arduino IDE](https://www.arduino.cc/en/Main/Software) for writing and uploading sketches
- [Teensyduino](https://www.pjrc.com/teensy/teensyduino.html) for Arduino to work with Teensy boards
- [SoX](http://sox.sourceforge.net/) to convert audio. Recommend installing via Homebrew (`brew install sox`)

For the computer:
- Python 2.*
- Virtualenv & virtualenvwrapper
- [pip](https://pip.pypa.io/en/stable/)

## hardware

You will need:
- Teensy 3.2
- Teensy Audio Shield (TODO: part number)
- SparkFun mic (TODO: part number)
- microSD card (ours is 8GB)
- USB --> MicroUSB cable for connecting Teensy to computer
- SD card adaptor so microSD card can be read on computer
- OPTIONAL: ESP8266 WiFi module

## installation

On the host computer, in the project directory, run the following commands to set up your Python environment:

```
mkvirtualenv sensing
pip install -r requirements.txt
```

This should install `pyserial` locally in your `sensing` virtual environment.

run `brew install sox` to get SoX on your computer.

You may need to install additional packages in your Arduino environment in order to interface with a Teensy (TODO: document this).

### virtualenvs

To work in your virtualenv, run the command `workon sensing`. To leave, run `deactivate`.

## project structure

- `/teensy` stores Teensy sketches
- `/base` will store "base station code"; i.e., the server the sensing unit reports data back to and a basic frontend to confirm that communication is working.
- `/rawToWav.sh` uses SoX to convert .RAW audio files, as they are saved to the SD card, into .WAV files. Run it via `source rawToWav.sh path/to/file/without/extension`


## fun facts
- our SD card uses [8.3 filenames](https://en.wikipedia.org/wiki/8.3_filename), so all files saved there can have names of max 8 characters, not including directory names or extension. The extension can be a max of 3 characters.
