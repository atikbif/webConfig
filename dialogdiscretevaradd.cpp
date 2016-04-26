#include "dialogdiscretevaradd.h"
#include "ui_dialogdiscretevaradd.h"

DialogDiscreteVarAdd::DialogDiscreteVarAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDiscreteVarAdd)
{
    ui->setupUi(this);
}

DialogDiscreteVarAdd::~DialogDiscreteVarAdd()
{
    delete ui;
}

QString DialogDiscreteVarAdd::getName() const
{
    return ui->lineEditName->text();
}

void DialogDiscreteVarAdd::setName(const QString &value)
{
    ui->lineEditName->setText(value);
}

int DialogDiscreteVarAdd::getPriority() const
{
    return ui->comboBoxPriority->currentIndex();
}

void DialogDiscreteVarAdd::setPriority(int value)
{
    if((value>=0)&&(value<ui->comboBoxPriority->count())) {
        ui->comboBoxPriority->setCurrentIndex(value);
    }
}

void DialogDiscreteVarAdd::updateParentList(const QStringList &list)
{
    ui->comboBoxParent->clear();
    if(list.count()) {
        ui->comboBoxParent->addItems(list);
        ui->comboBoxParent->setCurrentIndex(0);
    }
}

QString DialogDiscreteVarAdd::getParent() const
{
    return ui->comboBoxParent->currentText();
}

void DialogDiscreteVarAdd::setParent(const QString &value)
{
    ui->comboBoxParent->setCurrentText(value);
}

int DialogDiscreteVarAdd::getBitNum() const
{
    return ui->spinBoxBitNum->value();
}

void DialogDiscreteVarAdd::setBitNum(int value)
{
    ui->spinBoxBitNum->setValue(value);
}
