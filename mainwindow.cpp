#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoggroupadd.h"
#include "objectgroup.h"
#include <QMenu>
#include "dialoggroupchangename.h"
#include "dialogcontrolleradd.h"
#include "dialogobjectadd.h"
#include "dialoganalogvaradd.h"
#include "dialogdiscretevaradd.h"
#include "dialogmessagevaradd.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), contextItem(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->treeWidget->setSortingEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    DialogGroupAdd *dialog = new DialogGroupAdd();
    int ret = dialog->exec();
    if(ret==QDialog::Accepted) {
        QString name = dialog->getName();
        if(!name.isEmpty()) {
            ObjectGroup group;
            group.setName(name);
            if(root.addGroup(group)) {
                QSharedPointer<ObjectGroup> ptr = root.getGroup(name);
                if(!ptr->getName().isEmpty()) {
                    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << name << "группа объектов",0);
                    void *vPtr = (void*)ptr.data();
                    treeLink.insert(item,vPtr);
                    ui->treeWidget->addTopLevelItem(item);
                }
            }
        }
    }
    delete dialog;
}

void MainWindow::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem *item = ui->treeWidget->itemAt(pos);
    if(item!=nullptr) {
        contextItem = item;
        switch(item->type()) {
            case 0: // group
                {
                    QMenu *menu=new QMenu(this);
                    menu->addAction(QString("Добавить объект"), this,SLOT(addObject()));
                    menu->addAction(QString("Изменить название"), this, SLOT(changeGroupName()));
                    menu->addSeparator();
                    menu->addAction(QString("Удалить группу"), this,SLOT(deleteGroup()));
                    menu->popup(ui->treeWidget->viewport()->mapToGlobal(pos));
                }
                break;
            case 1:
                {
                    QMenu *menu=new QMenu(this);
                    menu->addAction(QString("Добавить контроллер"), this,SLOT(addController()));
                    menu->addAction(QString("Свойства"), this, SLOT(editObject()));
                    menu->addSeparator();
                    menu->addAction(QString("Удалить объект"), this,SLOT(deleteObject()));
                    menu->popup(ui->treeWidget->viewport()->mapToGlobal(pos));
                }
                break;
            case 2:
                {
                    QMenu *menu=new QMenu(this);
                    menu->addAction(QString("Добавить аналоговую переменную"), this,SLOT(addAnalogVar()));
                    menu->addAction(QString("Добавить дискретную переменную"), this,SLOT(addDiscreteVar()));
                    menu->addAction(QString("Добавить сообщение"), this,SLOT(addMessage()));
                    menu->addAction(QString("Свойства"), this, SLOT(editController()));
                    menu->addSeparator();
                    menu->addAction(QString("Удалить контроллер"), this,SLOT(deleteObject()));
                    menu->popup(ui->treeWidget->viewport()->mapToGlobal(pos));
                }
                break;
            case 3:
                {
                    QMenu *menu=new QMenu(this);
                    menu->addAction(QString("Свойства"), this, SLOT(editAnalogVar()));
                    menu->addSeparator();
                    menu->addAction(QString("Удалить переменную"), this,SLOT(deleteAnalogVar()));
                    menu->popup(ui->treeWidget->viewport()->mapToGlobal(pos));
                }
                break;
            case 4:
                {
                    QMenu *menu=new QMenu(this);
                    menu->addAction(QString("Свойства"), this, SLOT(editDiscreteVar()));
                    menu->addSeparator();
                    menu->addAction(QString("Удалить переменную"), this,SLOT(deleteDiscreteVar()));
                    menu->popup(ui->treeWidget->viewport()->mapToGlobal(pos));
                }
                break;
            case 5:
                {
                    QMenu *menu=new QMenu(this);
                    menu->addAction(QString("Свойства"), this, SLOT(editMessageVar()));
                    menu->addSeparator();
                    menu->addAction(QString("Удалить переменную"), this,SLOT(deleteMessageVar()));
                    menu->popup(ui->treeWidget->viewport()->mapToGlobal(pos));
                }
                break;
            default:
                break;
        }
    }
}

