#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loggingcategories.h"
#include "logindialog.h"
#include "connectiondialog.h"

#include <QMessageBox>

MainWindow::MainWindow(QSqlRecord user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    normalClose = true;
    this->resize(1600,900);
    currentUser.id=user.value("user_id").toInt();
    currentUser.fio=user.value("user_fio").toString();

    infoUser2StatusBar();
}

void MainWindow::show()
{
    QMainWindow::show();
//    Call your special function here.
    ConnectionDialog *connDlg = new ConnectionDialog();
    connect(connDlg,SIGNAL(sendConnInfo(QMap<QString,QString>)),this,SLOT(getConnInfo(QMap<QString,QString>)));

    connDlg->move(this->geometry().center().x() - connDlg->geometry().center().x(), this->geometry().center().y() - connDlg->geometry().center().y());
    connDlg->exec();

    infoConnect2StatusBar();
}

void MainWindow::getConnInfo(QMap<QString, QString> connInfo)
{
    centalDatabase = connInfo;
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
            qInfo(logInfo()) << "Завершение работы программы.";
            event->accept();
        }
    } else {
        qInfo(logInfo()) << "Не выполнена аутентификация. Завершение работы программы.";
        event->accept();
        }

}

void MainWindow::infoUser2StatusBar()
{
    labelUser = new QLabel(this);
    labelUser->setText("Пользователь: "+currentUser.fio);
    ui->statusBar->addPermanentWidget(labelUser);
}

void MainWindow::infoConnect2StatusBar()
{
    labelConnInfo = new QLabel(this);
    labelConnInfo->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    labelConnInfo->setStyleSheet("QLabel { color : green; }");
    labelConnInfo->setText("Подключено: " + centalDatabase.value("connname")+ " "
                           + centalDatabase.value("server")+":"+centalDatabase.value("basename"));
    ui->statusBar->addWidget(labelConnInfo);
}

void MainWindow::on_actionConnect_triggered()
{
//    ConnectionDialog *connDlg = new ConnectionDialog();

//    connDlg->move(this->geometry().center().x() - connDlg->geometry().center().x(), this->geometry().center().y() - connDlg->geometry().center().y());
//    connDlg->exec();
}
