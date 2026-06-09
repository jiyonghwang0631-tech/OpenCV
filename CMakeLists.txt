cmake_minimum_required(VERSION 3.10)
project(kuBig2026)

set(CMAKE_CXX_STANDARD 17)
include(ExternalProject)

option(KUBIG_BUILD_ATMEGA128 "Build the Atmega128 external project" ON)
option(KUBIG_BUILD_PICO "Build the Pico external project" ON)

add_subdirectory(c_example/part3)
add_subdirectory(c_example/part4/carSerial)
add_subdirectory(c_example/part4/myRandom)
add_subdirectory(c_example/part4/baseballGame)
add_subdirectory(c_example/part5/date)
add_subdirectory(c_example/part5/twoDouble)
add_executable(fileDescriptor c_example/part6/fileDescriptor.c)
add_subdirectory(c_example/part6/scoreProcess)
add_subdirectory(c_example/part6/iotLogReport)
add_subdirectory(ds/stack/myStack1)
add_subdirectory(ds/stack/myStack2)
add_subdirectory(ds/stack/myStack3)
add_subdirectory(ds/stack/myStack4)
add_subdirectory(ds/queue/myQueue1)
add_subdirectory(ds/queue/myQueue2)
add_subdirectory(ds/queue/myQueue3)
add_subdirectory(network)
add_subdirectory(bowling)
add_subdirectory(opencv_ex)
add_subdirectory(opencv_ex/part2)

if(KUBIG_BUILD_ATMEGA128)
	find_program(AVR_GCC_EXECUTABLE avr-gcc)
	find_program(AVR_OBJCOPY_EXECUTABLE avr-objcopy)

	if(AVR_GCC_EXECUTABLE AND AVR_OBJCOPY_EXECUTABLE)
		ExternalProject_Add(atmega128_project
			SOURCE_DIR ${CMAKE_SOURCE_DIR}/atmega128
			BINARY_DIR ${CMAKE_BINARY_DIR}/atmega128-build
			CMAKE_ARGS
				-DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/atmega128/avr-toolchain.cmake
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
			INSTALL_COMMAND ""
		)
	else()
		message(WARNING "Skipping atmega128_project because the AVR toolchain is not installed. Set KUBIG_BUILD_ATMEGA128=OFF to silence this warning.")
	endif()
endif()

if(KUBIG_BUILD_PICO)
	find_program(ARM_NONE_EABI_GCC_EXECUTABLE arm-none-eabi-gcc)

	if(ARM_NONE_EABI_GCC_EXECUTABLE)
		ExternalProject_Add(pico_project
			SOURCE_DIR ${CMAKE_SOURCE_DIR}/pico
			BINARY_DIR ${CMAKE_BINARY_DIR}/pico-build
			CMAKE_ARGS
				-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
				-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
				-DPICO_SDK_PATH=${CMAKE_SOURCE_DIR}/pico/deps/pico-sdk
			INSTALL_COMMAND ""
		)
	else()
		message(WARNING "Skipping pico_project because arm-none-eabi-gcc is not installed. Set KUBIG_BUILD_PICO=OFF to silence this warning.")
	endif()
endif()