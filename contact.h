#ifndef CONTACT_H
#define CONTACT_H

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
#include "lib.h"
namespace Ui {
class contact;
}

class contact : public QDialog
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
    explicit contact(QWidget *parent = 0);
    ~contact();

private slots:
    void on_send_clicked();

private:
    Ui::contact *ui;
};

#endif // CONTACT_H
