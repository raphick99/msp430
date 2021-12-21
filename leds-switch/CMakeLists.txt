# find header & source
file(GLOB_RECURSE HEADER "include/*.h")
file(GLOB_RECURSE SOURCE "src/*.c")

set(TARGET_NAME leds-switch)

add_executable(${TARGET_NAME}
  ${SOURCE}
  ${HEADER}
)

source_group("Header include" FILES ${HEADER})
source_group("Source src"     FILES ${SOURCE})

CREATE_FLASH_TARGET(${TARGET_NAME})
