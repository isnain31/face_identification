PROJECT(facedetect)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

########### cmake configuration and compiler flags ###########
SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_C_FLAGS_DEBUG "-fPIC -Wall -g")
SET(CMAKE_CXX_FLAGS_DEBUG "-fPIC -Wall -g")
SET(CMAKE_C_FLAGS_RELEASE "-fPIC -Wall")
SET(CMAKE_CXX_FLAGS_RELEASE "-fPIC -Wall")
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib) #static libraries
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) #executables
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib) #dynamic libraries (plugins)
find_package(OpenCV) 
########### Simple Open EtherCAT Master Library ###########

INCLUDE_DIRECTORIES(
 ${PROJECT_SOURCE_DIR}
)

#TARGET_LINK_LIBRARIES(soem)

ADD_EXECUTABLE(facedetect
 ${PROJECT_SOURCE_DIR}/facedetect.cpp
)

target_link_libraries(facedetect ${OpenCV_LIBS})
