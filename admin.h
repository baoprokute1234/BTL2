#ifndef ADMIN_H
#define ADMIN_H

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
#include <QListWidget>
#include <lib.h>
#include "add_user.h"
namespace Ui {
class admin;
}

class admin : public QDialog
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

    explicit admin(QWidget *parent = 0);
    ~admin();

private slots:
    void on_back_clicked();

    void on_list_clicked();

    void on_see_password_pressed();

    void on_see_password_released();

    void on_change_info_clicked();

    void on_reset_clicked();

    void on_update_clicked();

    void on_pushButton_clicked();

    void on_delete_2_clicked();

    void on_message_clicked();

private:
    Ui::admin *ui;
};

#endif // ADMIN_H
