#ifndef DBASECONNECT_H
#define DBASECONNECT_H

#include <QObject>
#include <QMap>

class DBaseConnect : public QObject
{
    Q_OBJECT
public:
    explicit DBaseConnect(QMap<QString,QString> opt, QObject *parent = nullptr);

signals:
    void connectionError(QString errorMeaage);
    void fin();
    void sendStatus(bool);

public slots:
    void createConnection();

private:
    QMap<QString, QString> config;


};

#endif // DBASECONNECT_H
