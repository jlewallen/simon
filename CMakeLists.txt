project(ARDUINO_PROJECTS)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_VERBOSE_MAKEFILE on)

message("${CMAKE_CURRENT_SOURCE_DIR}/../conservify/arduino-cmake-minimal/cmake/")

set(ARDUINO_IDE "${CMAKE_CURRENT_SOURCE_DIR}/../../conservify/arduino-1.8.3")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../conservify/arduino-cmake-minimal/cmake/")

include(ArduinoMinimal)

set(SOURCE_FILES
  Buttons.cpp
  DemoMode.cpp
  Game.cpp
  Speaker.cpp
  simon.ino
)

set(LIBRARIES
)

include_directories(./)

arduino(simon "${SOURCE_FILES}" "${LIBRARIES}")
