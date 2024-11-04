cmake_minimum_required(VERSION 3.29)
project(PHILO C)

set(CMAKE_C_STANDARD 11)

include_directories(philo)

add_executable(PHILO
    philo/actions.c
    philo/philo.c
    philo/philo.h
    philo/test.c
    philo/utils.c)
