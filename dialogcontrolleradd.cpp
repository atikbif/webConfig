#include "dialogcontrolleradd.h"
#include "ui_dialogcontrolleradd.h"

DialogControllerAdd::DialogControllerAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogControllerAdd)
{
    ui->setupUi(this);
}

DialogControllerAdd::~DialogControllerAdd()
{
    delete ui;
}

QString DialogControllerAdd::getIP() const
{
    return ui->lineEditIP->text();
}

void DialogControllerAdd::setIP(const QString &value)
{
    ui->lineEditIP->setText(value);
}

QString DialogControllerAdd::getName() const
{
    return ui->lineEditName->text();
}

void DialogControllerAdd::setName(const QString &value)
{
    ui->lineEditName->setText(value);
}

int DialogControllerAdd::getPort() const
{
    return ui->spinBoxPort->value();
}

void DialogControllerAdd::setPort(int value)
{
    ui->spinBoxPort->setValue(value);
}
