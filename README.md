# msp430
### Build target using:
```bash
TARGET=blink-leds  # bash variable holding target name
rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=msp430.cmake
cmake --build . --target ${TARGET} flash-${TARGET} -- -j 4  # Where blink-leds is the name of the target and flash-blink-leds writes output to flash
cd ..
```
