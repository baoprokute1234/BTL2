#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlError>
#include <QDir>
#include <QFile>
#include <QSqlQuery>
#include <QtGui>
#include <QMessageBox>
#include <QPixmap>

//#include "global_objects.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Sign in");
    if(db.open()) ui->status->setText("Connected");
    QPixmap pix(":/new/image/texture.jpg");
    ui->label_2->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()
{
    QString username,password;
    username=ui->username_edit->text();
    password=ui->password_edit->text();
    Conopen();
    if(!db.isOpen())
    {
        qDebug() << "Failed to open the database";
        return;
    }
    QSqlQuery query(db);
    query.prepare("select * from users where user_name='"+username+"' and user_passwd='"+password+"'");
    if(query.exec())
    {
        int count=0;
        while(query.next())
        {
            count++;
        }
        if(count==1)
        {
            ui->status->setText("Login Successed");

            QSqlQuery qry;
            qry.prepare("update users set user_temp='"+username+"'");
            if(qry.exec()) qDebug() << "OK";
            else qDebug() <<qry.lastError().text();

            Conclose();
            this->hide();
            lib library;
            library.setModal(true);
            library.exec();
        }
        if(count<1) ui->status->setText("Login Failed");
    }
}
