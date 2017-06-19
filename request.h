#ifndef REQUEST_H
#define REQUEST_H

#include <QDialog>
#include "lib.h"
namespace Ui {
class request;
}

class request : public QDialog
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
    void AddRoot(QString id,QString name,QString author);
    void AddRootLite(QString borrow_id,QString request_from);
    void ReloadView();
    explicit request(QWidget *parent = 0);
    ~request();

private slots:
    void on_back_clicked();

    void on_list_itemClicked(QTreeWidgetItem *item);

    void on_accept_clicked();

    void on_deny_clicked();

private:
    Ui::request *ui;
};

#endif // REQUEST_H
