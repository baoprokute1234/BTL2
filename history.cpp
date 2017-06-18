#include "history.h"
#include "ui_history.h"

history::history(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);
    ui->update->setVisible(false);
    Conopen();
    QSqlQuery query(db);
    query.prepare("select user_temp from users");
    query.exec();
    query.next();
    QString username=query.value(0).toString();
    QSqlQuery query1(db);
    query1.prepare("select * from users where user_name='"+username+"'");
    query1.exec();
    query1.next();
    QString user_id=query1.value(0).toString();
    QSqlQuery query2(db);
    query2.prepare("select * from borrow where borrow_user_id='"+user_id+"'");
    query2.exec();
    while(query2.next())
    {
        QString borrow_id=query2.value(0).toString();
        QString borrow_date=query2.value(2).toString();
        QString status=query2.value(3).toString();
        if(status!="Returned")
        {
            QDateTime now=QDateTime::currentDateTime();
            QString borrow=query2.value(2).toString();
            QDateTime borrow_time=QDateTime::fromString(borrow,"hh:mm:ss dd/MM/yyyy");
            qint64 time=borrow_time.daysTo(now);
            if(time>=14)
            {
                QSqlQuery query5(db);
                query5.prepare("update borrow set borrow_stt='Overdue' where borrow_id='"+borrow_id+"'");
                query5.exec();
            }
        }
        QSqlQuery query3(db);
        query3.prepare("select * from lend where lend_borrow_id='"+borrow_id+"'");
        query3.exec();
        while(query3.next())
        {
            QSqlQuery query4;
            query4.prepare("select * from books where book_id='"+query3.value(2).toString()+"'");
            query4.exec();
            query4.next();
            AddRoot(query4.value(0).toString(),query4.value(1).toString(),query4.value(2).toString(),borrow_date,query2.value(3).toString());
        }
    }
    ui->tree->hideColumn(0);
    ui->update->animateClick();
    Conclose();
}

history::~history()
{
    delete ui;
}

void history::on_back_clicked()
{
    this->hide();
    lib libr;
    libr.setModal(true);
    libr.exec();
}

void history::AddRoot(QString id,QString name,QString author,QString time,QString status)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->tree);
    item->setText(0,id);
    item->setText(1,name);
    item->setText(2,author);
    item->setText(3,time);
    item->setText(4,status);
    ui->tree->addTopLevelItem(item);
}

void history::on_update_clicked()
{
    Conopen();
    ui->tree->clear();
    QSqlQuery query(db);
    query.prepare("select user_temp from users");
    query.exec();
    query.next();
    QString username=query.value(0).toString();
    QSqlQuery query1(db);
    query1.prepare("select * from users where user_name='"+username+"'");
    query1.exec();
    query1.next();
    QString user_id=query1.value(0).toString();
    QSqlQuery query2(db);
    query2.prepare("select * from borrow where borrow_user_id='"+user_id+"'");
    query2.exec();
    while(query2.next())
    {
        QString borrow_id=query2.value(0).toString();
        QString borrow_date=query2.value(2).toString();
        QSqlQuery query3(db);
        query3.prepare("select * from lend where lend_borrow_id='"+borrow_id+"'");
        query3.exec();
        while(query3.next())
        {
            QSqlQuery query4;
            query4.prepare("select * from books where book_id='"+query3.value(2).toString()+"'");
            query4.exec();
            query4.next();
            AddRoot(query4.value(0).toString(),query4.value(1).toString(),query4.value(2).toString(),borrow_date,query2.value(3).toString());
        }
    }
    Conclose();
}
