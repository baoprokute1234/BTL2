#include "add_user.h"
#include "ui_add_user.h"
add_user::add_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_user)
{
    ui->setupUi(this);
    QIcon add_icon(":/new/image/sign-add.png");
    ui->pushButton->setIcon(add_icon);
    QIcon back_icon(":/new/image/sign-right.png");
    ui->pushButton_2->setIcon(back_icon);
    QPixmap pix(":/new/image/pink.jpg");
    ui->label_7->setPixmap(pix);
    this->setWindowTitle("Add User");
}

add_user::~add_user()
{
    delete ui;
}

void add_user::on_pushButton_clicked()
{
    Conopen();
    QSqlQuery qry(db);
    QString username=ui->username->text();
    QString password=ui->password->text();
    QString birthday=ui->birthday->text();
    QString cmnd=ui->cmnd->text();
    QString realname=ui->real_name->text();
    QString role=ui->role->currentText();
    qry.prepare("insert into users (user_name, user_passwd, user_role, user_infoname,user_cmnd,user_birthday) values ('"+username+"','"+password+"', '"+role+"', '"+realname+"', '"+cmnd+"', '"+birthday+"')");
    qry.exec();
    Conclose();
    QMessageBox message;
    message.setText("New user added");
    message.exec();
}

void add_user::on_pushButton_2_clicked()
{
    this->hide();
    admin ad;
    ad.setModal(true);
    ad.exec();
}
