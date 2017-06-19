#include "lib.h"
#include "ui_lib.h"
#include <QDialog>
#include <QTreeWidget>
#include <QDateTime>
lib::lib(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lib)
{
    ui->setupUi(this);
    connect(ui->search_edit, SIGNAL(returnPressed()),ui->search_button,SIGNAL(clicked()));
    ui->tree->header()->resizeSection(1,350);
    ui->cart->header()->hide();
    ui->cart->header()->resizeSection(1,45);
    this->setWindowTitle("Main Window");
    Conopen();
    QSqlQuery query1(db),query(db);
    query.prepare("select user_temp from users");
    query.exec();
    query.next();
    QString username=query.value(0).toString();
    query1.prepare("select book_id,book_name,book_author from books");
    query1.exec();
    while(query1.next())
    {
        QString id = query1.value(0).toString();
        QString name = query1.value(1).toString();
        QString author = query1.value(2).toString();
        AddRoot(id,name,author);
    }
    ui->tree->hideColumn(0);
    QSqlQuery qry(db);
    qry.prepare("select * from users where user_name='"+username+"'");
    qry.exec();
    qry.next();
    qDebug() << qry.value("user_role").toInt();
    if(qry.value("user_role").toInt()==3||qry.value("user_role").toInt()==2) ui->admin->setVisible(false);
    if(qry.value("user_role").toInt()==1||qry.value("user_role").toInt()==3) ui->library->setVisible(false);
    if(qry.value("user_role").toInt()==1||qry.value("user_role").toInt()==2) ui->history->setVisible(false);
    if(qry.value("user_role").toInt()==1||qry.value("user_role").toInt()==2) ui->message->setVisible(false);
    if(qry.value("user_role").toInt()==1||qry.value("user_role").toInt()==2) ui->contact->setVisible(false);
    if(qry.value("user_role").toInt()==1||qry.value("user_role").toInt()==3) ui->lib_message->setVisible(false);
    if(qry.value("user_role").toInt()==1||qry.value("user_role").toInt()==3) ui->request->setVisible(false);
    QSqlQuery qry1(db);
    qry1.prepare("select * from users where user_name='"+username+"'");
    qry1.exec();
    qry1.next();
    QString user_id=qry1.value(0).toString();
    QSqlQuery qry2(db);
    qry2.prepare("select * from borrow where borrow_user_id='"+user_id+"'");
    qry2.exec();
    while(qry2.next())
    {
        QString status=qry2.value(3).toString();
        if(status!="Returned")
        {
            QDateTime now=QDateTime::currentDateTime();
            QString borrow=qry2.value(2).toString();
            QDateTime borrow_time=QDateTime::fromString(borrow,"hh:mm:ss dd/MM/yyyy");
            qint64 time=borrow_time.daysTo(now);
            if(time>=14)
            {
                QMessageBox messa;
                messa.setText("Some books are overdue. Please check details in History");
                messa.exec();
            }
        }
    }
    Conclose();
    QPixmap pix(":/new/image/pink.jpg");
    ui->label_5->setPixmap(pix);
    QIcon search_icon(":/new/image/search.png");
    ui->search_button->setIcon(search_icon);
    QIcon history_icon(":/new/image/calibre.png");
    ui->history->setIcon(history_icon);
    QIcon admin_icon(":/new/image/user-male.png");
    ui->admin->setIcon(admin_icon);
    QIcon signout_icon(":/new/image/kshutdown.png");
    ui->sign_out->setIcon(signout_icon);
    QIcon info_icon(":/new/image/sign-info.png");
    ui->info_button->setIcon(info_icon);
    QIcon library_icon(":/new/image/calibre-ebook-edit.png");
    ui->library->setIcon(library_icon);
    QIcon message_icon(":/new/image/bubble.png");
    ui->message->setIcon(message_icon);
    ui->lib_message->setIcon(message_icon);
    QIcon request_icon(":/new/image/bullhorn.png");
    ui->request->setIcon(request_icon);
    QIcon add_icon(":/new/image/box-in.png");
    ui->add_button->setIcon(add_icon);
    QIcon remove_icon(":/new/image/box-out.png");
    ui->remove_button->setIcon(remove_icon);
    QIcon borrow_button(":/new/image/shield-ok.png");
    ui->borrow_button->setIcon(borrow_button);
    QIcon contact_icon(":/new/image/gmail-offline.png");
    ui->contact->setIcon(contact_icon);
    ui->groupBox->setAutoFillBackground(false);
    ui->groupBox_3->setAutoFillBackground(false);
}

lib::~lib()
{
    delete ui;
}

void lib::AddRoot(QString id,QString name,QString author)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->tree);
    item->setText(0,id);
    item->setText(1,name);
    item->setText(2,author);
    ui->tree->addTopLevelItem(item);
}

void lib::AddRootLite(QString id,QString name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->cart);
    item->setText(0,id);
    item->setText(1,name);
    ui->cart->addTopLevelItem(item);
}

