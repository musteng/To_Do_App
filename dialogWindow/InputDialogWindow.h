//
// Created by Mustafa Çevik on 27.06.2022.
//

#ifndef TO_DO_APP_INPUTDIALOGWINDOW_H
#define TO_DO_APP_INPUTDIALOGWINDOW_H

#include <QInputDialog>



QT_BEGIN_NAMESPACE
namespace Ui { class InputDialogWindow; }
QT_END_NAMESPACE

class InputDialogWindow : public QInputDialog {
Q_OBJECT

public:
    explicit InputDialogWindow(QWidget *parent = nullptr);

    ~InputDialogWindow() override;

private:
    Ui::InputDialogWindow *ui;
     ;
};


#endif //TO_DO_APP_INPUTDIALOGWINDOW_H
