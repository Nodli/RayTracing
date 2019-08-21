cmake_minimum_required(VERSION 3.5)
project(RayTracer)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_DEBUG "-g")
set(CMAKE_CXX_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)


include_directories("source")
file(GLOB RAY_TRACER_SOURCES "source/*.cpp")

# Application : Ray Tracer
add_executable(RayTracer.exe ${RAY_TRACER_SOURCES})
