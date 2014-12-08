#------------------------------------------------------------------------------
# Tell cmake where to find the project cmake scripts
#------------------------------------------------------------------------------
PROJECT(char_classifier)
cmake_minimum_required(VERSION 2.8)

#-- Where to look first for cmake modules
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

#-- Type of build
SET(CMAKE_BUILD_TYPE Release)

FIND_PACKAGE(OpenCV REQUIRED)
MESSAGE(STATUS "OPENCV_LIBRARIES=${OpenCV_LIBS}")
MESSAGE(STATUS "OPENCV_INCLUDE_DIRS=${OpenCV_INCLUDE_DIRS}")

FIND_PACKAGE(Boost REQUIRED COMPONENTS system filesystem REQUIRED)
MESSAGE(STATUS "BOOST_LIBRARIES=${Boost_LIBRARIES}")
MESSAGE(STATUS "BOOST_INCLUDE_DIRS=${Boost_INCLUDE_DIR}")

#-- Find include files
INCLUDE_DIRECTORIES(
    ${OpenCV_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

#-- Add .h and .cpp files to the project
ADD_EXECUTABLE(test_char_classifier
    ${CMAKE_SOURCE_DIR}/include/trace.hpp
    ${CMAKE_SOURCE_DIR}/include/Constants.hpp
    ${CMAKE_SOURCE_DIR}/src/Constants.cpp
    ${CMAKE_SOURCE_DIR}/include/utils.hpp
    ${CMAKE_SOURCE_DIR}/src/utils.cpp
    ${CMAKE_SOURCE_DIR}/include/RTClassifier.hpp
    ${CMAKE_SOURCE_DIR}/src/RTClassifier.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

#-- Link the executable to the libraries
TARGET_LINK_LIBRARIES(test_char_classifier
    ${OpenCV_LIBS}   
    jpeg
    tiff
    png
    ${Boost_LIBRARIES}
)
