cmake_minimum_required(VERSION 3.16)

project(PlannerGUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp

    ui/MainWindow.cpp
    ui/MainWindow.h
    ui/MainWindow.ui

    ui/LoginWindow.cpp
    ui/LoginWindow.h


    ui/RegisterWindow.cpp
    ui/RegisterWindow.h
    ui/RegisterWindow.ui





    ui/AddTaskDialog.cpp
    ui/AddTaskDialog.h
    ui/AddTaskDialog.ui

    core/Task.cpp
    core/Task.h

    core/Planner.cpp
    core/Planner.h

    core/UserManager.cpp
    core/UserManager.h



)

qt_add_executable(PlannerGUI
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ui/LoginWindow.ui
    resources.qrc
)
target_include_directories(PlannerGUI PRIVATE
    ${CMAKE_SOURCE_DIR}
)
target_link_libraries(PlannerGUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Copy resources (themes, data)
file(COPY themes DESTINATION ${CMAKE_BINARY_DIR})


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PlannerGUI)
endif()

