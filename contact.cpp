#include "contact.h"
#include "ui_contact.h"

contact::contact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contact)
{
    ui->setupUi(this);
    QIcon send_icon(":/new/image/fly.png");
    ui->send->setIcon(send_icon);
    QPixmap pix(":/new/image/pink.jpg");
    ui->label_5->setPixmap(pix);
    this->setWindowTitle("Contact");
}

contact::~contact()
{
    delete ui;
}

void contact::on_send_clicked()
{
    Conopen();
    const QString &send_to = ui->send_to->currentText();
    if(send_to=="Admin")
    {
        QSqlQuery qry(db),qry1(db),qry2(db);
        qry1.prepare("select user_temp from users");
        qry1.exec();
        qry1.next();
        qry2.prepare("select * from users where user_name='"+qry1.value(0).toString()+"'");
        qry2.exec();
        qry2.next();
        QString time=QDateTime::currentDateTime().toString("hh:mm:ss dd/MM/yyyy");
        qry.prepare("insert into message_to_admin (mess_from_user_id, mess_title, mess_content, mess_date,mess_status) values ('"+qry2.value(0).toString()+"','"+ui->title->text()+"', '"+ui->contact_2->text()+"', '"+time+"', 'Unread')");
        qry.exec();
        this->hide();
    }
    else if(send_to=="Librarian")
    {
        QSqlQuery qry(db),qry1(db),qry2(db);
        qry1.prepare("select user_temp from users");
        qry1.exec();
        qry1.next();
        qry2.prepare("select * from users where user_name='"+qry1.value(0).toString()+"'");
        qry2.exec();
        qry2.next();
        QString time=QDateTime::currentDateTime().toString("hh:mm:ss dd/MM/yyyy");
        qry.prepare("insert into message_to_librarian (mess_from_user_id, mess_title, mess_content, mess_date,mess_status) values ('"+qry2.value(0).toString()+"','"+ui->title->text()+"', '"+ui->contact_2->text()+"', '"+time+"', 'Unread')");
        qry.exec();
        QMessageBox message;
        message.setText("Message Sent");
        message.exec();
    }
    Conclose();
}

/*void contact::on_send_to_currentIndexChanged(const QString &arg1)
{
    qDebug() << arg1;
}*/
