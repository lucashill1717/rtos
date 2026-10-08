cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME USART-exploration)

set(LINKER_SCRIPT
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32F401RETX_FLASH.ld
)

set(PROJECT_SOURCES
    Startup/startup_stm32f401retx.s

    Sources/main.c
    Sources/syscalls.c
    Sources/sysmem.c

	Sources/Drivers/Src/USART.c
)

set(PROJECT_DEFINES
    STM32F401xE
)

project(${PROJECT_NAME} C ASM)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Drivers/Include
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    ${PROJECT_DEFINES}
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -mthumb
    -std=gnu11
    -Wall
    -Werror
    --specs=nano.specs
)

target_link_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -mthumb

    -T${LINKER_SCRIPT}
    --specs=nosys.specs
    -Wl,-Map=${PROJECT_NAME}.map
    -Wl,--gc-sections
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX ".elf"
)