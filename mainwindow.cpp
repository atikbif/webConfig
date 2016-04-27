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
#include <QAction>
#include <QFile>
#include <QDir>
#include <QXmlStreamWriter>
#include <QDomDocument>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), contextItem(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->treeWidget->setSortingEnabled(true);
    QAction *actionSave = new QAction("сохранить",this);
    connect(actionSave,SIGNAL(triggered(bool)),this,SLOT(saveProject()));
    ui->mainToolBar->addAction(actionSave);
    QAction *actionClear = new QAction("очистить",this);
    connect(actionClear,SIGNAL(triggered(bool)),this,SLOT(clearProject()));
    ui->mainToolBar->addAction(actionClear);

    // QTreeWidget::item:selected "
    // "{ border: 1px solid gainsboro; border-left: none; border-top: none;} "

    QString style =
                    "QTreeWidget{"
                    "color: #FFFFFF;"
                    "background: #535353;"
                    "font-size: 9pt;}"
                    "QTreeWidget::item:selected {"
                    "color: #FFFFFF;"
                    "background-color: #151515;}"
                    "QTreeWidget::item:hover{background: rgb(155, 55, 55);}";
    ui->treeWidget->setStyleSheet(style);

    style = "QPushButton {"
        "background-color:rgb(155, 155, 55);}"
        "QPushButton:hover {background-color: rgb(155, 55, 55);color: #FFFFFF;}";
    ui->pushButton->setStyleSheet(style);

    loadProject();
    ui->treeWidget->expandAll();
    ui->treeWidget->resizeColumnToContents(0);
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
            addGroup(group);
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

QTreeWidgetItem *MainWindow::addController(Controller &c, QTreeWidgetItem *obItem)
{
    void *ptr = treeLink.value(obItem);
    DispObject *ob = (DispObject*)ptr;
    if((!c.getName().isEmpty())&&(ob->addController(c))) {
        QSharedPointer<Controller> cPtr = ob->getController(c.getName());
        if(!cPtr->getName().isEmpty()) {
            QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<c.getName()<<"контроллер",2);
            obItem->addChild(item);
            treeLink.insert(item,(void*)cPtr.data());
            return item;
        }
    }
    return nullptr;
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

QTreeWidgetItem* MainWindow::addObject(DispObject &ob, QTreeWidgetItem *grItem)
{
    void *ptr = treeLink.value(grItem);
    ObjectGroup *gr = (ObjectGroup*)ptr;
    if((!ob.getName().isEmpty())&&(gr->addObject(ob))) {
        QSharedPointer<DispObject> obPtr = gr->getObject(ob.getName());
        if(!obPtr->getName().isEmpty()) {
            QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<ob.getName()<<"объект",1);
            grItem->addChild(item);
            treeLink.insert(item,(void*)obPtr.data());
            return item;
        }
    }
    return nullptr;
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

QTreeWidgetItem *MainWindow::addAnalogVar(AnalogVar &var, QTreeWidgetItem *cItem)
{
    void *ptr = treeLink.value(cItem);
    Controller *c = (Controller*)ptr;
    if((!var.getComment().isEmpty())&&(c->addAnVar(var))) {
        QSharedPointer<AnalogVar> vPtr = c->getAnalogVar(var.getComment());
        if(!vPtr->getComment().isEmpty()) {
            QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<var.getComment()<<"аналоговая переменная",3);
            cItem->addChild(item);
            treeLink.insert(item,(void*)vPtr.data());
            return item;
        }
    }
    return nullptr;
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

QTreeWidgetItem *MainWindow::addDiscreteVar(DiscreteVar &var, QTreeWidgetItem *cItem)
{
    void *ptr = treeLink.value(cItem);
    Controller *c = (Controller*)ptr;
    if((!var.getComment().isEmpty())&&(c->addDiscreteVar(var))) {
        QSharedPointer<DiscreteVar> vPtr = c->getDiscreteVar(var.getComment());
        if(!vPtr->getComment().isEmpty()) {
            QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<var.getComment()<<"дискретная переменная",4);
            cItem->addChild(item);
            treeLink.insert(item,(void*)vPtr.data());
            return item;
        }
    }
    return nullptr;
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

