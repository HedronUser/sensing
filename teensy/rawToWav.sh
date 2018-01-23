#!/usr/bin/env bash

sox -b 16 -c 1 -r 44100 -e signed-integer $1.raw $1.wav
