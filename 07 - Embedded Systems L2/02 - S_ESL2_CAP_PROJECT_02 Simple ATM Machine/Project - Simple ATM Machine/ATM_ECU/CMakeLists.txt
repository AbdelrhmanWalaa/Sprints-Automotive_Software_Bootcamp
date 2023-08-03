cmake_minimum_required(VERSION 3.25)
#project(ATM_ECU C)

set(CMAKE_C_STANDARD 11)

include_directories(ATM_ECU/)
include_directories(ATM_ECU/APP)
include_directories(ATM_ECU/HAL/lcd)
include_directories(ATM_ECU/HAL/temp_sensor)
include_directories(ATM_ECU/HAL/mbtn)
include_directories(ATM_ECU/LIB)
include_directories(ATM_ECU/MCAL/dio)
include_directories(ATM_ECU/MCAL/timer)
include_directories(ATM_ECU/MCAL/spi)

add_executable(
        ATM_ECU
        ATM_ECU/APP/app_interface.h
        ATM_ECU/APP/app_program.c
        ATM_ECU/HAL/lcd/lcd_config.h
        ATM_ECU/HAL/lcd/lcd_interface.h
        ATM_ECU/HAL/lcd/lcd_private.h
        ATM_ECU/HAL/lcd/lcd_program.c
        ATM_ECU/MCAL/spi/spi_config.h
        ATM_ECU/MCAL/spi/spi_interface.h
        ATM_ECU/MCAL/spi/spi_program.c
        ATM_ECU/LIB/bit_math.h
        ATM_ECU/LIB/std.h
        ATM_ECU/MCAL/dio/dio_config.h
        ATM_ECU/MCAL/dio/dio_interface.h
        ATM_ECU/MCAL/dio/dio_private.h
        ATM_ECU/MCAL/dio/dio_program.c
        ATM_ECU/MCAL/timer/timer_config.h
        ATM_ECU/MCAL/timer/timer_interface.h
        ATM_ECU/MCAL/timer/timer_private.h
        ATM_ECU/MCAL/timer/timer_program.c
        ATM_ECU/main.c
        ATM_ECU/HAL/kpd/kpd_program.c
        ATM_ECU/HAL/buzzer/buzzer.c
        ATM_ECU/MCAL/exi/exi_program.c
        ATM_ECU/HAL/mbtn/mbtn_program.c)
