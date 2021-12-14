cmake_minimum_required(VERSION 3.0.0)
project(OpenCV_cascades VERSION 0.1.0)

find_package(OpenCV REQUIRED)
                        
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(OpenCV_cascades main.cpp)
target_link_libraries(OpenCV_cascades ${OpenCV_LIBS})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/haarcascade_frontalcatface_extended.xml
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/haarcascade_fullbody.xml
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/hamilton.mp4
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/pedestrians.mp4
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
