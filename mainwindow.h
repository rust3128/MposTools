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

private:
    Ui::MainWindow *ui;
    bool normalClose;
    userdata currentUser;
    QLabel *labelUser;
private:
    void closeEvent(QCloseEvent *event);
    void infoUser2StatusBar();

};

#endif // MAINWINDOW_H
