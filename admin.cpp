#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    Conopen();
    QSqlQuery qry(db);
    qry.prepare("select user_id,user_name,user_passwd,user_role,user_infoname,user_cmnd,user_birthday from users");
    qry.exec();
    while(qry.next())
    {
        ui->list->addItem(qry.value("user_name").toString());
    }
    Conclose();
}

admin::~admin()
{
    delete ui;
}

void admin::on_back_clicked()
{
    this->hide();
    lib library;
    library.setModal(true);
    library.exec();
}

void admin::on_list_clicked()
{
    Conopen();
    QSqlQuery qry(db);
    QString username = ui->list->currentItem()->text();
    qry.prepare("select * from users where user_name='"+username+"'");
    qry.exec();
    while(qry.next())
    {
        ui->username->setText(qry.value("user_name").toString());
        ui->user_id->setText(qry.value("user_id").toString());
        ui->user_passwd->setText(qry.value("user_passwd").toString());
        ui->user_role->setText(qry.value("user_role").toString());
        ui->user_cmnd->setText(qry.value("user_cmnd").toString());
        ui->user_birthday->setText(qry.value("user_birthday").toString());
        ui->real_name->setText(qry.value("user_infoname").toString());
    }
    Conclose();
}


void admin::on_see_password_pressed()
{
    ui->user_passwd->setEchoMode(QLineEdit::Normal);
}

void admin::on_see_password_released()
{
    ui->user_passwd->setEchoMode(QLineEdit::Password);
}

void admin::on_change_info_clicked()
{
    ui->user_birthday->setReadOnly(false);
    ui->username->setReadOnly(false);
    ui->user_role->setReadOnly(false);
    ui->user_cmnd->setReadOnly(false);
    ui->real_name->setReadOnly(false);
}

void admin::on_reset_clicked()
{
    Conopen();
    QSqlQuery qry(db);
    QString username = ui->username->text();
    QString new_password = username;
    qry.prepare("update users set user_name='"+username+"',user_passwd='"+new_password+"' where user_name='"+username+"'");
    qry.exec();
    Conclose();
}

void admin::on_update_clicked()
{
    Conopen();
    QString username = ui->username->text();
    QString realname = ui->real_name->text();
    QString cmnd = ui->user_cmnd->text();
    QString birthday = ui->user_birthday->text();
    QString role = ui->user_role->text();
    qDebug() << username;
    QSqlQuery qry(db);
    qry.prepare("update users set user_name='"+username+"',user_infoname='"+realname+"',user_cmnd='"+cmnd+"',user_birthday='"+birthday+"',user_role='"+role+"' where user_name='"+username+"'");
    qry.exec();
    Conclose();
    ui->user_birthday->setReadOnly(true);
    ui->username->setReadOnly(true);
    ui->user_role->setReadOnly(true);
    ui->user_cmnd->setReadOnly(true);
    ui->real_name->setReadOnly(true);
}

void admin::on_pushButton_clicked()
{
    this->hide();
    add_user add;
    add.setModal(true);
    add.exec();
}

void admin::on_delete_2_clicked()
{
    Conopen();
    QString username=ui->username->text();
    QSqlQuery qry(db);
    qry.prepare("delete from users where user_name='"+username+"'");
    qry.exec();
    QListWidgetItem *item = ui->list->takeItem(ui->list->currentRow());
    delete item;
    Conclose();
}

