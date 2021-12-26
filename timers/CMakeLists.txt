# find header & source
file(GLOB_RECURSE HEADER "include/*.h")
file(GLOB_RECURSE SOURCE "src/*.c")

set(TARGET_NAME timers)

include_directories(
	include/
)

add_executable(${TARGET_NAME}
  ${SOURCE}
)

CREATE_FLASH_TARGET(${TARGET_NAME})
