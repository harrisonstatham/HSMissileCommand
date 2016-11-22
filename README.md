# HSMissileCommand
Missile Command on the MBED.

## Dependencies

1. GCC-ARM toolchain (https://launchpad.net/gcc-arm-embedded)
2. Make
3. ... 


## Building

1. Read the `Notes` section first.
2. Install the above dependencies.
3. Download the zip file or `git clone` the source to your computer.
4. Run `cd <HSMissileCommand-folder-you-just-downloaded-or-cloned>`
5. Run `chmod u+x BuildScript.bash`
6. Run `./BuildScript.bash`


## Notes
1. I have applied a MIT copyright to all of this. However, if you are a GT student you are bound by the honor code. 
    
    * I will not be responsible if you are caught cheating whilst using my code!! 
    * I provide this repo as a, potential, future reference to other students, NOT as a "hey look, I can copy, and paste this code, and call it mine". 
    * If you're caught cheating, don't drag me into your mess.

2. If you are using another toolchain, the make file is almost worthless. You will need to write a new one or patch the current one.

3. `BuildScript.bash` looks for the gcc-arm toolchain within the `usr/local/Cellar` folder. A relic on my system of the `brew` package manager. You can modify the `bash` script to point to wherever you have your toolchain installed.

4. `BuildScript.bash` tries to write the resultant binary to `/Volumes/MBED` (Mac platform). If this is the incorrect location, you will need to modify this.
