#ifndef DATABASES_H
#define DATABASES_H

#define DATABASE_NAME "./MPosTools.opt"
#define DATABASE_HOSTNAME   "OptionsHost"

#include <QtSql>
#include <QSqlQuery>
#include <loggingcategories.h>

static bool createTable()
{
    QSqlDatabase dblite = QSqlDatabase::database("lite");
    QSqlQuery query = QSqlQuery(dblite);
    QString strSQL = "CREATE TABLE users "
                     "(user_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "user_name VARCHAR(50) NOT NULL, "
                     "user_fio VARCHAR(50) NOT NULL, "
                     "user_pass VARCHAR(50) NOT NULL)";

     if(!query.exec(strSQL)){
         qCritical(logCritical()) << "DataBase: Ошибка создания таблицы пользователя." << query.lastError().text();
         return false;
     } else {
         strSQL = "INSERT INTO `users`(`user_name`,`user_fio`,`user_pass`) "
                  "VALUES ('Admin','Администратор А.А.','defrag')";
         if(!query.exec(strSQL)) {
             qCritical(logCritical()) << "DataBase: Ошибка добавления записи пользователя." << query.lastError().text();
             return false;
         }

         strSQL = "CREATE TABLE `connections` ( "
                 "`conn_id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
                 "`conn_name`	VARCHAR(50) NOT NULL UNIQUE, "
                 "`conn_host`	varchar(50) NOT NULL, "
                 "`conn_db`	VARCHAR(100) NOT NULL, "
                 "`conn_user`	INTEGER NOT NULL, "
                 "`conn_pass`	INTEGER NOT NULL)";
         if(!query.exec(strSQL)) {
             qCritical(logCritical()) << "DataBase: Ошибка создания таблицы подключений." << query.lastError().text();
             return false;
         }
         qInfo(logInfo()) << "Файл настроек приложения успешно создан.";
         return true;
     }

     return false;

}

static bool openDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","lite");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

static bool createDataBase()
{
    if(openDatabase()){
        if(!createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

static bool connectionOptions()
{
    //База данных опций приложения
    if(!QFile(DATABASE_NAME).exists()){
        qInfo(logInfo) << "Отсутсвует файл настроек приложения";
        createDataBase();
    } else {
        openDatabase();
    }
    return true;
}




#endif // DATABASES_H
