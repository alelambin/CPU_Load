cmake_minimum_required(VERSION 3.24)
project(CPU_Load)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED
)

set(CODE sources/main.cpp
    headers/mainwidget.h sources/mainwidget.cpp
    headers/selectwidget.h sources/selectwidget.cpp
    headers/openglwidget.h sources/openglwidget.cpp
    headers/worker.h
    headers/workercpu.h sources/workercpu.cpp
    sources/workercore.cpp headers/workercore.h
    headers/circularlist.h
    sources/thread.cpp headers/thread.h
    sources/mutex.cpp headers/mutex.h
)
set(RESOURCES resources.qrc)

add_executable(CPU_Load ${CODE} ${RESOURCES})
target_link_libraries(CPU_Load
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

