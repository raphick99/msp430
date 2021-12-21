cmake_minimum_required(VERSION 3.16)

project(msp430)

# find packages
add_compile_options(-mmcu=msp430g2553)
add_link_options(-mmcu=msp430g2553 -L/opt/msp430-gcc/include)

macro(CREATE_FLASH_TARGET TARGET_NAME)
	add_custom_target(flash-${TARGET_NAME}
		COMMAND ${PROGBIN} rf2500 "prog ${TARGET_NAME}"
		DEPENDS ${TARGET_NAME}
	)
endmacro()

add_subdirectory(blink-leds)
add_subdirectory(leds-switch)

# MESSAGE("link directories: ${LINK_DIRECTORIES}")
# MESSAGE("compile options: ${COMPILE_OPTIONS}")
# 
# get_target_property(MAIN_CFLAGS msp430 COMPILE_OPTIONS)
# get_target_property(MAIN_LDIRS msp430 LINK_DIRECTORIES)
# # also see: COMPILE_DEFINITIONS INCLUDE_DIRECTORIES
# message("-- Target compiler flags are: ${MAIN_CFLAGS}")
# message("-- Target link directories are: ${MAIN_LDIRS}")

