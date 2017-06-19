#ifndef ADD_BOOK_H
#define ADD_BOOK_H

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
#include "library.h"
namespace Ui {
class add_book;
}

class add_book : public QDialog
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
        db.setDatabaseName("library.db");
        if(db.open()) { qDebug()<<("Connected"); return true;}
        else return false;
    }
    explicit add_book(QWidget *parent = 0);
    ~add_book();

private slots:
    void on_add_clicked();

    void on_back_clicked();

private:
    Ui::add_book *ui;
};

#endif // ADD_BOOK_H
