#include "user_message.h"
#include "ui_user_message.h"

user_message::user_message(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_message)
{
    ui->setupUi(this);
    ui->mess_preview->header()->resizeSection(1,100);
    ui->mess_preview->header()->resizeSection(2,150);
    Conopen();
    QSqlQuery qry(db),qry1(db),qry2(db);
    qry.prepare("select user_temp from users");
    qry.exec();
    qry.next();
    QString username=qry.value(0).toString();
    qry1.prepare("select * from users where user_name='"+username+"'");
    qry1.exec();
    qry1.next();
    QString id=qry1.value(0).toString();
    qry2.prepare("select * from message_to_user where mess_to_user_id='"+id+"'");
    qry2.exec();
    while(qry2.next())
    {
        QString mess_id = qry2.value(0).toString();
        QString title=qry2.value(2).toString();
        QString time = qry2.value(4).toString();
        QString from = qry2.value(6).toString();
        QString status = qry2.value(5).toString();
        AddRoot(mess_id,title,time,from,status);
    }
    ui->mess_preview->hideColumn(0);
    Conclose();
    QIcon reply_icon(":/new/image/bubbles-alt.png");
    ui->reply->setIcon(reply_icon);
    QIcon back_icon(":/new/image/sign-right.png");
    ui->back->setIcon(back_icon);
    QPixmap pix(":/new/image/pink.jpg");
    ui->label_2->setPixmap(pix);
    this->setWindowTitle("Messages to User");
}

user_message::~user_message()
{
    delete ui;
}

void user_message::on_mess_preview_itemClicked(QTreeWidgetItem *item)
{
    Conopen();
    QString id = item->text(0);
    qDebug() << id;
    QSqlQuery qry(db);
    qry.prepare("select * from message_to_user where mess_id='"+id+"'");
    qry.exec();
    qry.next();
    ui->mess_box->setText(qry.value(3).toString());
    QSqlQuery qry1(db);
    qry1.prepare("update message_to_user set mess_status='Read' where mess_id='"+id+"'");
    qry1.exec();
    Conclose();
    ReloadView();
}

void user_message::AddRoot(QString id,QString title,QString time,QString from,QString status)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->mess_preview);
    item->setText(0,id);
    item->setText(1,title);
    item->setText(2,time);
    item->setText(3,from);
    item->setText(4,status);
    ui->mess_preview->addTopLevelItem(item);
}

void user_message::on_back_clicked()
{
    this->hide();
    lib libr;
    libr.setModal(true);
    libr.exec();
}

void user_message::on_reply_clicked()
{
    Conopen();
}

void user_message::ReloadView()
{
    ui->mess_preview->clear();
    Conopen();
    QSqlQuery qry(db),qry1(db),qry2(db);
    qry.prepare("select user_temp from users");
    qry.exec();
    qry.next();
    QString username=qry.value(0).toString();
    qry1.prepare("select * from users where user_name='"+username+"'");
    qry1.exec();
    qry1.next();
    QString id=qry1.value(0).toString();
    qry2.prepare("select * from message_to_user where mess_to_user_id='"+id+"'");
    qry2.exec();
    while(qry2.next())
    {
        QString mess_id = qry2.value(0).toString();
        QString title=qry2.value(2).toString();
        QString time = qry2.value(4).toString();
        QString from = qry2.value(6).toString();
        QString status=qry2.value(5).toString();
        AddRoot(mess_id,title,time,from,status);
    }
    ui->mess_preview->hideColumn(0);
    Conclose();
}
