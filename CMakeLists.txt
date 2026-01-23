cmake_minimum_required(VERSION 3.5)

project(RGB_Gulag_GUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Update this path if your Qt location is different
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.1/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        filters.cpp
        filters.h
        stb_impl.cpp         # This compiles the image library
        Image_Class.h
        stb_image.h
        stb_image_write.h
)

add_executable(RGB_Gulag_GUI ${PROJECT_SOURCES})

target_link_libraries(RGB_Gulag_GUI PRIVATE Qt6::Widgets)
target_include_directories(RGB_Gulag_GUI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})