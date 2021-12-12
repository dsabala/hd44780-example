add_library(stm32f4-drivers STATIC EXCLUDE_FROM_ALL)

target_include_directories(stm32f4-drivers PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_compile_options(stm32f4-drivers PRIVATE "-Wno-unused-parameter")

target_sources(stm32f4-drivers
    PRIVATE
        source/startup_stm32f407xx.s
        source/stm32f4xx_hal.c
        source/stm32f4xx_hal_cortex.c
        source/stm32f4xx_hal_flash.c
        source/stm32f4xx_hal_gpio.c
        source/stm32f4xx_hal_pwr.c
        source/stm32f4xx_hal_pwr_ex.c
        source/stm32f4xx_hal_rcc.c
        source/stm32f4xx_hal_rcc_ex.c
        source/system_stm32f4xx.c
)
