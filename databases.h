#ifndef DATABASES_H
#define DATABASES_H

#define DATABASE_NAME "./MPosTools.opt"

#include <QtSql>

static bool openDatabase()
{

}

static bool createDataBase()
{

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
