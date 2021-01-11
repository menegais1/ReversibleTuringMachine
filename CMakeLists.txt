cmake_minimum_required(VERSION 3.17)
project(ReversibleTuringMachine)

set(CMAKE_CXX_STANDARD 14)

add_executable(ReversibleTuringMachine main.cpp Extensions.h QuadrupleOperation.h ShiftOperation.h ReadWriteOperation.h Tape.h)