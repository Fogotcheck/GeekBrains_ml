cmake_minimum_required(VERSION 3.26.4)
project(myLibs VERSION 0.1.0 LANGUAGES CXX)

file(GLOB_RECURSE Head "./hdr/*.h")
file(GLOB_RECURSE Src "./src/*.cpp")
message("Hdr::${Head}\nSrc::${Src}")

add_library(myLibs ${Head} ${Src})