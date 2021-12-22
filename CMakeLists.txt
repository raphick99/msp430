cmake_minimum_required(VERSION 3.16)

project(msp430)

add_compile_options(
	-mmcu=msp430g2553
	-Wall
	-Werror
	-Wextra
	-Wshadow
	-Wpedantic
)

add_link_options(
	-mmcu=msp430g2553
	-L/opt/msp430-gcc/include
)

macro(CREATE_FLASH_TARGET TARGET_NAME)
	add_custom_target(flash-${TARGET_NAME}
		COMMAND ${PROGBIN} rf2500 "prog ${TARGET_NAME}"
		DEPENDS ${TARGET_NAME}
	)
endmacro()

add_subdirectory(blink-leds)
add_subdirectory(leds-switch)

