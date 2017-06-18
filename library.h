#ifndef LIBRARY_H
#define LIBRARY_H
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
#include "lib.h"
#include <QDialog>
#include "add_book.h"
namespace Ui {
class library;
}

class library : public QDialog
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

    explicit library(QWidget *parent = 0);
    ~library();
    void Khoitao();
    void AddRoot(QString id,QString name,QString author);
private slots:
    void on_tree_itemClicked(QTreeWidgetItem *item);

    void on_change_detail_clicked();

    void on_update_clicked();

    void on_back_clicked();

    void on_remove_clicked();

    void on_add_clicked();

    void on_search_button_clicked();

private:
    Ui::library *ui;
};

#endif // LIBRARY_H
