#include "add_user.h"
#include "ui_add_user.h"

//#inc
add_user::add_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_user)
{
    ui->setupUi(this);
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
    QString role=ui->role->text();
    qry.prepare("insert into users (user_name, user_passwd, user_role, user_infoname,user_cmnd,user_birthday) values ('"+username+"','"+password+"', '"+role+"', '"+realname+"', '"+cmnd+"', '"+birthday+"')");
    if(!qry.exec())
        qDebug() << "??";
    Conclose();
}

void add_user::on_pushButton_2_clicked()
{
    this->hide();
    admin ad;
    ad.setModal(true);
    ad.exec();
}
