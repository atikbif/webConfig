#include "dialogmessagevaradd.h"
#include "ui_dialogmessagevaradd.h"

DialogMessageVarAdd::DialogMessageVarAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMessageVarAdd)
{
    ui->setupUi(this);
}

DialogMessageVarAdd::~DialogMessageVarAdd()
{
    delete ui;
}

QString DialogMessageVarAdd::getMessage() const
{
    return ui->lineEditMessage->text();
}

void DialogMessageVarAdd::setMessage(const QString &value)
{
    ui->lineEditMessage->setText(value);
}

int DialogMessageVarAdd::getType() const
{
    return ui->comboBoxType->currentIndex();
}

void DialogMessageVarAdd::setType(int value)
{
    if((value>=0)&&(value<ui->comboBoxType->count())) {
        ui->comboBoxType->setCurrentIndex(value);
    }
}

QString DialogMessageVarAdd::getParent() const
{
    return ui->comboBoxParent->currentText();
}

void DialogMessageVarAdd::setParent(const QString &value)
{
    ui->comboBoxParent->setCurrentText(value);
}

int DialogMessageVarAdd::getBitNum() const
{
    return ui->spinBoxBitNum->value();
}

void DialogMessageVarAdd::setBitNum(int value)
{
    ui->spinBoxBitNum->setValue(value);
}

void DialogMessageVarAdd::updateParentList(const QStringList &list)
{
    ui->comboBoxParent->clear();
    ui->comboBoxParent->addItems(list);
}
