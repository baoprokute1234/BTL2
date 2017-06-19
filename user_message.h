#ifndef USER_MESSAGE_H
#define USER_MESSAGE_H

#include <QDialog>
#include <lib.h>
namespace Ui {
class user_message;
}

class user_message : public QDialog
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
    void AddRoot(QString id,QString title,QString time,QString from,QString status);
    void ReloadView();
    explicit user_message(QWidget *parent = 0);
    ~user_message();

private slots:
    void on_mess_preview_itemClicked(QTreeWidgetItem *item);

    void on_back_clicked();

    void on_reply_clicked();

private:
    Ui::user_message *ui;
};

#endif // USER_MESSAGE_H
