cmake_minimum_required(VERSION 3.16)
project(UniversalDialogQtBinding VERSION 0.1.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_library(UniversalDialogQtBinding SHARED UniversalDialogQtBinding.cpp)
target_link_libraries(UniversalDialogQtBinding Qt5::Widgets)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
