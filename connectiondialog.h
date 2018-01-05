#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();

private:
    Ui::ConnectionDialog *ui;
    QSqlTableModel *modelConnect;
private:
    void createUI();
};

#endif // CONNECTIONDIALOG_H
