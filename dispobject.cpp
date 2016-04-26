#include "dispobject.h"

QString DispObject::getName() const
{
    return name;
}

void DispObject::setName(const QString &value)
{
    name = value;
}

QString DispObject::getComment() const
{
    return comment;
}

void DispObject::setComment(const QString &value)
{
    comment = value;
}

int DispObject::getPeriod() const
{
    return period;
}

void DispObject::setPeriod(int value)
{
    period = value;
}

int DispObject::getWaitTime() const
{
    return waitTime;
}

void DispObject::setWaitTime(int value)
{
    waitTime = value;
}

bool DispObject::addController(const Controller &c)
{
    QSharedPointer<Controller> ptr = QSharedPointer<Controller>(new Controller(c));
    foreach (QSharedPointer<Controller> cPtr, plcList) {
        if(cPtr->getName() == ptr->getName()) return false;
    }
    plcList.append(ptr);
    return true;
}

void DispObject::deleteController(const QString &cName)
{
    for(int i=0;i<plcList.count();++i) {
        QSharedPointer<Controller> ptr = plcList.at(i);
        if(ptr->getName()==cName) {
            plcList.remove(i);
            break;
        }
    }
}

void DispObject::deleteController(int num)
{
    if((num>=0)&&(num<plcList.count())) {
        QString cName = plcList.at(num)->getName();
        deleteController(cName);
    }
}

QSharedPointer<Controller> DispObject::getController(int num)
{
    if((num>=0)&&(num<plcList.count())) {
        return plcList.at(num);
    }
    return QSharedPointer<Controller>(new Controller());
}

QSharedPointer<Controller> DispObject::getController(const QString &cName)
{
    for(int i=0;i<plcList.count();++i) {
        if(plcList.at(i)->getName()==cName) return plcList.at(i);
    }
    return QSharedPointer<Controller>(new Controller());
}

DispObject::DispObject():name(""),comment(""),period(10),waitTime(8000)
{

}
