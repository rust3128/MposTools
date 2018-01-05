#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    createUI();

}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::createUI()
{
    QSqlDatabase dblite = QSqlDatabase::database("lite");

    ui->frame->hide();
    modelConnect = new QSqlTableModel(this,dblite);
    modelConnect->setTable("connections");
    modelConnect->select();

    ui->listView->setModel(modelConnect);
    ui->listView->setModelColumn(1);

}
