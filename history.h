#ifndef HISTORY_H
#define HISTORY_H

#include <QDialog>
#include "lib.h"
namespace Ui {
class history;
}

class history : public QDialog
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
    void AddRoot(QString id, QString name, QString author, QString time, QString status, QString borrow_id);
    explicit history(QWidget *parent = 0);
    ~history();

private slots:
    void on_back_clicked();

    void on_update_clicked();

    void on_return_book_clicked();

    void on_report_lost_clicked();

private:
    Ui::history *ui;
};

#endif // HISTORY_H
