cmake_minimum_required(VERSION 3.7)
project(Something)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(
    main
    
    include/window.hpp
    include/entity.hpp
    include/text.hpp
    
    src/window.cpp
    src/entity.cpp
    src/main.cpp
    src/text.cpp
)

target_link_libraries(main ${SDL2_LIBRARIES} SDL2_image SDL2_ttf)