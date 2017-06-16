#ifndef MESS_H
#define MESS_H

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
class mess;
}

class mess : public QDialog
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
    void AddRoot(QString username, QString time, QString title, QString status);
    explicit mess(QWidget *parent = 0);
    ~mess();

private slots:
    void on_back_clicked();

private:
    Ui::mess *ui;
};

#endif // MESS_H
