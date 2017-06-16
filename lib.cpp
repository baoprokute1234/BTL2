#include "lib.h"
#include "ui_lib.h"
#include <QMessageBox>
#include <QDialog>
#include <QTreeWidget>
#include <QDate>
//#define MIN(x,y) ((x) < (y) ? (x) : (y))
lib::lib(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lib)
{
    ui->setupUi(this);
    connect(ui->search_edit, SIGNAL(returnPressed()),ui->search_button,SIGNAL(clicked()));
    ui->tree->header()->resizeSection(1,350);
    ui->cart->header()->hide();
    ui->cart->header()->resizeSection(1,45);
    this->setWindowTitle("Main Window");
    Conopen();
    QSqlQuery query1(db),query(db);
    query.prepare("select user_temp from users");
    query.exec();
    query.next();
    QString username=query.value(0).toString();
    query1.prepare("select book_id,book_name,book_author from books COLLATE NOCASE");
    query1.exec();
    while(query1.next())
    {
        QString id = query1.value(0).toString();
        QString name = query1.value(1).toString();
        QString author = query1.value(2).toString();
        AddRoot(id,name,author);
    }
    ui->tree->hideColumn(0);
    QSqlQuery qry(db);
    qry.prepare("select * from users where user_name='"+username+"'");
    qry.exec();
    qry.next();
    qDebug() << qry.value("user_role").toInt();
    if(qry.value("user_role").toInt()==3||qry.value("user_role").toInt()==2) ui->admin->setVisible(false);
    if(qry.value("user_role").toInt()==1||qry.value("user_role").toInt()==3) ui->library->setVisible(false);
    if(qry.value("user_role").toInt()==1||qry.value("user_role").toInt()==2) ui->history->setVisible(false);
    Conclose();
    //connect(ui->info_button,QPushButton::clicked(),this,lib::info_clicked(tmp));

}

lib::~lib()
{
    delete ui;
}

void lib::AddRoot(QString id,QString name,QString author)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->tree);
    item->setText(0,id);
    item->setText(1,name);
    item->setText(2,author);
    ui->tree->addTopLevelItem(item);
}

void lib::AddRootLite(QString id,QString name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->cart);
    item->setText(0,id);
    item->setText(1,name);
    ui->cart->addTopLevelItem(item);
}

void lib::on_search_button_clicked()
{
    Conopen();
    QSqlQuery query1(db);
    query1.prepare("select book_id,book_name,book_author from books COLLATE NOCASE");
    query1.exec();
    QString search;
    search=ui->search_edit->text();
    ui->tree->clear();
    while(query1.next())
    {
        QString id = query1.value(0).toString();
        QString name = query1.value(1).toString();
        QString author = query1.value(2).toString();
        if(name.contains(search)||author.contains(search))
        {
            AddRoot(id,name,author);
        }
    }
    ui->tree->hideColumn(0);
    Conclose();
}

void lib::on_tree_itemClicked(QTreeWidgetItem *item)
{
    QString current = item->text(0);
    Conopen();
    QSqlQuery qry;
    qry.prepare("select * from books where book_id='"+current+"' ");
    qry.exec();
    while(qry.next())
    {
        ui->book_name->setText(qry.value(1).toString());
        ui->book_author->setText(qry.value(2).toString());
        ui->book_prize->setText(qry.value(4).toString());
        ui->book_remain->setText(qry.value(5).toString());
    }
    Conclose();
}

void lib::on_add_button_clicked()
{
    Conopen();
    QTreeWidgetItem *item=ui->tree->currentItem();
    QString current = item->text(0);
    QSqlQuery qry;
    qry.prepare("select * from books where book_id='"+current+"' ");
    qry.exec();
    while(qry.next())
    {
        AddRootLite(qry.value(0).toString(),qry.value(1).toString());
    }
    Conclose();
    ui->cart->hideColumn(0);
}

void lib::on_remove_button_clicked()
{
    QTreeWidgetItem *item=ui->cart->currentItem();
    ui->cart->takeTopLevelItem(ui->cart->indexOfTopLevelItem(item));
}

void lib::on_info_button_clicked()
{
    this->hide();
    info infor;
    infor.setModal(true);
    infor.exec();
}



void lib::on_sign_out_clicked()
{
    this->hide();
    MainWindow *mainwindow = new MainWindow;
    mainwindow->show();
}

void lib::on_admin_clicked()
{
    this->hide();
    admin ad;
    ad.setModal(true);
    ad.exec();
}

void lib::on_library_clicked()
{
    this->hide();
    library libr;
    libr.setModal(true);
    libr.exec();
}

void lib::on_borrow_button_clicked()
{
    Conopen();
    QSqlQuery qry(db),qry1(db),qry2(db);
    qry1.prepare("select user_temp from users");
    qry1.exec();
    qry1.next();
    QString username=qry1.value(0).toString();
    qry2.prepare("select * from users where user_name='"+username+"'");
    qry2.exec();
    qry2.next();
    QString id=qry2.value(0).toString();
    QString time=QDateTime::currentDateTime().toString("hh:mm:ss dd/MM/yyyy");
    qry.prepare("insert into borrow (borrow_user_id, borrow_date, borrow_stt) values ('"+id+"','"+time+"', '0')");
    if(ui->cart->topLevelItemCount()!=0)
    {
        qry.exec();
        QSqlQuery query1(db);
        query1.prepare("select * from borrow");
        query1.exec();
        query1.last();
        QString borrow_id=query1.value(0).toString();
        QMessageBox message;
        message.setText("Borrow Successful");
        message.exec();
        for(int i=0;i<ui->cart->topLevelItemCount();i++)
        {
            QTreeWidgetItem *item=ui->cart->topLevelItem(i);
            QString book_id=item->text(0);
            qDebug() << book_id;
            QSqlQuery query(db);
            query.prepare("insert into lend (lend_borrow_id, lend_book_id) values ('"+borrow_id+"','"+book_id+"')");
            query.exec();
        }
        ui->cart->clear();
        //QString book_id=ui->cart->setCurrentItem()->text(0);

        //qDebug() << book_id;
        /*QSqlQuery query(db);
        query.prepare("insert into lend (lend_borrow_id, lend_book_id) values ('"+book_id+"','"+time+"')");
        query.exec();*/
    }
    Conclose();
}

void lib::on_history_clicked()
{
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
    query2.next();
    QString borrow_id=query2.value(0).toString();
    QString borrow_date=query2.value(2).toString();

    Conclose();
}

void lib::on_contact_clicked()
{
    contact cont;
    cont.setModal(true);
    cont.exec();
}
