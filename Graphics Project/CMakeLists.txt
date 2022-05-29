cmake_minimum_required(VERSION 3.20)
project(Graphics_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(. "C:\\MinGW\\include")

add_executable(Graphics_Project
        framework.h
        "Graphics Project.cpp"
        "Graphics Project.h"
        Line.cpp
        Line.h
        LineData.cpp
        LineData.h
        LineDrawer.h
        LineDrawerDDA.cpp
        LineDrawerDDA.h
        menu_items.h
        Resource.h
        Shape.cpp
        Shape.h
        ShapeData.cpp
        ShapeData.h
        ShapeDrawer.cpp
        ShapeDrawer.h
        targetver.h LineDrawerMidpoint.cpp LineDrawerMidpoint.h LineDrawerParametric.cpp LineDrawerParametric.h CardinalSplineDrawer.cpp CardinalSplineDrawer.h CardinalSplineData.cpp CardinalSplineData.h CardinalSpline.cpp CardinalSpline.h)

target_link_libraries(Graphics_Project -lOpenGL32  -lglu32)

