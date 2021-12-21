# msp430
### Execute using:
```bash
rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=msp430.cmake
cmake --build . --target blink-leds flash-blink-leds -- -j 4  # Where blink-leds is the name of the target and flash-blink-leds writes output to flash
cd ..
```
