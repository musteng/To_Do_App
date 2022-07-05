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
        WindowMain/MainWindow.cpp WindowMain/MainWindow.h WindowMain/MainWindow.ui
        WindowDialog/InputDialogWindow.cpp WindowDialog/InputDialogWindow.h WindowDialog/InputDialogWindow.ui
        WindowMain/TaskList.cpp WindowMain/TaskList.h WindowMain/TaskList.ui
        WindowMain/ListItem.cpp WindowMain/ListItem.h
        WindowDialog/DialogWindow.cpp WindowDialog/DialogWindow.h WindowDialog/DialogWindow.ui
        FileControl/FileController.cpp FileControl/FileController.h)

add_executable(To_Do_App ${PROJECT_SOURCES})

target_link_libraries(To_Do_App
        Qt::Core
        Qt::Gui
        Qt::Widgets)

