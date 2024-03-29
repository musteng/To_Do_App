cmake_minimum_required(VERSION 3.20)
project(To_Do_App)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "$ENV{HOME}/Qt")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        Network)


set(PROJECT_SOURCES
        main.cpp
        ApplicationWindow/MainWindow.cpp ApplicationWindow/MainWindow.h ApplicationWindow/MainWindow.ui
        ApplicationWindow/TaskList.cpp ApplicationWindow/TaskList.h ApplicationWindow/TaskList.ui
        ApplicationWindow/ListItem.cpp ApplicationWindow/ListItem.h
        AddUpdateWindow/DialogWindow.cpp AddUpdateWindow/DialogWindow.h AddUpdateWindow/DialogWindow.ui
        FileControl/FileController.cpp FileControl/FileController.h
        DatabaseHandlerFiles/DatabaseHandler.cpp DatabaseHandlerFiles/DatabaseHandler.h
        DatabaseHandlerFiles/DatabaseItem.cpp DatabaseHandlerFiles/DatabaseItem.h)

add_executable(To_Do_App ${PROJECT_SOURCES})

target_link_libraries(To_Do_App
        Qt::Gui
        Qt::Widgets
        Qt::Network)

include_directories("${PROJECT_SOURCE_DIR}/inc/")