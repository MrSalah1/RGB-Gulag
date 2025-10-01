cmake_minimum_required(VERSION 3.30)
project(A1_Ramly)

set(CMAKE_CXX_STANDARD 23)

# Specify the directory where the compiler should look for header files.
# The `.` means the current directory, which is where your header files are.
include_directories(.)

# Link the executable with the source file.
# Since the image library is header-only, you don't need to link it as a separate library.
add_executable(A1_Ramly
        main.cpp
        samurai.jpg
        #[[ImageProcessingDemo.cpp]]
        Sample-imgs

)
