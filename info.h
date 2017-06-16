#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include <QTreeWidget>
#include <QDialog>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlError>
#include <QDir>
#include <QFile>
#include <QSqlQuery>
#include <QDebug>
#include <lib.h>

namespace Ui {
class info;
}

class info : public QDialog
{
    Q_OBJECT

public:

    QSqlDatabase db;
    void Conclose()
    {
        db.close();
        db.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool Conopen()
    {
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("C:/Users/Admin/Source Code/BTL2/library.db");
        if(db.open()) { qDebug()<<("Connected"); return true;}
        else return false;
    }

    explicit info(QWidget *parent = 0);
    ~info();

private slots:
    void on_change_info_clicked();

    void on_update_clicked();

    void on_update_password_clicked();

    void on_back_button_clicked();
private:
    Ui::info *ui;
};

#endif // INFO_H
