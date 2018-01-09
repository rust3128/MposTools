#include "connectiondialog.h"
#include "ui_connectiondialog.h"
#include "loggingcategories.h"
#include "dbaseconnect.h"
#include <QMessageBox>
#include <QDebug>
#include <QThread>


ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);
    checkConnectButton = new QPushButton(tr("Проверка"));

    createUI();

}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::createUI()
{
    QSqlDatabase dblite = QSqlDatabase::database("lite");

    ui->groupBox->hide();
    modelConnect = new QSqlTableModel(this,dblite);
    modelConnect->setTable("connections");
    modelConnect->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelConnect->select();

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(modelConnect);
    mapper->addMapping(ui->lineEditName,1);
    mapper->addMapping(ui->lineEditServer,2);
    mapper->addMapping(ui->lineEditDataBase,3);
    mapper->addMapping(ui->lineEditLogin,4);
    mapper->addMapping(ui->lineEditPassword,5);

    ui->listView->setModel(modelConnect);
    ui->listView->setModelColumn(1);
    connect(ui->listView->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(connectSelectionChanged(QItemSelection)));
    ui->buttonBox->addButton(checkConnectButton, QDialogButtonBox::AcceptRole);
    connect(checkConnectButton,SIGNAL(clicked()),this,SLOT(checkConnectionButton_clicked()));
//    connect(checkConnectButton,&QAbstractButton::clicked,
//            this, &ConnectionDialog::on_checkConnectionButton_clicked);

}

void ConnectionDialog::on_pushButtonAdd_clicked()
{
    ui->groupBox->show();
    ui->listView->setEnabled(false);
    ui->lineEditDataBase->clear();
    ui->lineEditLogin->clear();
    ui->lineEditName->clear();
    ui->lineEditPassword->clear();
    ui->lineEditServer->clear();
    modelConnect->insertRow(modelConnect->rowCount(QModelIndex()));
    mapper->toLast();
}

void ConnectionDialog::connectSelectionChanged(QItemSelection selection)
{
    mapper->setCurrentModelIndex(selection.indexes().first());
}

void ConnectionDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->standardButton(button)) {
    case QDialogButtonBox::Save:
        mapper->submit();
        modelConnect->submitAll();
        ui->listView->setEnabled(true);
        ui->groupBox->hide();
        break;
    case QDialogButtonBox::Cancel:
        ui->listView->setEnabled(true);
        ui->groupBox->hide();
        break;
    default:
        break;
    }
}

void ConnectionDialog::on_pushButtonEdit_clicked()
{
    ui->groupBox->show();
    ui->listView->setEnabled(false);
}

void ConnectionDialog::on_pushButtonDelete_clicked()
{
    int row =  ui->listView->currentIndex().row();


    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromUtf8("Удаление подключения"),
                          QString::fromUtf8("Вы действительно хотите удалить подключение %1?")
                                  .arg(modelConnect->data(modelConnect->index(row,1)).toString()),
                          QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        modelConnect->removeRow(row);
        modelConnect->submitAll();
        modelConnect->select();
    }

}

void ConnectionDialog::checkConnectionButton_clicked()
{

    tcpSocket->abort();
    tcpSocket->connectToHost(ui->lineEditServer->text().trimmed(),
                             3050);
    if(tcpSocket->waitForConnected(1000)){
      qInfo(logInfo()) << "Проверка доступности. Сервер: " << ui->lineEditServer->text() <<  "FireBird доступен.";
      QString strInfo = QString("<font size='6'><center>Сервер Fierbird по адресу <br><b>%1<br><font color='green'>ДОСТУПЕН!</font></b></center></font>")
              .arg(ui->lineEditServer->text());;
      QMessageBox::information(0, "Проверка подключения", strInfo);
    }  else {
      qInfo(logInfo()) << "Проверка доступности. Сервер: " << ui->lineEditServer->text() <<  "FireBird  НЕ доступен.";
      QString strInfo = QString("<font size='6'><center>Сервер Fierbird по адресу <br><b>%1<br><font color='red'>НЕ ДОСТУПЕН!</font></b></center></font>")
              .arg(ui->lineEditServer->text());
      QMessageBox::information(0, "Проверка подключения", strInfo);
    }

}

void ConnectionDialog::on_pushButtonConnect_clicked()
{
    thread = new QThread;

    isConnected =true;
    progress = new QProgressDialog();
    progress->setWindowModality(Qt::WindowModal);
    progress->setLabelText("Подключение к центральной базе данных...");
    progress->setCancelButton(0);
    progress->setRange(0,0);
    progress->setMinimumDuration(0);

    database.insert("connname",ui->lineEditName->text().trimmed());
    database.insert("server", ui->lineEditServer->text().trimmed());
    database.insert("basename",ui->lineEditDataBase->text().trimmed());
    database.insert("login",ui->lineEditLogin->text().trimmed());
    database.insert("password",ui->lineEditPassword->text().trimmed());

    DBaseConnect *dbConn = new DBaseConnect(database);

    connect(dbConn,SIGNAL(sendStatus(bool)),this,SLOT(getStaus(bool)));
    connect(dbConn,SIGNAL(connectionError(QString)),this,SLOT(errogConnectInfo(QString)));
    connect(dbConn,SIGNAL(fin()),thread,SLOT(terminate()));
    connect(thread,SIGNAL(started()),this,SLOT(startDBConnect()));
    connect(thread,SIGNAL(started()),dbConn,SLOT(createConnection()));
    connect(thread,SIGNAL(finished()),this,SLOT(finishDBConnect()));



    thread->start();
    dbConn->moveToThread(thread);


}

void ConnectionDialog::startDBConnect()
{
    progress->show();
}

void ConnectionDialog::finishDBConnect()
{
    progress->cancel();
    if(isConnected) {
        emit sendConnInfo(database);
        this->accept();
    }
}

void ConnectionDialog::errogConnectInfo(QString str)
{
    QMessageBox::critical(0, qApp->tr("Не могу открыть базу данных"),
                              QString("Не могу установить соединение с центральной БД!\nПричина: %1\n Проверьте настройки подключения.").arg(str),
                              QMessageBox::Ok);
    qDebug() << "Error slot";
}

void ConnectionDialog::getStaus(bool status)
{
    isConnected =status;
}
