#ifndef LIB_MESSAGE_H
#define LIB_MESSAGE_H

#include <QDialog>
#include "lib.h"
namespace Ui {
class lib_message;
}

class lib_message : public QDialog
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
        db.setDatabaseName("E:/library.db");
        if(db.open()) { qDebug()<<("Connected"); return true;}
        else return false;
    }

    explicit lib_message(QWidget *parent = 0);
    ~lib_message();
    void AddRoot(QString id,QString username,QString time,QString title,QString status);
    void ReloadView();
private slots:
    void on_back_clicked();

    void on_mess_preview_itemClicked(QTreeWidgetItem *item);

    void on_reply_clicked();

private:
    Ui::lib_message *ui;
};

#endif // LIB_MESSAGE_H
