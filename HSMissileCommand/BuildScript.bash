#!/bin/bash

# Clean up everything first.
make clean

# Call Make

make

outputResult = $?


# Upload the new binary to the MBED.

cp -f .build/MissileCommand.bin /Volumes/MBED/MissileCommand.bin

# Clear the screen of all the junk.
clear

# List all of the files in the directory of the MBED to make sure it worked.

ls -a /Volumes/MBED/

