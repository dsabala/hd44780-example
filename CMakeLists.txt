cmake_minimum_required(VERSION 3.16.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(hd44780-example C ASM) 

set(CPU_OPTIONS
    -mthumb 
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

add_compile_options(
    $<$<CONFIG:Debug>:-Og>
    $<$<CONFIG:Debug>:-gdwarf-2>
    -Wall
    -Wextra
    -fdata-sections
    -ffunction-sections
    ${CPU_OPTIONS}
)

add_compile_definitions(
    STM32F407xx
    USE_HAL_DRIVER
    HSE_VALUE=8000000U
)

add_subdirectory(hd44780)
add_subdirectory(stm32f4-drivers)

add_executable(hd44780-example.elf)

target_include_directories(hd44780-example.elf PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

target_sources(hd44780-example.elf
    PRIVATE
        src/bsp_lcd.c
        src/main.c
)

target_link_libraries(hd44780-example.elf
    PUBLIC
        stm32f4-drivers
        hd44780
)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32F407VGTx_FLASH.ld)

target_link_options(hd44780-example.elf PRIVATE -T${LINKER_SCRIPT} -specs=nosys.specs -lnosys -lc -lm -Wl,-Map=${PROJECT_NAME}.map,--gc-sections,--cref,--print-memory-usage ${CPU_OPTIONS})

add_custom_command(
    TARGET hd44780-example.elf
    POST_BUILD
        COMMAND echo ***** Memory sections *****
        COMMAND ${CMAKE_SIZE_UTIL} hd44780-example.elf --radix=10
        COMMAND ${CMAKE_OBJCOPY} -Osrec hd44780-example.elf hd44780-example.srec
        COMMAND ${CMAKE_OBJCOPY} -Oihex hd44780-example.elf hd44780-example.hex
)
