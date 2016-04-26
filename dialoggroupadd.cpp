#include "dialoggroupadd.h"
#include "ui_dialoggroupadd.h"

DialogGroupAdd::DialogGroupAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGroupAdd)
{
    ui->setupUi(this);
}

DialogGroupAdd::~DialogGroupAdd()
{
    delete ui;
}

QString DialogGroupAdd::getName() const
{
    return ui->lineEdit->text();
}
