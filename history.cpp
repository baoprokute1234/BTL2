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
            QSqlQuery query5;
            query5.prepare("select * from lend where lend_borrow_id='"+borrow_id+"' and lend_book_id='"+query4.value(0).toString()+"'");
            query5.exec();
            query5.next();
            AddRoot(query4.value(0).toString(),query4.value(1).toString(),query4.value(2).toString(),borrow_date,query5.value(3).toString(),query3.value(1).toString());
        }
    }
    ui->tree->hideColumn(0);
    ui->tree->hideColumn(5);
    ui->update->animateClick();
    ui->tree->header()->resizeSection(1,240);
    ui->tree->header()->resizeSection(3,120);
    Conclose();
    QIcon return_icon(":/new/image/freechartgeany.png");
    ui->return_book->setIcon(return_icon);
    QIcon report_icon(":/new/image/apport.png");
    ui->report_lost->setIcon(report_icon);
    QIcon back_icon(":/new/image/sign-right.png");
    ui->back->setIcon(back_icon);
    QPixmap pix(":/new/image/pink.jpg");
    ui->label->setPixmap(pix);
    this->setWindowTitle("Borrow History");
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

void history::AddRoot(QString id,QString name,QString author,QString time,QString status,QString borrow_id)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->tree);
    item->setText(0,id);
    item->setText(1,name);
    item->setText(2,author);
    item->setText(3,time);
    item->setText(4,status);
    item->setText(5,borrow_id);
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
            QSqlQuery query5;
            query5.prepare("select * from lend where lend_borrow_id='"+borrow_id+"' and lend_book_id='"+query4.value(0).toString()+"'");
            query5.exec();
            query5.next();
            AddRoot(query4.value(0).toString(),query4.value(1).toString(),query4.value(2).toString(),borrow_date,query5.value(3).toString(),query3.value(1).toString());
        }
    }
    Conclose();
}

void history::on_return_book_clicked()
{
    QTreeWidgetItem *item=ui->tree->currentItem();
    QString book_id=item->text(0);
    QString borrow_id=item->text(5);
    Conopen();
    QSqlQuery qery1(db),qry(db);
    qery1.prepare("select book_left from books where book_id='"+book_id+"'");
    qery1.exec();
    qery1.next();
    int left=qery1.value(0).toInt();
    qry.prepare("update books set book_left=:left where book_id='"+book_id+"'");
    qry.bindValue(":left",QString::number(left+1));
    qry.exec();
    QSqlQuery qry1(db);
    qry1.prepare("update lend set lend_stt='Returned' where lend_book_id='"+book_id+"' and lend_borrow_id='"+borrow_id+"'");
    qry1.exec();
    QSqlQuery query(db);
    query.prepare("select * from lend where lend_borrow_id='"+borrow_id+"'");
    query.exec();
    int count=0;
    while(query.next())
    {
        QString status=query.value(3).toString();
        if(status.compare("Returned")!=0) count++;
    }
    if(count==0)
    {
        QSqlQuery query1(db);
        query1.prepare("update borrow set borrow_stt='Returned' where borrow_id='"+borrow_id+"'");
        query1.exec();
    }
    Conclose();
    ui->update->animateClick();
}

void history::on_report_lost_clicked()
{
    QMessageBox message;
    message.setText("Please go see the Librarian for indemnify");
    message.exec();
    QTreeWidgetItem *item = ui->tree->currentItem();
    QString borrow_id=item->text(5);
    QString book_id=item->text(0);
    Conopen();
    QSqlQuery qry(db);
    qry.prepare("update lend set lend_stt='Returned' where lend_borrow_id='"+borrow_id+"' and lend_book_id='"+book_id+"'");
    qry.exec();
    Conclose();
    ui->update->animateClick();
}
