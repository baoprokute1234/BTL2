#include "mess.h"
#include "ui_mess.h"

mess::mess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mess)
{
    ui->setupUi(this);
    ui->mess_preview->header()->resizeSection(1,150);
    Conopen();
    QSqlQuery qry(db),qry1(db);
    qry.prepare("select * from message_to_admin");
    qry.exec();
    while(qry.next())
    {
        QString id=qry.value(1).toString();
        qry1.prepare("select * from users where user_id='"+id+"'");
        qry1.exec();
        qry1.next();
        QString username = qry1.value(1).toString();
        QString time = qry.value(4).toString();
        QString title = qry.value(2).toString();
        QString status;
        if(qry.value(5).toInt()==0) status = "unread";
        else status = "read";
        AddRoot(username,time,title,status);
    }
    Conclose();
}

mess::~mess()
{
    delete ui;
}

void mess::AddRoot(QString username,QString time,QString title,QString status)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->mess_preview);
    item->setText(0,username);
    item->setText(1,time);
    item->setText(2,title);
    item->setText(3,status);
    ui->mess_preview->addTopLevelItem(item);
}

void mess::on_back_clicked()
{
    this->hide();
    admin ad;
    ad.setModal(true);
    ad.exec();
}
