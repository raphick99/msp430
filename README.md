## msp430-training
### Based off of [this blog](http://www.simplyembedded.org/tutorials/) and [this repository](https://github.com/simplyembedded/msp430_launchpad)
#### Build target using:
```bash
TARGET=blink-leds  # bash variable holding target name
rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=cmake/msp430.cmake
cmake --build . --target ${TARGET} flash-${TARGET} -- -j 4  # Where blink-leds is the name of the target and flash-blink-leds writes output to flash
cd ..
```
