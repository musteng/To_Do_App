## To Do List Application

Application created by using Cmake, C++ and Qt 6.

Application is a standalone executable. And it saves your to-do lists by saving their name, due date and priority of a to-do.

Application can be used by database or if no internet connection is available, application is able to save your to-so list on local computer.

## To create firebase database follow the steps below;
 1. Go to address https://firebase.google.com
 2. Click "Get Started"
 3. Click "Add Project"
 4. Give a name to your project and continue
 5. Create project
 6. After project creation click "Build" on the left panel
 7. Click "Realtime Database"
 8. Create a database
 9. After creation database, copy reference url
 10.Paste the database URL to "dbUrl" variable which is in the file DatabaseHandlerFiles/DatabaseHandler.cpp, line 11.
 11. Once The URL is copied, the application can be used.

## Offline Mode
To use offline mode, more automated way will be released but for now one should uncomment all file write and read related commented code and comment the database related codes.
###
#### For more information mail to xcevik00@gmail.com