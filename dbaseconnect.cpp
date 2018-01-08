#include "dbaseconnect.h"
#include <QtSql>
#include <QDebug>

DBaseConnect::DBaseConnect(QMap<QString,QString> opt, QObject *parent) : QObject(parent)
{
    config = opt;
}

void DBaseConnect::createConnection()
{

//    QMapIterator<QString, QString> i(config);
//     while (i.hasNext()) {
//         i.next();
//         qDebug() << i.key() << ": " << i.value() << endl;
//     }
    //    qDebug() << azsRec.value("SERVER_NAME").toString();
    ///Подключаемся к базе данных АЗС
//    QString pass;

    QSqlDatabase db = QSqlDatabase::addDatabase("QIBASE","central");
    db.setHostName(config.value("server"));
    db.setDatabaseName(config.value("basename"));
    db.setUserName(config.value("login"));

//    if(config.value("password") == "ncvxjxrm‚")
//            pass="masterkey";
//    if(config.value("password") == "twqsnrhlv")
//            pass="sunoiladm";
    db.setPassword(config.value("password"));
    if(!db.open()) {
        emit sendStatus(false);
        QString errorString =  db.lastError().text();
        qDebug() <<  "Не возможно подключиться к базе данных." << endl << "Причина:" << errorString;

        emit connectionError(errorString);
        emit fin();

    }
    emit sendStatus(true);
    emit fin();
}
