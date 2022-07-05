cmake_minimum_required(VERSION 3.20)
project(To_Do_App)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "/Users/mustafacevik/Qt/6.2.2/macos/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp MainWindow.h MainWindow.ui
        InputDialogWindow.cpp InputDialogWindow.h InputDialogWindow.ui
        TaskList.cpp TaskList.h TaskList.ui
        ListItem.cpp ListItem.h
        DialogWindow.cpp DialogWindow.h DialogWindow.ui FileController.cpp FileController.h)

add_executable(To_Do_App ${PROJECT_SOURCES})

target_link_libraries(To_Do_App
        Qt::Core
        Qt::Gui
        Qt::Widgets)

