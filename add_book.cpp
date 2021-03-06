#include "add_book.h"
#include "ui_add_book.h"

add_book::add_book(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_book)
{
    ui->setupUi(this);
    QIcon add_icon(":/new/image/sign-add.png");
    ui->add->setIcon(add_icon);
    QIcon back_icon(":/new/image/sign-right.png");
    ui->back->setIcon(back_icon);
    QPixmap pix(":/new/image/pink.jpg");
    ui->label_6->setPixmap(pix);
    this->setWindowTitle("Add Book");
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
    QString des=ui->description->toPlainText();
    qry.prepare("insert into books (book_name, book_author, book_stock, book_left,book_prize,book_date_in,book_description) values ('"+name+"','"+author+"', '"+stock+"', '"+stock+"', '"+prize+"', '"+date_in+"', '"+des+"')");
    qry.exec();
    Conclose();
    QMessageBox message;
    message.setText("New book added");
    message.exec();
}

void add_book::on_back_clicked()
{
    this->hide();
    library libr;
    libr.setModal(true);
    libr.exec();
}
