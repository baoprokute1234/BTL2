#include "lib_message.h"
#include "ui_lib_message.h"
QString mess_id_1;
lib_message::lib_message(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lib_message)
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
    this->setWindowTitle("Messages to Librarian");
}

lib_message::~lib_message()
{
    delete ui;
}

void lib_message::AddRoot(QString id,QString username,QString time,QString title,QString status)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->mess_preview);
    item->setText(0,id);
    item->setText(1,username);
    item->setText(2,time);
    item->setText(3,title);
    item->setText(4,status);
    ui->mess_preview->addTopLevelItem(item);
}

void lib_message::on_back_clicked()
{
    this->hide();
    lib libr;
    libr.setModal(true);
    libr.exec();
}

void lib_message::on_mess_preview_itemClicked(QTreeWidgetItem *item)
{
    mess_id_1=item->text(0);
    Conopen();
    QSqlQuery qry(db),qry1(db);
    qry.prepare("select * from message_to_librarian where mess_id='"+mess_id_1+"'");
    qry.exec();
    qry.next();
    ui->mess_box->setText(qry.value(3).toString());
    qry1.prepare("update message_to_librarian set mess_status='Read' where mess_id='"+mess_id_1+"'");
    qry1.exec();
    Conclose();
    ReloadView();
}

void lib_message::on_reply_clicked()
{
    Conopen();
    QSqlQuery qry(db),qry1(db);
    qry1.prepare("select * from message_to_librarian where mess_id='"+mess_id_1+"'");
    qry1.exec();
    qry1.next();
    QString id=qry1.value(1).toString();
    QString title=ui->title->text();
    QString content = ui->replay_edit->text();
    QString time=QDateTime::currentDateTime().toString("hh:mm:ss dd/MM/yyyy");
    qry.prepare("insert into message_to_user (mess_to_user_id, mess_title, mess_content,mess_date ,mess_status,mess_from) values ('"+id+"','"+title+"', '"+content+"', '"+time+"', 'Unread', 'Librarian')");
    qry.exec();
    Conclose();
}

void lib_message::ReloadView()
{
    ui->mess_preview->clear();
    Conopen();
    QSqlQuery qry(db),qry1(db);
    qry.prepare("select * from message_to_librarian");
    qry.exec();
    while(qry.next())
    {
        QString id=qry.value(1).toString();
        qry1.prepare("select * from users where user_id='"+id+"'");
        qry1.exec();
        qry1.next();
        QString mess_from_id=qry.value(0).toString();
        QString username = qry1.value(1).toString();
        QString time = qry.value(4).toString();
        QString title = qry.value(2).toString();
        QString status = qry.value(5).toString();
        AddRoot(mess_from_id,username,time,title,status);
    }
    ui->mess_preview->hideColumn(0);
    Conclose();
}
