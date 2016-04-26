#include "dialoggroupchangename.h"
#include "ui_dialoggroupchangename.h"

QString DialogGroupChangeName::getGrName() const
{
    return ui->lineEdit->text();
}

void DialogGroupChangeName::setGrName(const QString &value)
{
    ui->lineEdit->setText(value);
}

DialogGroupChangeName::DialogGroupChangeName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGroupChangeName)
{
    ui->setupUi(this);
}

DialogGroupChangeName::~DialogGroupChangeName()
{
    delete ui;
}
