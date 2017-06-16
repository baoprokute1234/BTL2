#ifndef LIB_H
#define LIB_H
#include <QTreeWidget>
#include <QDialog>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlError>
#include <QDir>
#include <QFile>
#include <QSqlQuery>
#include <QDebug>
#include "info.h"
#include "mainwindow.h"
#include "admin.h"
#include "library.h"
#include "mess.h"
#include "contact.h"
namespace Ui {
class lib;
}

class lib : public QDialog
{
    Q_OBJECT
void AddRoot(QString id,QString name, QString author);
void AddRootLite(QString id,QString name);
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

    explicit lib(QWidget *parent = 0);
    ~lib();

private slots:
    void on_search_button_clicked();

    void on_tree_itemClicked(QTreeWidgetItem *item);

    void on_add_button_clicked();

    void on_remove_button_clicked();

    void on_info_button_clicked();

    void on_sign_out_clicked();

    void on_admin_clicked();

    void on_library_clicked();

    void on_borrow_button_clicked();

    void on_history_clicked();

    void on_contact_clicked();

private:
    Ui::lib *ui;
};

#endif // LIB_H
