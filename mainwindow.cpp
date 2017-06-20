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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->username_edit, SIGNAL(returnPressed()),ui->login,SIGNAL(clicked()));
    connect(ui->password_edit, SIGNAL(returnPressed()),ui->login,SIGNAL(clicked()));
    this->setWindowTitle("Sign in");
    if(db.open()) ui->status->setText("Connected");
    QPixmap pix(":/new/image/default.png");
    ui->label_2->setPixmap(pix);
    QPixmap pix2(":/new/image/texture.jpg");
    ui->label->setPixmap(pix2);
    ui->about->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(255, 255, 255)");
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

void MainWindow::on_about_clicked()
{
    QMessageBox message;
    message.setText("BTBN team: \n"
                    "Trương Như Bảo - 1610204 \n"
                    "Nguyễn Trương Ngọc Bách - 1610155 \n"
                    "Võ Khắc Trí - 1613754 \n"
                    "Nguyễn Minh Nhựt - 1612483");
    message.exec();
}
