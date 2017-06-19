#include "library.h"
#include "ui_library.h"

library::library(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::library)
{
    ui->setupUi(this);
    connect(ui->search_edit, SIGNAL(returnPressed()),ui->search_button,SIGNAL(clicked()));
    ui->tree->header()->resizeSection(1,350);
    this->setWindowTitle("Main Window");
    Conopen();
    QSqlQuery query1(db);
    query1.prepare("select book_id,book_name,book_author from books");
    query1.exec();
    while(query1.next())
    {
        QString id = query1.value(0).toString();
        QString name = query1.value(1).toString();
        QString author = query1.value(2).toString();
        AddRoot(id,name,author);
    }
    Conclose();
    QIcon change_icon(":/new/image/pencil.png");
    ui->change_detail->setIcon(change_icon);
    QIcon update_icon(":/new/image/accessories-media-converter.png");
    ui->update->setIcon(update_icon);
    QIcon remove_icon(":/new/image/sign-delete.png");
    ui->remove->setIcon(remove_icon);
    QIcon add_icon(":/new/image/sign-add.png");
    ui->add->setIcon(add_icon);
    QIcon back_icon(":/new/image/sign-right.png");
    ui->back->setIcon(back_icon);
    QIcon search_icon(":/new/image/search.png");
    ui->search_button->setIcon(search_icon);
    QPixmap pix(":/new/image/pink.jpg");
    ui->label_9->setPixmap(pix);
}

library::~library()
{
    delete ui;
}

void library::AddRoot(QString id,QString name,QString author)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->tree);
    item->setText(0,id);
    item->setText(1,name);
    item->setText(2,author);
    ui->tree->addTopLevelItem(item);
}


void library::on_tree_itemClicked(QTreeWidgetItem *item)
{
    QString current = item->text(0);
    Conopen();
    QSqlQuery qry;
    qry.prepare("select * from books where book_id='"+current+"' ");
    qry.exec();
    while(qry.next())
    {
        ui->id->setText(qry.value(0).toString());
        ui->name->setText(qry.value(1).toString());
        ui->author->setText(qry.value(2).toString());
        ui->stock->setText(qry.value(3).toString());
        ui->prize->setText(qry.value(4).toString());
        ui->left->setText(qry.value(5).toString());
        QDate date=QDate::fromString(qry.value(6).toString(),"dd/MM/yyyy");
        ui->date_in->setDate(date);
    }
    Conclose();
}

void library::on_change_detail_clicked()
{
    ui->name->setReadOnly(false);
    ui->author->setReadOnly(false);
    ui->stock->setReadOnly(false);
    ui->left->setReadOnly(false);
    ui->prize->setReadOnly(false);
    ui->date_in->setReadOnly(false);
}

void library::on_update_clicked()
{
    Conopen();
    QString id=ui->id->text();
    QString name=ui->name->text();
    QString author=ui->author->text();
    QString stock=ui->left->text();
    QString left=ui->left->text();
    QString prize=ui->prize->text();
    QString date_in=ui->date_in->date().toString("dd/MM/yyyy");
    QSqlQuery qry(db);
    qry.prepare("update books set book_name='"+name+"',book_author='"+author+"',book_prize='"+prize+"',book_stock='"+stock+"',book_left='"+left+"',book_date_in='"+date_in+"' where book_id='"+id+"'");
    qry.exec();
    ui->tree->clear();
    QSqlQuery query1(db);
    query1.prepare("select book_id,book_name,book_author from books");
    query1.exec();
    while(query1.next())
    {
        QString id = query1.value(0).toString();
        QString name = query1.value(1).toString();
        QString author = query1.value(2).toString();
        AddRoot(id,name,author);
    }
    Conclose();
    QMessageBox message;
    message.setText("Updated");
    message.exec();
}

void library::on_back_clicked()
{
    this->hide();
    lib libr;
    libr.setModal(true);
    libr.exec();
}

void library::on_remove_clicked()
{
    Conopen();
    QString id=ui->id->text();
    QSqlQuery qry(db);
    qry.prepare("delete from books where book_id='"+id+"'");
    if(!qry.exec()) qDebug() << "hello world";
    QTreeWidgetItem *item=ui->tree->currentItem();
    ui->tree->takeTopLevelItem(ui->tree->indexOfTopLevelItem(item));
    Conclose();
}

void library::on_add_clicked()
{
    this->hide();
    add_book add;
    add.setModal(true);
    add.exec();
}

void library::on_search_button_clicked()
{
    Conopen();
    QSqlQuery query1(db);
    query1.prepare("select book_id,book_name,book_author from books");
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
    Conclose();
}