QTreeWidgetItem *MainWindow::addMessage(MessageVar &var, QTreeWidgetItem *cItem)
{
    void *ptr = treeLink.value(cItem);
    Controller *c = (Controller*)ptr;
    if((!var.getMessage().isEmpty())&&(c->addMessageVar(var))) {
        QSharedPointer<MessageVar> vPtr = c->getMessageVar(var.getMessage());
        if(!vPtr->getMessage().isEmpty()) {
            QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<var.getMessage()<<"сообщение",5);
            cItem->addChild(item);
            treeLink.insert(item,(void*)vPtr.data());
            return item;
        }
    }
    return nullptr;
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

void MainWindow::saveProject()
{
    QString confDirPath = QApplication::applicationDirPath() + "/config";
    QDir confDir(confDirPath);
    if(confDir.exists()) {
        confDir.removeRecursively();
    }
    confDir.mkpath(".");
    QXmlStreamWriter xmlWriter;

    xmlWriter.setAutoFormatting(true);
    QFile file(confDirPath+"/config.xml");

    if (!file.open(QIODevice::WriteOnly)) {return;}
    else
    {
        xmlWriter.setDevice(&file);

        /* Writes a document start with the XML version number. */
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("webConf");

        int obNum = 1;

        for(int i=0;i<root.getGroopCount();i++) {
            QSharedPointer<ObjectGroup> gr = root.getGroup(i);
            xmlWriter.writeStartElement("group");
            xmlWriter.writeAttribute("name", gr->getName());
            for(int j=0;j<gr->getObjCount();j++) {
                xmlWriter.writeStartElement("object");
                xmlWriter.writeAttribute("xmlFile","ob_"+QString::number(obNum)+"/object.xml");
                xmlWriter.writeEndElement();
                saveObjectXML(confDirPath+"/ob_"+QString::number(obNum),gr->getObject(j));
                obNum++;
            }
            xmlWriter.writeEndElement();
        }

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
}

void MainWindow::loadProject()
{
    QString confDirPath = QApplication::applicationDirPath() + "/config";
    QDir confDir(confDirPath);
    if(confDir.exists()) {
        QFile file(confDirPath+"/config.xml");
        if(file.exists()) {
            QDomDocument doc("config");
            if (!doc.setContent(&file)) {
                return;
            }
            if(doc.elementsByTagName("webConf").count()!=1) return;
            QDomNodeList groups = doc.elementsByTagName("group");
            for(int i=0;i<groups.count();i++) {
                QDomNode n = groups.at(i);
                QDomElement e = n.toElement();
                if(!e.isNull()) {
                    QString grName = e.attribute("name");
                    ObjectGroup gr;
                    gr.setName(grName);
                    QTreeWidgetItem *grItem = addGroup(gr);
                    if(grItem!=nullptr) {
                        QDomNodeList childs = n.childNodes();
                        for(int j=0;j<childs.count();j++) {
                            QDomNode n = childs.at(j);
                            QDomElement e = n.toElement();
                            if(e.nodeName()=="object") {
                                QString xmlFilePath = confDirPath + "/" + e.attribute("xmlFile");
                                loadObject(xmlFilePath, grItem);
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::clearProject()
{
    treeLink.clear();
    contextItem = nullptr;
    ui->treeWidget->clear();
    for(int i=0;i<root.getGroopCount();i++) {
        root.deleteGroup(i);
    }
}

QTreeWidgetItem *MainWindow::loadController(const QString &fName, QTreeWidgetItem *obItem)
{
    QFile file(fName);
    if(file.exists()) {
        QDomDocument doc("controller");
        if (!doc.setContent(&file)) {
            return nullptr;
        }
        if(doc.elementsByTagName("contrConf").count()!=1) return nullptr;
        Controller c;
        QDomNodeList names = doc.elementsByTagName("definition");
        if(names.count()) c.setName(names.at(0).toElement().text());
        QDomNodeList ips = doc.elementsByTagName("ip");
        if(ips.count()) c.setIp(ips.at(0).toElement().text());
        QDomNodeList ports = doc.elementsByTagName("port");
        if(ports.count()) c.setPort(ports.at(0).toElement().text().toInt());
        QTreeWidgetItem *cItem = addController(c,obItem);
        if(cItem!=nullptr) {
            QDomNodeList adc = doc.elementsByTagName("analog");
            for(int i=0;i<adc.count();i++) {
                QDomElement e = adc.at(i).toElement();
                if(!e.isNull()) {
                    AnalogVar var;
                    QDomNodeList childs = e.childNodes();
                    for(int j=0;j<childs.count();j++) {
                        QDomElement e = childs.at(j).toElement();
                        if(!e.isNull()) {
                            if(e.nodeName()=="name") var.setName(e.text());
                            if(e.nodeName()=="comment") var.setComment(e.text());
                            if(e.nodeName()=="priority") {
                                QString pr = e.text();
                                int prNum = 0;
                                if(pr=="none") prNum = 0;
                                else if(pr=="low") prNum = 1;
                                else if(pr=="normal") prNum = 2;
                                else if(pr=="high") prNum = 3;
                                var.setDPrior((AnalogVar::displPriority)prNum);
                            }
                            if(e.nodeName()=="address") var.setAddress(e.text().toInt());
                            if(e.nodeName()=="min") var.setScaleMin(e.text().toInt());
                            if(e.nodeName()=="max") var.setScaleMax(e.text().toInt());
                            if(e.nodeName()=="minLimit") var.setNormMin(e.text().toInt());
                            if(e.nodeName()=="maxLimit") var.setNormMax(e.text().toInt());
                            if(e.nodeName()=="coeff") var.setCoeff(e.text().toFloat());
                        }
                    }
                    addAnalogVar(var,cItem);
                }
            }
            void *ptr = treeLink.value(cItem);
            Controller *cUpd = (Controller*)ptr;
            c = *cUpd;

            QDomNodeList din = doc.elementsByTagName("discrete");
            for(int i=0;i<din.count();i++) {
                QDomElement e = din.at(i).toElement();
                if(!e.isNull()) {
                    DiscreteVar var;
                    QDomNodeList childs = e.childNodes();
                    for(int j=0;j<childs.count();j++) {
                        QDomElement e = childs.at(j).toElement();
                        if(!e.isNull()) {
                            if(e.nodeName()=="name") var.setName(e.text());
                            if(e.nodeName()=="comment") var.setComment(e.text());
                            if(e.nodeName()=="priority") {
                                QString pr = e.text();
                                int prNum = 0;
                                if(pr=="none") prNum = 0;
                                else if(pr=="low") prNum = 1;
                                else if(pr=="normal") prNum = 2;
                                else if(pr=="high") prNum = 3;
                                var.setDPrior((DiscreteVar::displPriority)prNum);
                            }
                            if(e.nodeName()=="parent") {

                                for(int k=0;k<c.getAnVarCount();k++) {
                                    QSharedPointer<AnalogVar> av = c.getAnalogVar(k);
                                    if(av->getName()==e.text()) {
                                        var.setParentName(av->getComment());
                                        break;
                                    }
                                }
                            }
                            if(e.nodeName()=="bit") var.setBitNum(e.text().toInt());
                        }
                    }
                    addDiscreteVar(var,cItem);
                }
            }

            QDomNodeList m = doc.elementsByTagName("message");
            for(int i=0;i<m.count();i++) {
                QDomElement e = m.at(i).toElement();
                if(!e.isNull()) {
                    MessageVar var;
                    QDomNodeList childs = e.childNodes();
                    for(int j=0;j<childs.count();j++) {
                        QDomElement e = childs.at(j).toElement();
                        if(!e.isNull()) {
                            if(e.nodeName()=="name") var.setName(e.text());
                            if(e.nodeName()=="text") var.setMessage(e.text());
                            if(e.nodeName()=="type") {
                                QString pr = e.text();
                                int prNum = 0;
                                if(pr=="info") prNum = 0;
                                else if(pr=="warning") prNum = 1;
                                else if(pr=="alarm") prNum = 2;
                                var.setType((MessageVar::mesType)prNum);
                            }
                            if(e.nodeName()=="parent") {
                                for(int k=0;k<c.getAnVarCount();k++) {
                                    QSharedPointer<AnalogVar> av = c.getAnalogVar(k);
                                    if(av->getName()==e.text()) {
                                        var.setParentName(av->getComment());
                                        break;
                                    }
                                }
                            }
                            if(e.nodeName()=="bit") var.setBitNum(e.text().toInt());
                        }
                    }
                    addMessage(var,cItem);
                }
            }
            return cItem;
        }
    }
    return nullptr;
}

QTreeWidgetItem *MainWindow::loadObject(const QString &fName, QTreeWidgetItem *grItem)
{
    QFile file(fName);
    if(file.exists()) {
        QDomDocument doc("object");
        if (!doc.setContent(&file)) {
            return nullptr;
        }
        if(doc.elementsByTagName("objConf").count()!=1) return nullptr;
        DispObject ob;
        QDomNodeList names = doc.elementsByTagName("name");
        if(names.count()) ob.setName(names.at(0).toElement().text());
        QDomNodeList comments = doc.elementsByTagName("comment");
        if(comments.count()) ob.setComment(comments.at(0).toElement().text());
        QDomNodeList periods = doc.elementsByTagName("period");
        if(periods.count()) ob.setPeriod(periods.at(0).toElement().text().toInt());
        QDomNodeList waits = doc.elementsByTagName("wait");
        if(waits.count()) ob.setWaitTime(waits.at(0).toElement().text().toInt());
        QTreeWidgetItem *obItem = addObject(ob, grItem);
        if(obItem != nullptr) {
            QDomNodeList plcList = doc.elementsByTagName("controller");
            for(int i=0;i<plcList.count();i++) {
                QDomElement e = plcList.at(i).toElement();
                if(!e.isNull()) {
                    QFileInfo fInfo(file);
                    QString fName = fInfo.absoluteDir().path() + "/" + e.attribute("file");
                    loadController(fName, obItem);
                }
            }
            return obItem;
        }
    }
    return nullptr;
}

QTreeWidgetItem* MainWindow::addGroup(const ObjectGroup &gr)
{
    if(root.addGroup(gr)) {
        QSharedPointer<ObjectGroup> ptr = root.getGroup(gr.getName());
        if(!ptr->getName().isEmpty()) {
            QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << gr.getName() << "группа объектов",0);
            void *vPtr = (void*)ptr.data();
            treeLink.insert(item,vPtr);
            ui->treeWidget->addTopLevelItem(item);
            return item;
        }
    }
    return nullptr;
}

void MainWindow::saveObjectXML(const QString &dirPath, QSharedPointer<DispObject> ob)
{
    QDir obDir(dirPath);
    if(!obDir.exists()) obDir.mkpath(".");
    QXmlStreamWriter xmlWriter;
    xmlWriter.setAutoFormatting(true);
    QFile file(dirPath + "/object.xml");

    if (!file.open(QIODevice::WriteOnly)) {return;}
    else
    {
        xmlWriter.setDevice(&file);

        /* Writes a document start with the XML version number. */
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("objConf");
            xmlWriter.writeStartElement("name");
            xmlWriter.writeCharacters(ob->getName());
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("comment");
            xmlWriter.writeCharacters(ob->getComment());
            xmlWriter.writeEndElement();

            int obNum = 1;
            QRegExp e("ob_(\\d+)");
            if(e.indexIn(dirPath)!=-1) {
                obNum = e.cap(1).toInt();
            }
            xmlWriter.writeStartElement("pageName");
            xmlWriter.writeCharacters("ob"+QString::number(obNum)+".html");
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("period");
            xmlWriter.writeCharacters(QString::number(ob->getPeriod()));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("wait");
            xmlWriter.writeCharacters(QString::number(ob->getWaitTime()));
            xmlWriter.writeEndElement();

            for(int i=0;i<ob->getControllerCount();i++) {
                QSharedPointer<Controller> c = ob->getController(i);
                QString fName = "plc_"+QString::number(i+1)+".xml";
                xmlWriter.writeStartElement("controller");
                xmlWriter.writeAttribute("file",fName);
                xmlWriter.writeEndElement();
                saveControllerXML(dirPath + "/" + fName, c);
            }

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();

    }
}

void MainWindow::saveControllerXML(const QString &fName, QSharedPointer<Controller> c)
{
    QXmlStreamWriter xmlWriter;
    xmlWriter.setAutoFormatting(true);
    QFile file(fName);

    if (!file.open(QIODevice::WriteOnly)) {return;}
    else
    {
        xmlWriter.setDevice(&file);

        /* Writes a document start with the XML version number. */
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("contrConf");

        xmlWriter.writeStartElement("definition");
        xmlWriter.writeCharacters(c->getName());
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("ip");
        xmlWriter.writeCharacters(c->getIp());
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("port");
        xmlWriter.writeCharacters(QString::number(c->getPort()));
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement("vars");
        for(int i=0;i<c->getAnVarCount();i++) {
            QSharedPointer<AnalogVar> var = c->getAnalogVar(i);
            xmlWriter.writeStartElement("analog");
                xmlWriter.writeStartElement("name");
                xmlWriter.writeCharacters("ADC"+QString::number(i+1));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("comment");
                xmlWriter.writeCharacters(var->getComment());
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("priority");
                switch(var->getDPrior()) {
                    case 0:xmlWriter.writeCharacters("none");break;
                    case 1:xmlWriter.writeCharacters("low");break;
                    case 2:xmlWriter.writeCharacters("normal");break;
                    case 3:xmlWriter.writeCharacters("high");break;
                }
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("address");
                xmlWriter.writeCharacters(QString::number(var->getAddress()));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("min");
                xmlWriter.writeCharacters(QString::number(var->getScaleMin()));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("max");
                xmlWriter.writeCharacters(QString::number(var->getScaleMax()));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("minLimit");
                xmlWriter.writeCharacters(QString::number(var->getNormMin()));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("maxLimit");
                xmlWriter.writeCharacters(QString::number(var->getNormMax()));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("coeff");
                xmlWriter.writeCharacters(QString::number(var->getCoeff()));
                xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
        }

        for(int i=0;i<c->getDiscrVarCount();i++) {
            QSharedPointer<DiscreteVar> var = c->getDiscreteVar(i);
            xmlWriter.writeStartElement("discrete");
                xmlWriter.writeStartElement("name");
                xmlWriter.writeCharacters("BIT"+QString::number(i+1));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("comment");
                xmlWriter.writeCharacters(var->getComment());
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("priority");
                switch(var->getDPrior()) {
                    case 0:xmlWriter.writeCharacters("none");break;
                    case 1:xmlWriter.writeCharacters("low");break;
                    case 2:xmlWriter.writeCharacters("normal");break;
                    case 3:xmlWriter.writeCharacters("high");break;
                }
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("parent");
                QString parName;
                for(int j=0;i<c->getAnVarCount();j++) {
                    if(c->getAnalogVar(j)->getComment()==var->getParentName()) {
                        parName = "ADC" + QString::number(j+1);
                        break;
                    }
                }
                xmlWriter.writeCharacters(parName);
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("bit");
                xmlWriter.writeCharacters(QString::number(var->getBitNum()));
                xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
        }

        for(int i=0;i<c->getMessageVarCount();i++) {
            QSharedPointer<MessageVar> var = c->getMessageVar(i);
            xmlWriter.writeStartElement("message");
                xmlWriter.writeStartElement("name");
                xmlWriter.writeCharacters("M"+QString::number(i+1));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("text");
                xmlWriter.writeCharacters(var->getMessage());
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("type");
                switch(var->getType()) {
                    case 0:xmlWriter.writeCharacters("info");break;
                    case 1:xmlWriter.writeCharacters("warning");break;
                    case 2:xmlWriter.writeCharacters("alarm");break;
                }
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("parent");
                QString parName;
                for(int j=0;i<c->getAnVarCount();j++) {
                    if(c->getAnalogVar(j)->getComment()==var->getParentName()) {
                        parName = "ADC" + QString::number(j+1);
                        break;
                    }
                }
                xmlWriter.writeCharacters(parName);
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("bit");
                xmlWriter.writeCharacters(QString::number(var->getBitNum()));
                xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
        }

        xmlWriter.writeEndElement();

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
}
