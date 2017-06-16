#ifndef ADD_USER_H
#define ADD_USER_H

#include <QDialog>
#include "admin.h"
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
namespace Ui {
class add_user;
}

class add_user : public QDialog
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

    explicit add_user(QWidget *parent = 0);
    ~add_user();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add_user *ui;
};

#endif // ADD_USER_H
