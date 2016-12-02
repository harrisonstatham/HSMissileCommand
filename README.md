# HSMissileCommand
Missile Command on the MBED. This repo assumes either a Mac or Linux platform. Modify the build script, and makefile appropriately.

## Dependencies

1. GCC-ARM toolchain (https://launchpad.net/gcc-arm-embedded)
2. Make


## Building

1. Read the `Notes` section first.
2. Install the above dependencies.
3. Download the zip file or `git clone` the source to your computer.
4. Run `cd <HSMissileCommand-folder-you-just-downloaded-or-cloned>`
5. Run `chmod u+x BuildScript.bash`
6. Run `./BuildScript.bash`


## Notes
1. I have applied a MIT copyright to all of this. However, if you are a GT student you are bound by the honor code. 
    
    * I will not be responsible if you are caught cheating while using my code!! 
    * I provide this repo as a, potential, future reference to other students, NOT as a "hey look, I can copy, and paste this code, and call it mine". 
    * If you're caught cheating, don't drag me into your mess.

2. If you are using another toolchain, the make file is almost worthless. You will need to write a new one or patch the current one. You can "cheat", and let the MBED compiler write the makefile for you. Go to the MBED online compiler, go to the export menu, choose your compiler that you want to export for, and make sure to check "Include all files". You should find a makefile within the downloaded directory. You might have to modify it a little to point to the correct locations on your system.

3. `BuildScript.bash` looks for the gcc-arm toolchain within the `usr/local/gcc-arm` folder. This just happens to be where I installed the compiler when I first downloaded it. If you add the binary to a non-standard path, then you will need to modify your `PATH` to search for the binary within that directory. `EXPORT PATH="<my new path here>:{$PATH}"` should do the trick.

4. `BuildScript.bash` tries to write the resultant binary to `/Volumes/MBED` (Mac platform). If this is the incorrect location, you will need to modify this.
