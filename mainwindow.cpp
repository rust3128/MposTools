#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loggingcategories.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Закрыть?",
                          "Уверены?",
                          QMessageBox::Yes|QMessageBox::No))
    {
    event->accept();
    qInfo(logInfo()) << "Завершение работы программы.";
    }
}
