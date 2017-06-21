#include "mess.h"
#include "ui_mess.h"
QString mess_id;
mess::mess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mess)
{
    ui->setupUi(this);
    ui->mess_preview->header()->resizeSection(1,100);
    ui->mess_preview->header()->resizeSection(2,150);
    ReloadView();
    QIcon reply_icon(":/new/image/bubbles-alt.png");
    ui->reply->setIcon(reply_icon);
    QIcon back_icon(":/new/image/sign-right.png");
    ui->back->setIcon(back_icon);
    QPixmap pix(":/new/image/pink.jpg");
    ui->label->setPixmap(pix);
    ui->mess_preview->header()->resizeSection(3,200);
    this->setWindowTitle("Messages to Admin");
}

mess::~mess()
{
    delete ui;
}

void mess::AddRoot(QString id,QString username,QString time,QString title,QString status)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->mess_preview);
    item->setText(0,id);
    item->setText(1,username);
    item->setText(2,time);
    item->setText(3,title);
    item->setText(4,status);
    ui->mess_preview->addTopLevelItem(item);
}

void mess::on_back_clicked()
{
    this->hide();
    admin ad;
    ad.setModal(true);
    ad.exec();
}

void mess::on_mess_preview_itemClicked(QTreeWidgetItem *item)
{
    mess_id=item->text(0);
    Conopen();
    QSqlQuery qry(db),qry1(db);
    qry.prepare("select * from message_to_admin where mess_id='"+mess_id+"'");
    qry.exec();
    qry.next();
    ui->mess_box->setPlainText(qry.value(3).toString());
    qry1.prepare("update message_to_admin set mess_status='Read' where mess_id='"+mess_id+"'");
    qry1.exec();
    Conclose();
    ReloadView();
}

void mess::on_reply_clicked()
{
    Conopen();
    QSqlQuery qry(db),qry1(db);
    qry1.prepare("select * from message_to_admin where mess_id='"+mess_id+"'");
    qry1.exec();
    qry1.next();
    QString id=qry1.value(1).toString();
    QString title=ui->title->text();
    QString content = ui->replay_edit->toPlainText();
    QString time=QDateTime::currentDateTime().toString("hh:mm:ss dd/MM/yyyy");
    qry.prepare("insert into message_to_user (mess_to_user_id, mess_title, mess_content,mess_date ,mess_status,mess_from) values ('"+id+"','"+title+"', '"+content+"', '"+time+"', 'Unread', 'Admin')");
    qry.exec();
    Conclose();
    QMessageBox message;
    message.setText("Message sent");
    message.exec();
}

void mess::ReloadView()
{
    ui->mess_preview->clear();
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
        QString mess_id=qry.value(0).toString();
        QString username = qry1.value(1).toString();
        QString time = qry.value(4).toString();
        QString title = qry.value(2).toString();
        QString status = qry.value(5).toString();
        AddRoot(mess_id,username,time,title,status);
    }
    ui->mess_preview->hideColumn(0);
    Conclose();
}
