#include "add_book.h"
#include "ui_add_book.h"

add_book::add_book(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_book)
{
    ui->setupUi(this);
}

add_book::~add_book()
{
    delete ui;
}

void add_book::on_add_clicked()
{
    Conopen();
    QSqlQuery qry(db);
    QString name=ui->name->text();
    QString author=ui->author->text();
    QString stock=ui->stock->text();
    QString prize=ui->prize->text();
    QString date_in=ui->date_in->text();
    qry.prepare("insert into users (book_name, book_author, book_stock, book_left,book_prize,book_date_in) values ('"+name+"','"+author+"', '"+stock+"', '"+stock+"', '"+prize+"', '"+date_in+"')");
    qry.exec();
    Conclose();
}

void add_book::on_back_clicked()
{
    this->hide();
    library libr;
    libr.setModal(true);
    libr.exec();
}
