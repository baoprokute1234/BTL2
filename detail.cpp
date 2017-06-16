#include "detail.h"
#include "ui_detail.h"

detail::detail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::detail)
{
    ui->setupUi(this);
}

detail::~detail()
{
    delete ui;
}
