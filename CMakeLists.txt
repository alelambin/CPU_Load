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

set(SOURCES sources/main.cpp
    sources/mainwidget.cpp
    sources/selectwidget.cpp
    sources/openglwidget.cpp
    sources/workercpu.cpp
    sources/workercore.cpp
    sources/thread.cpp
    sources/mutex.cpp
)
set(HEADERS
    headers/mainwidget.h
    headers/selectwidget.h
    headers/openglwidget.h
    headers/worker.h
    headers/workercpu.h
    headers/workercore.h
    headers/circularlist.h
    headers/thread.h
    headers/mutex.h
)
set(RESOURCES resources.qrc)

add_executable(CPU_Load ${SOURCES} ${HEADERS} ${RESOURCES})
target_link_libraries(CPU_Load
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