void MainWindow::addController()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            DispObject *ob = (DispObject*)ptr;
            DialogControllerAdd *dialog = new DialogControllerAdd();
            int ret = dialog->exec();
            if(ret==QDialog::Accepted) {
                Controller plc;
                plc.setName(dialog->getName());
                plc.setIp(dialog->getIP());
                plc.setPort(dialog->getPort());
                if((!plc.getName().isEmpty())&&(ob->addController(plc))) {
                    QSharedPointer<Controller> cPtr = ob->getController(plc.getName());
                    if(!cPtr->getName().isEmpty()) {
                        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<plc.getName()<<"контроллер",2);
                        contextItem->addChild(item);
                        treeLink.insert(item,(void*)cPtr.data());
                    }
                }
            }
            delete dialog;
        }
    }
}

void MainWindow::addObject()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            ObjectGroup *gr = (ObjectGroup*)ptr;
            DialogObjectAdd *dialog = new DialogObjectAdd();
            int ret = dialog->exec();
            if(ret==QDialog::Accepted) {
                DispObject ob;
                ob.setName(dialog->getName());
                ob.setComment(dialog->getComment());
                ob.setPeriod(dialog->getPeriod());
                ob.setWaitTime(dialog->getWaitTime());
                if((!ob.getName().isEmpty())&&(gr->addObject(ob))) {
                    QSharedPointer<DispObject> obPtr = gr->getObject(ob.getName());
                    if(!obPtr->getName().isEmpty()) {
                        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<ob.getName()<<"объект",1);
                        contextItem->addChild(item);
                        treeLink.insert(item,(void*)obPtr.data());
                    }
                }
            }
            delete dialog;
        }
    }
}

void MainWindow::deleteGroup()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            ObjectGroup *gr = (ObjectGroup*)ptr;
            QString grName = gr->getName();
            treeLink.remove(contextItem);
            delete contextItem;
            root.deleteGroup(grName);
        }
    }
}

void MainWindow::changeGroupName()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            ObjectGroup *gr = (ObjectGroup*)ptr;
            QString grName = gr->getName();

            DialogGroupChangeName *dialog = new DialogGroupChangeName();
            dialog->setGrName(grName);
            int ret = dialog->exec();
            if(ret==QDialog::Accepted) {
                grName = dialog->getGrName();
                gr->setName(grName);
                contextItem->setText(0,grName);
            }
            delete dialog;
        }
    }
}

void MainWindow::editObject()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            DispObject *ob = (DispObject*)ptr;
            DialogObjectAdd *dialog = new DialogObjectAdd();
            dialog->setName(ob->getName());
            dialog->setComment(ob->getComment());
            dialog->setPeriod(ob->getPeriod());
            dialog->setWaitTime(ob->getWaitTime());
            int ret = dialog->exec();
            if(ret==QDialog::Accepted) {
                ob->setName(dialog->getName());
                ob->setComment(dialog->getComment());
                ob->setPeriod(dialog->getPeriod());
                ob->setWaitTime(dialog->getWaitTime());
                contextItem->setText(0,ob->getName());
            }
            delete dialog;
        }
    }
}

void MainWindow::deleteObject()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            DispObject *ob = (DispObject*)ptr;
            QString obName = ob->getName();
            QTreeWidgetItem *parItem = contextItem->parent();
            if(parItem!=nullptr) {
                if(treeLink.keys().contains(parItem)) {
                    void *parPtr = treeLink.value(parItem);
                    ObjectGroup *gr = (ObjectGroup*)parPtr;
                    gr->deleteObject(obName);
                    treeLink.remove(contextItem);
                    delete contextItem;
                }
            }
        }
    }
}

void MainWindow::addAnalogVar()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            Controller *c = (Controller*)ptr;
            DialogAnalogVarAdd *dialog = new DialogAnalogVarAdd();
            int ret = dialog->exec();
            if(ret==QDialog::Accepted) {
                AnalogVar var;
                var.setComment(dialog->getName());
                var.setDPrior((AnalogVar::displPriority)dialog->getPriority());
                var.setAddress(dialog->getAddress());
                var.setScaleMin(dialog->getScaleMin());
                var.setScaleMax(dialog->getScaleMax());
                var.setNormMin(dialog->getAlarmMin());
                var.setNormMax(dialog->getAlarmMax());
                var.setCoeff(dialog->getCoeff());
                if((!var.getComment().isEmpty())&&(c->addAnVar(var))) {
                    QSharedPointer<AnalogVar> vPtr = c->getAnalogVar(var.getComment());
                    if(!vPtr->getComment().isEmpty()) {
                        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<var.getComment()<<"аналоговая переменная",3);
                        contextItem->addChild(item);
                        treeLink.insert(item,(void*)vPtr.data());
                    }
                }
            }
            delete dialog;
        }
    }
}

