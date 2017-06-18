#include "request.h"
#include "ui_request.h"
QString borrow_id;
request::request(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::request)
{
    ui->setupUi(this);
    ui->tree->hideColumn(0);
    ui->list->hideColumn(0);
    ui->tree->header()->resizeSection(1,280);
    Conopen();
    QSqlQuery qry(db),qry1(db);
    qry.prepare("select * from borrow where borrow_stt='Waiting for Confirmation'");
    qry.exec();
    while(qry.next())
    {
        QString user_id=qry.value(1).toString();
        QString borrow_id=qry.value(0).toString();
        qry1.prepare("select * from users where user_id='"+user_id+"'");
        qry1.exec();
        qry1.next();
        QString username=qry1.value(1).toString();
        AddRootLite(borrow_id,username);
    }
    Conclose();
}

request::~request()
{
    delete ui;
}

void request::on_back_clicked()
{
    this->hide();
    lib libr;
    libr.setModal(true);
    libr.exec();
}

void request::AddRoot(QString id,QString name,QString author)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->tree);
    item->setText(0,id);
    item->setText(1,name);
    item->setText(2,author);
    ui->tree->addTopLevelItem(item);
}

void request::AddRootLite(QString borrow_id,QString request_from)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->list);
    item->setText(0,borrow_id);
    item->setText(1,request_from);
    ui->tree->addTopLevelItem(item);
}

void request::on_list_itemClicked(QTreeWidgetItem *item)
{
    ui->tree->clear();
    Conopen();
    borrow_id=item->text(0);
    QSqlQuery qry1(db),qry(db);
    qry1.prepare("select * from lend where lend_borrow_id='"+borrow_id+"'");
    qry1.exec();
    while(qry1.next())
    {
        QString book_id=qry1.value(2).toString();
        qry.prepare("select * from books where book_id='"+book_id+"'");
        qry.exec();
        qry.next();
        QString book_name=qry.value(1).toString();
        QString book_author=qry.value(2).toString();
        AddRoot(book_id,book_name,book_author);
    }
    Conclose();
}

void request::on_accept_clicked()
{
    Conopen();
    QSqlQuery qry(db);
    qry.prepare("update borrow set borrow_stt='Not Returned' where borrow_id='"+borrow_id+"'");
    qry.exec();
    Conclose();
    QMessageBox message;
    message.setText("Accepted");
    message.exec();
    ReloadView();
}

void request::ReloadView()
{
    ui->list->clear();
    ui->tree->clear();
    Conopen();
    QSqlQuery qry(db),qry1(db);
    qry.prepare("select * from borrow where borrow_stt='Waiting for Confirmation'");
    qry.exec();
    while(qry.next())
    {
        QString user_id=qry.value(1).toString();
        QString borrow_id=qry.value(0).toString();
        qry1.prepare("select * from users where user_id='"+user_id+"'");
        qry1.exec();
        qry1.next();
        QString username=qry1.value(1).toString();
        AddRootLite(borrow_id,username);
    }
    Conclose();
}

void request::on_deny_clicked()
{
    Conopen();
    QSqlQuery qry(db),qery1;
    for(int i=0;i<ui->tree->topLevelItemCount();i++)
    {
        QTreeWidgetItem *item=ui->tree->topLevelItem(i);
        QString book_id=item->text(0);
        qery1.prepare("select book_left from books where book_id='"+book_id+"'");
        qery1.exec();
        qery1.next();
        int left=qery1.value(0).toInt();
        qry.prepare("update books set book_left=:left where book_id='"+book_id+"'");
        qry.bindValue(":left",QString::number(left+1));
        qry.exec();
    }
    QSqlQuery qry1(db);
    qry1.prepare("update borrow set borrow_stt='Denied' where borrow_id='"+borrow_id+"'");
    qry1.exec();
    Conclose();
    QMessageBox message;
    message.setText("Denied");
    message.exec();
    ReloadView();
}
