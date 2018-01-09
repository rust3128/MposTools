#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QItemSelection>
#include <QAbstractButton>
#include <QTcpSocket>
#include <QProgressDialog>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();

signals:
    void sendConnInfo(QMap<QString, QString>);
private slots:
    void on_pushButtonAdd_clicked();
    void connectSelectionChanged(QItemSelection selection);
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_pushButtonEdit_clicked();
    void on_pushButtonDelete_clicked();
    void checkConnectionButton_clicked();
    void on_pushButtonConnect_clicked();
    void startDBConnect();
    void finishDBConnect();
    void errogConnectInfo(QString str);
    void getStaus(bool status);

private:
    Ui::ConnectionDialog *ui;
    QSqlTableModel *modelConnect;
    QDataWidgetMapper *mapper;
    QPushButton *checkConnectButton;
    QTcpSocket *tcpSocket;
    QMap<QString, QString> database;
    QProgressDialog *progress;
    bool isConnected;
    QThread *thread;
private:
    void createUI();
};

#endif // CONNECTIONDIALOG_H