void lib::on_search_button_clicked()
{
    Conopen();
    QSqlQuery query1(db);
    query1.prepare("select book_id,book_name,book_author from books");
    query1.exec();
    QString search;
    search=ui->search_edit->text();
    ui->tree->clear();
    while(query1.next())
    {
        QString id = query1.value(0).toString();
        QString name = query1.value(1).toString();
        QString author = query1.value(2).toString();
        if(name.contains(search)||author.contains(search))
        {
            AddRoot(id,name,author);
        }
    }
    ui->tree->hideColumn(0);
    Conclose();
}

void lib::on_tree_itemClicked(QTreeWidgetItem *item)
{
    QString current = item->text(0);
    Conopen();
    QSqlQuery qry;
    qry.prepare("select * from books where book_id='"+current+"' ");
    qry.exec();
    while(qry.next())
    {
        ui->book_name->setText(qry.value(1).toString());
        ui->book_author->setText(qry.value(2).toString());
        ui->book_prize->setText(qry.value(4).toString());
        ui->book_remain->setText(qry.value(5).toString());
        ui->book_des->setPlainText(qry.value(7).toString());
    }
    Conclose();
}

void lib::on_add_button_clicked()
{
    QString book_remain = ui->book_remain->text();
    int remain=book_remain.toInt();
    qDebug() << remain;
    if(remain <=1)
    {
        QMessageBox message;
        message.setText("This book cannot be borrowed");
        message.exec();
    }
    else
    {
    Conopen();
    QTreeWidgetItem *item=ui->tree->currentItem();
    QString current = item->text(0);
    QSqlQuery qry;
    qry.prepare("select * from books where book_id='"+current+"' ");
    qry.exec();
    while(qry.next())
    {
        AddRootLite(qry.value(0).toString(),qry.value(1).toString());
    }
    Conclose();
    ui->cart->hideColumn(0);
}
}
void lib::on_remove_button_clicked()
{
    QTreeWidgetItem *item=ui->cart->currentItem();
    ui->cart->takeTopLevelItem(ui->cart->indexOfTopLevelItem(item));
}

void lib::on_info_button_clicked()
{
    this->hide();
    info infor;
    infor.setModal(true);
    infor.exec();
}



void lib::on_sign_out_clicked()
{
    this->hide();
    MainWindow *mainwindow = new MainWindow;
    mainwindow->show();
}

void lib::on_admin_clicked()
{
    this->hide();
    admin ad;
    ad.setModal(true);
    ad.exec();
}

void lib::on_library_clicked()
{
    this->hide();
    library libr;
    libr.setModal(true);
    libr.exec();
}

void lib::on_borrow_button_clicked()
{
    Conopen();
    QSqlQuery qry(db),qry1(db),qry2(db);
    qry1.prepare("select user_temp from users");
    qry1.exec();
    qry1.next();
    QString username=qry1.value(0).toString();
    qry2.prepare("select * from users where user_name='"+username+"'");
    qry2.exec();
    qry2.next();
    QString id=qry2.value(0).toString();
    QString time=QDateTime::currentDateTime().toString("hh:mm:ss dd/MM/yyyy");
    qry.prepare("insert into borrow (borrow_user_id, borrow_date, borrow_stt) values ('"+id+"','"+time+"', 'Waiting for Confirmation')");
    if(ui->cart->topLevelItemCount()!=0)
    {
        qry.exec();
        QSqlQuery query1(db),query(db),qery(db),qery1(db);
        query1.prepare("select * from borrow");
        query1.exec();
        query1.last();
        QString borrow_id=query1.value(0).toString();
        QMessageBox message;
        message.setText("Borrow request sent");
        message.exec();
        for(int i=0;i<ui->cart->topLevelItemCount();i++)
        {
            QTreeWidgetItem *item=ui->cart->topLevelItem(i);
            QString book_id=item->text(0);
            query.prepare("insert into lend (lend_borrow_id, lend_book_id,lend_stt) values ('"+borrow_id+"','"+book_id+"','Waiting for Confirmation')");
            query.exec();
            qery1.prepare("select book_left from books where book_id='"+book_id+"'");
            qery1.exec();
            qery1.next();
            int left=qery1.value(0).toInt();
            qery.prepare("update books set book_left=:left where book_id='"+book_id+"'");
            qery.bindValue(":left",QString::number(left-1));
            qery.exec();
        }
        ui->cart->clear();
    }
    Conclose();
}

void lib::on_history_clicked()
{
    this->hide();
    history his;
    his.setModal(true);
    his.exec();
}

void lib::on_contact_clicked()
{
    contact cont;
    cont.setModal(true);
    cont.exec();
}

void lib::on_message_clicked()
{
    this->hide();
    user_message um;
    um.setModal(true);
    um.exec();
}

void lib::on_lib_message_clicked()
{
    this->hide();
    lib_message lm;
    lm.setModal(true);
    lm.exec();
}

void lib::on_request_clicked()
{
    this->hide();
    request req;
    req.setModal(true);
    req.exec();
}
