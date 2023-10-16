cmake_minimum_required(VERSION 3.24)
project(BullCow)

set(CMAKE_CXX_STANDARD 20)

file(GLOB cmd
        "src/*"
        )

add_executable(BullCow ${cmd})