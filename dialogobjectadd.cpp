#include "dialogobjectadd.h"
#include "ui_dialogobjectadd.h"

DialogObjectAdd::DialogObjectAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogObjectAdd)
{
    ui->setupUi(this);
}

DialogObjectAdd::~DialogObjectAdd()
{
    delete ui;
}

QString DialogObjectAdd::getName() const
{
    return ui->lineEditName->text();
}

void DialogObjectAdd::setName(const QString &value)
{
    ui->lineEditName->setText(value);
}

QString DialogObjectAdd::getComment() const
{
    return ui->lineEditComment->text();
}

void DialogObjectAdd::setComment(const QString &value)
{
    ui->lineEditComment->setText(value);
}

int DialogObjectAdd::getPeriod() const
{
    return ui->spinBoxPeriod->value();
}

void DialogObjectAdd::setPeriod(int value)
{
    ui->spinBoxPeriod->setValue(value);
}

int DialogObjectAdd::getWaitTime() const
{
    return ui->spinBoxWaitTime->value();
}

void DialogObjectAdd::setWaitTime(int value)
{
    ui->spinBoxWaitTime->setValue(value);
}
