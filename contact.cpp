#include "contact.h"
#include "ui_contact.h"

contact::contact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contact)
{
    ui->setupUi(this);
}

contact::~contact()
{
    delete ui;
}

void contact::on_send_clicked()
{
    Conopen();
    QSqlQuery qry(db),qry1(db),qry2(db);
    qry1.prepare("select user_temp from users");
    qry1.exec();
    qry1.next();
    qry2.prepare("select * from users where user_name='"+qry1.value(0).toString()+"'");
    qry2.exec();
    qry2.next();
    QString time=QDateTime::currentDateTime().toString("hh:mm:ss dd/MM/yyyy");
    qry.prepare("insert into message_to_admin (mess_from_user_id, mess_title, mess_content, mess_date,mess_status) values ('"+qry2.value(0).toString()+"','"+ui->title->text()+"', '"+ui->contact_2->text()+"', '"+time+"', '0')");
    qry.exec();
    this->hide();
    Conclose();
}
