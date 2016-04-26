#include "dialoganalogvaradd.h"
#include "ui_dialoganalogvaradd.h"

DialogAnalogVarAdd::DialogAnalogVarAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAnalogVarAdd)
{
    ui->setupUi(this);
}

DialogAnalogVarAdd::~DialogAnalogVarAdd()
{
    delete ui;
}

QString DialogAnalogVarAdd::getName() const
{
    return ui->lineEditName->text();
}

void DialogAnalogVarAdd::setName(const QString &value)
{
    ui->lineEditName->setText(value);
}

int DialogAnalogVarAdd::getPriority() const
{
    return ui->comboBoxPriority->currentIndex();
}

void DialogAnalogVarAdd::setPriority(int value)
{
    if((value>=0)&&(value<ui->comboBoxPriority->count())) {
        ui->comboBoxPriority->setCurrentIndex(value);
    }
}

int DialogAnalogVarAdd::getAddress() const
{
    return ui->spinBoxAddress->value();
}

void DialogAnalogVarAdd::setAddress(int value)
{
    ui->spinBoxAddress->setValue(value);
}

int DialogAnalogVarAdd::getScaleMin() const
{
    return ui->spinBoxScaleMin->value();
}

void DialogAnalogVarAdd::setScaleMin(int value)
{
    ui->spinBoxScaleMin->setValue(value);
}

int DialogAnalogVarAdd::getScaleMax() const
{
    return ui->spinBoxScaleMax->value();
}

void DialogAnalogVarAdd::setScaleMax(int value)
{
    ui->spinBoxScaleMax->setValue(value);
}

int DialogAnalogVarAdd::getAlarmMin() const
{
    return ui->spinBoxAlarmMin->value();
}

void DialogAnalogVarAdd::setAlarmMin(int value)
{
    ui->spinBoxAlarmMin->setValue(value);
}

int DialogAnalogVarAdd::getAlarmMax() const
{
    return ui->spinBoxAlarmMax->value();
}

void DialogAnalogVarAdd::setAlarmMax(int value)
{
    ui->spinBoxAlarmMax->setValue(value);
}

double DialogAnalogVarAdd::getCoeff() const
{
    return ui->doubleSpinBoxCoeff->value();
}

void DialogAnalogVarAdd::setCoeff(double value)
{
    ui->doubleSpinBoxCoeff->setValue(value);
}
