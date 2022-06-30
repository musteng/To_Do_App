#include "MainWindow.h"
#include "QApplication"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    /**
     * QWidget: Must construct a QApplication before a QWidget
     * Before creating a main window object, QApplication must be created and initialized.
     */
    MainWindow mainWindow = new MainWindow();
    mainWindow.show();

    return a.exec();
}
