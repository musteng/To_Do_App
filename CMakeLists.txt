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
        mainWindowItems/MainWindow.cpp mainWindowItems/MainWindow.h mainWindowItems/MainWindow.ui
        dialogWindow/InputDialogWindow.cpp dialogWindow/InputDialogWindow.h dialogWindow/InputDialogWindow.ui
        mainWindowItems/TaskList.cpp mainWindowItems/TaskList.h mainWindowItems/TaskList.ui
        mainWindowItems/ListItem.cpp mainWindowItems/ListItem.h
        dialogWindow/DialogWindow.cpp dialogWindow/DialogWindow.h dialogWindow/DialogWindow.ui
        fileControl/FileController.cpp fileControl/FileController.h)

add_executable(To_Do_App ${PROJECT_SOURCES})

target_link_libraries(To_Do_App
        Qt::Core
        Qt::Gui
        Qt::Widgets)

