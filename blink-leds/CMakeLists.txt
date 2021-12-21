# find header & source
file(GLOB_RECURSE HEADER "include/*.h")
file(GLOB_RECURSE SOURCE "src/*.c")

set(TARGET_NAME blink-leds)

add_executable(${TARGET_NAME}
  ${SOURCE}
  ${HEADER}
)

source_group("Header include" FILES ${HEADER})
source_group("Source src"     FILES ${SOURCE})

add_custom_target(flash
	COMMAND ${PROGBIN} rf2500 "prog ${TARGET_NAME}"
	DEPENDS ${TARGET_NAME}
)