void MainWindow::addDiscreteVar()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            Controller *c = (Controller*)ptr;
            DialogDiscreteVarAdd *dialog = new DialogDiscreteVarAdd();
            dialog->updateParentList(c->getAnalogVarsComments());
            int ret = dialog->exec();
            if(ret==QDialog::Accepted) {
                DiscreteVar var;
                var.setComment(dialog->getName());
                var.setDPrior((DiscreteVar::displPriority)dialog->getPriority());
                var.setParentName(dialog->getParent());
                var.setBitNum(dialog->getBitNum());
                if((!var.getComment().isEmpty())&&(c->addDiscreteVar(var))) {
                    QSharedPointer<DiscreteVar> vPtr = c->getDiscreteVar(var.getComment());
                    if(!vPtr->getComment().isEmpty()) {
                        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<var.getComment()<<"дискретная переменная",4);
                        contextItem->addChild(item);
                        treeLink.insert(item,(void*)vPtr.data());
                    }
                }
            }
            delete dialog;
        }
    }
}

void MainWindow::addMessage()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            Controller *c = (Controller*)ptr;
            DialogMessageVarAdd *dialog = new DialogMessageVarAdd();
            dialog->updateParentList(c->getAnalogVarsComments());
            int ret = dialog->exec();
            if(ret==QDialog::Accepted) {
                MessageVar var;
                var.setMessage(dialog->getMessage());
                var.setType((MessageVar::mesType)dialog->getType());
                var.setParentName(dialog->getParent());
                var.setBitNum(dialog->getBitNum());
                if((!var.getMessage().isEmpty())&&(c->addMessageVar(var))) {
                    QSharedPointer<MessageVar> vPtr = c->getMessageVar(var.getMessage());
                    if(!vPtr->getMessage().isEmpty()) {
                        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<var.getMessage()<<"сообщение",5);
                        contextItem->addChild(item);
                        treeLink.insert(item,(void*)vPtr.data());
                    }
                }
            }
            delete dialog;
        }
    }
}

void MainWindow::editController()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            Controller *c = (Controller*)ptr;
            DialogControllerAdd *dialog = new DialogControllerAdd();
            dialog->setName(c->getName());
            dialog->setPort(c->getPort());
            dialog->setIP(c->getIp());
            int ret = dialog->exec();
            if(ret==QDialog::Accepted) {
                c->setName(dialog->getName());
                c->setPort(dialog->getPort());
                c->setIp(dialog->getIP());
                contextItem->setText(0,c->getName());
            }
            delete dialog;
        }
    }
}

void MainWindow::deleteController()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            Controller *c = (Controller*)ptr;
            QString cName = c->getName();
            QTreeWidgetItem *parItem = contextItem->parent();
            if(parItem!=nullptr) {
                if(treeLink.keys().contains(parItem)) {
                    void *parPtr = treeLink.value(parItem);
                    DispObject *ob = (DispObject*)parPtr;
                    ob->deleteController(cName);
                    treeLink.remove(contextItem);
                    delete contextItem;
                }
            }
        }
    }
}

void MainWindow::editAnalogVar()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            AnalogVar *var = (AnalogVar*)ptr;
            DialogAnalogVarAdd *dialog = new DialogAnalogVarAdd();
            dialog->setName(var->getComment());
            dialog->setPriority(var->getDPrior());
            dialog->setAddress(var->getAddress());
            dialog->setScaleMin(var->getScaleMin());
            dialog->setScaleMax(var->getScaleMax());
            dialog->setAlarmMin(var->getNormMin());
            dialog->setAlarmMax(var->getNormMax());
            dialog->setCoeff(var->getCoeff());
            int ret = dialog->exec();
            if(ret==QDialog::Accepted) {
                var->setComment(dialog->getName());
                var->setDPrior((AnalogVar::displPriority)dialog->getPriority());
                var->setAddress(dialog->getAddress());
                var->setScaleMin(dialog->getScaleMin());
                var->setScaleMax(dialog->getScaleMax());
                var->setNormMin(dialog->getAlarmMin());
                var->setNormMax(dialog->getAlarmMax());
                var->setCoeff(dialog->getCoeff());
                contextItem->setText(0,var->getComment());
            }
            delete dialog;
        }
    }
}

