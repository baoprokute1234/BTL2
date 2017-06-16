#ifndef DETAIL_H
#define DETAIL_H

#include <QDialog>
namespace Ui {
class detail;
}

class detail : public QDialog
{
    Q_OBJECT

public:
    /*QSqlDatabase db;
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
    }*/
    explicit detail(QWidget *parent = 0);
    ~detail();

private:
    Ui::detail *ui;
};

#endif // DETAIL_H
