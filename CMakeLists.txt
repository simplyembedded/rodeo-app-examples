cmake_minimum_required(VERSION 3.15)

# Specify before project().
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/opt/se-rodeo-iot-sdk/lib/rodeo-iot/cmake/")
find_package(RodeoIot REQUIRED)

project(rodeo-iot VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

string(REPLACE " " ";" common_cflags "${COMMON_CFLAGS}")
add_compile_options(
    ${common_cflags}
    -DORG_NAME="${ORG_NAME}"
)

add_subdirectory("env_sensor_demo")
add_subdirectory("ir_sensor_demo")
add_subdirectory("audio_input_demo")