void MainWindow::deleteAnalogVar()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            AnalogVar *var = (AnalogVar*)ptr;
            QString vComment = var->getComment();
            QTreeWidgetItem *parItem = contextItem->parent();
            if(parItem!=nullptr) {
                if(treeLink.keys().contains(parItem)) {
                    void *parPtr = treeLink.value(parItem);
                    Controller *c = (Controller*)parPtr;
                    c->deleteAnVar(vComment);
                    treeLink.remove(contextItem);
                    delete contextItem;
                }
            }
        }
    }
}

void MainWindow::editDiscreteVar()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            QTreeWidgetItem *parItem = contextItem->parent();
            if(parItem!=nullptr) {
                if(treeLink.keys().contains(parItem)) {
                    void *parPtr = treeLink.value(parItem);
                    Controller *c = (Controller*)parPtr;
                    DiscreteVar *var = (DiscreteVar*)ptr;
                    DialogDiscreteVarAdd *dialog = new DialogDiscreteVarAdd();
                    dialog->updateParentList(c->getAnalogVarsComments());
                    dialog->setName(var->getComment());
                    dialog->setPriority(var->getDPrior());
                    dialog->setParent(var->getParentName());
                    dialog->setBitNum(var->getBitNum());
                    int ret = dialog->exec();
                    if(ret==QDialog::Accepted) {
                        var->setComment(dialog->getName());
                        var->setDPrior((DiscreteVar::displPriority)dialog->getPriority());
                        var->setParentName(dialog->getParent());
                        var->setBitNum(dialog->getBitNum());
                        contextItem->setText(0,var->getComment());
                    }
                    delete dialog;
                }
            }

        }
    }
}

void MainWindow::deleteDiscreteVar()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            DiscreteVar *var = (DiscreteVar*)ptr;
            QString vComment = var->getComment();
            QTreeWidgetItem *parItem = contextItem->parent();
            if(parItem!=nullptr) {
                if(treeLink.keys().contains(parItem)) {
                    void *parPtr = treeLink.value(parItem);
                    Controller *c = (Controller*)parPtr;
                    c->deleteDiscrVar(vComment);
                    treeLink.remove(contextItem);
                    delete contextItem;
                }
            }
        }
    }
}

void MainWindow::editMessageVar()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            QTreeWidgetItem *parItem = contextItem->parent();
            if(parItem!=nullptr) {
                if(treeLink.keys().contains(parItem)) {
                    void *parPtr = treeLink.value(parItem);
                    Controller *c = (Controller*)parPtr;
                    MessageVar *var = (MessageVar*)ptr;
                    DialogMessageVarAdd *dialog = new DialogMessageVarAdd();
                    dialog->updateParentList(c->getAnalogVarsComments());
                    dialog->setMessage(var->getMessage());
                    dialog->setType(var->getType());
                    dialog->setParent(var->getParentName());
                    dialog->setBitNum(var->getBitNum());
                    int ret = dialog->exec();
                    if(ret==QDialog::Accepted) {
                        var->setMessage(dialog->getMessage());
                        var->setType((MessageVar::mesType)dialog->getType());
                        var->setParentName(dialog->getParent());
                        var->setBitNum(dialog->getBitNum());
                        contextItem->setText(0,var->getMessage());
                    }
                    delete dialog;
                }
            }

        }
    }
}

void MainWindow::deleteMessageVar()
{
    if(contextItem!=nullptr) {
        if(treeLink.keys().contains(contextItem)) {
            void *ptr = treeLink.value(contextItem);
            MessageVar *var = (MessageVar*)ptr;
            QString vMessage = var->getMessage();
            QTreeWidgetItem *parItem = contextItem->parent();
            if(parItem!=nullptr) {
                if(treeLink.keys().contains(parItem)) {
                    void *parPtr = treeLink.value(parItem);
                    Controller *c = (Controller*)parPtr;
                    c->deleteMessageVar(vMessage);
                    treeLink.remove(contextItem);
                    delete contextItem;
                }
            }
        }
    }
}
