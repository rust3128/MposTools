#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QSqlRecord>
#include <QLabel>

struct userdata
{
    int id;
    QString fio;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QSqlRecord user, QWidget *parent = 0);
    ~MainWindow();
    void show();

private slots:
    void on_actionConnect_triggered();
    void getConnInfo(QMap<QString, QString> connInfo);

private:
    Ui::MainWindow *ui;
    bool normalClose;
    userdata currentUser;
    QLabel *labelUser;
    QLabel *labelConnInfo;
    QMap<QString, QString> centalDatabase;
private:
    void closeEvent(QCloseEvent *event);
    void infoUser2StatusBar();
    void infoConnect2StatusBar();

};

#endif // MAINWINDOW_H
