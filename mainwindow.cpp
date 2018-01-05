#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loggingcategories.h"
#include "logindialog.h"
#include "connectiondialog.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    normalClose = true;
    this->resize(1600,900);


}

void MainWindow::show()
{
    QMainWindow::show();
    // Call your special function here.
        LoginDialog *loginDlg = new LoginDialog();
        loginDlg->move(this->geometry().center().x() - loginDlg->geometry().center().x(), this->geometry().center().y() - loginDlg->geometry().center().y());
        loginDlg->exec();

//move(parent->geometry().center().x() - rect().center().x(), parent->geometry().center().y() - rect().center().y());

        if(loginDlg->result()==QDialog::Rejected){
            normalClose=false;
            this->close();
        }
        user = loginDlg->getUser();
        infoUser2StatusBar();
        ConnectionDialog *connDlg = new ConnectionDialog();
        connDlg->exec();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if(normalClose) {
        if (QMessageBox::Yes == QMessageBox::question(this, "Закрыть?",
                              "Уверены?",
                              QMessageBox::Yes|QMessageBox::No))
        {
            event->accept();
            qInfo(logInfo()) << "Завершение работы программы.";
        }
    } else {
            event->accept();
            qInfo(logInfo()) << "Не выполнена аутентификация. Завершение работы программы.";
        }

}

void MainWindow::infoUser2StatusBar()
{
    labelUser = new QLabel(this);
    labelUser->setText("Пользователь: "+user.value("user_fio").toString());
    ui->statusBar->addPermanentWidget(labelUser);
}
