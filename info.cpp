#include "info.h"
#include "ui_info.h"
#include <QMessageBox>
#include <QDialog>
#include <QTreeWidget>

info::info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
    Conopen();
    QSqlQuery query(db),query1(db),qry(db);
    query.prepare("select user_temp from users");
    query.exec();
    query.next();
    QString username = query.value("user_temp").toString();
    qry.prepare("select * from users where user_name='"+username+"'");
    qry.exec();
    while(qry.next())
    {
        ui->real_name->setText(qry.value("user_infoname").toString());
        ui->user_name->setText(qry.value("user_name").toString());
        ui->cmnd->setText(qry.value("user_cmnd").toString());
        ui->birthday->setText(qry.value("user_birthday").toString());
        ui->role->setText(qry.value("user_role").toString());
    }
    Conclose();
    QIcon update_icon(":/new/image/accessories-media-converter.png");
    ui->update_password->setIcon(update_icon);
    QIcon tab2_icon(":/new/image/key.png");
    ui->tabWidget->setTabIcon(1,tab2_icon);
    QIcon tab1_icon(":/new/image/profile.png");
    ui->tabWidget->setTabIcon(0,tab1_icon);
    QIcon back_icon(":/new/image/sign-right.png");
    ui->back_button->setIcon(back_icon);
    QIcon change_icon(":/new/image/pencil.png");
    ui->change_info->setIcon(change_icon);
    ui->update->setIcon(update_icon);
    QPixmap pix(":/new/image/pink.jpg");
    ui->label_9->setPixmap(pix);
    ui->label_10->setPixmap(pix);
    ui->label_11->setPixmap(pix);
    this->setWindowTitle("Personal Information");
}

info::~info()
{
    delete ui;
}

void info::on_change_info_clicked()
{
    ui->real_name->setReadOnly(false);
    ui->cmnd->setReadOnly(false);
    ui->birthday->setReadOnly(false);
}

void info::on_update_clicked()
{
    Conopen();
    QString username = ui->user_name->text();
    QString realname = ui->real_name->text();
    QString cmnd = ui->cmnd->text();
    QString birthday = ui->birthday->text();
    qDebug() << username;
    QSqlQuery qry(db);
    qry.prepare("update users set user_name='"+username+"',user_infoname='"+realname+"',user_cmnd='"+cmnd+"',user_birthday='"+birthday+"' where user_name='"+username+"'");
    qry.exec();
    Conclose();
    ui->real_name->setReadOnly(true);
    ui->cmnd->setReadOnly(true);
    ui->birthday->setReadOnly(true);
    QMessageBox message;
    message.setText("Info updated");
    message.exec();
}

void info::on_update_password_clicked()
{
    QString username = ui->user_name->text();
    QString current_password = ui->current_password->text();
    QString new_password = ui->new_password->text();
    QString retype_password = ui->retype_password->text();
    Conopen();
    QSqlQuery qry(db),query(db);
    qry.prepare("select * from users where user_name='"+username+"'");
    qry.exec();
    qry.next();
    if(current_password.compare(qry.value("user_passwd").toString())) ui->status->setText("Wrong password");
    else if(new_password.compare(retype_password)) ui->status->setText("Please type new password");
    else
    {
        query.prepare("update users set user_name='"+username+"',user_passwd='"+new_password+"' where user_name='"+username+"'");
        query.exec();
        ui->status->setText("Success");
    }
    Conclose();
    QMessageBox message;
    message.setText("Password updated");
    message.exec();
}
void info::on_back_button_clicked()
{
    this->hide();
    lib library;
    library.setModal(true);
    library.exec();
}
