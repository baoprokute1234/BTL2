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
    QIcon update_icon(":/new/image/accessories-media-converter.png");
    ui->update->setIcon(update_icon);
    QIcon change_icon(":/new/image/pencil.png");
    ui->change_info->setIcon(change_icon);
    QIcon reset_icon(":/new/image/am2r.png");
    ui->reset->setIcon(reset_icon);
    QIcon add_icon(":/new/image/sign-add.png");
    ui->pushButton->setIcon(add_icon);
    QIcon delete_icon(":/new/image/sign-delete.png");
    ui->delete_2->setIcon(delete_icon);
    QIcon message_icon(":/new/image/bubble.png");
    ui->message->setIcon(message_icon);
    QIcon back_icon(":/new/image/sign-right.png");
    ui->back->setIcon(back_icon);
    QPixmap pix(":/new/image/pink.jpg");
    ui->label_8->setPixmap(pix);
    this->setWindowTitle("Administrator Tool");
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
    QListWidgetItem *item = ui->list->currentItem();
    QString username1=item->text();
    QSqlQuery query(db);
    query.prepare("select user_passwd from users where user_name='"+username1+"'");
    query.exec();
    query.next();
    ui->user_passwd->setText(query.value(0).toString());
    Conclose();
    QMessageBox message;
    message.setText("Password resetted");
    message.exec();
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
    QMessageBox message;
    message.setText("Info updated");
    message.exec();
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
    QSqlQuery qry1(db);
    QString username=ui->username->text();
    QSqlQuery qry(db);
    qry1.prepare("select user_role from users where user_name='"+username+"'");
    qry1.exec();
    qry1.next();
    if(qry1.value(0).toString().compare("admin")!=0)
    {
    qry.prepare("delete from users where user_name='"+username+"'");
    qry.exec();
    QListWidgetItem *item = ui->list->takeItem(ui->list->currentRow());
    delete item;
    }
    else
    {
        QMessageBox message;
        message.setText("Admin account cannot be deleted");
        message.exec();
    }
    Conclose();
}

void admin::on_message_clicked()
{
    this->hide();
    mess message;
    message.setModal(true);
    message.exec();
}
