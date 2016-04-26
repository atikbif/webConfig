#include "controller.h"

QString Controller::getName() const
{
    return name;
}

void Controller::setName(const QString &value)
{
    name = value;
}

int Controller::getPort() const
{
    return port;
}

void Controller::setPort(int value)
{
    port = value;
}

QString Controller::getIp() const
{
    return ip;
}

void Controller::setIp(const QString &value)
{
    ip = value;
}

Controller::Controller():name(""),port(0),ip("")
{

}

bool Controller::addAnVar(const AnalogVar &var)
{
    foreach (QSharedPointer<AnalogVar> v, anVars) {
        if(v->getComment()==var.getComment()) return false;
    }
    AnalogVar *v = new AnalogVar(var);
    QSharedPointer<AnalogVar> ptr = QSharedPointer<AnalogVar>(v);
    ptr->setName("ADC" + QString::number(getAnVarCount()+1));
    anVars.append(ptr);
    return true;
}

bool Controller::addDiscreteVar(const DiscreteVar &var)
{
    foreach (QSharedPointer<DiscreteVar> v, dVars) {
        if(v->getComment()==var.getComment()) return false;
    }
    DiscreteVar *v = new DiscreteVar(var);
    QSharedPointer<DiscreteVar> ptr = QSharedPointer<DiscreteVar>(v);
    ptr->setName("BIT" + QString::number(getDiscrVarCount()+1));
    dVars.append(ptr);
    return true;
}

bool Controller::addMessageVar(const MessageVar &var)
{
    MessageVar *v = new MessageVar(var);
    QSharedPointer<MessageVar> ptr = QSharedPointer<MessageVar>(v);
    ptr->setName("M" + QString::number(getMessageVarCount()+1));
    mVars.append(ptr);
    return true;
}

QSharedPointer<AnalogVar> Controller::getAnalogVar(int num)
{
    if((num>=0)&&(num<getAnVarCount())) {
        return anVars.at(num);
    }
    return QSharedPointer<AnalogVar>(new AnalogVar());

}

QSharedPointer<AnalogVar> Controller::getAnalogVar(QString comment)
{
    for(int i=0;i<anVars.count();++i) {
        if(anVars.at(i)->getComment()==comment) return anVars.at(i);
    }
    return QSharedPointer<AnalogVar>(new AnalogVar());
}

QSharedPointer<DiscreteVar> Controller::getDiscreteVar(int num)
{
    if((num>=0)&&(num<getDiscrVarCount())) {
        return dVars.at(num);
    }
    return QSharedPointer<DiscreteVar>(new DiscreteVar());
}

QSharedPointer<DiscreteVar> Controller::getDiscreteVar(QString comment)
{
    for(int i=0;i<dVars.count();++i) {
        if(dVars.at(i)->getComment()==comment) return dVars.at(i);
    }
    return QSharedPointer<DiscreteVar>(new DiscreteVar());
}

QSharedPointer<MessageVar> Controller::getMessageVar(int num)
{
    if((num>=0)&&(num<getMessageVarCount())) {
        return mVars.at(num);
    }
    return QSharedPointer<MessageVar>(new MessageVar());
}

QSharedPointer<MessageVar> Controller::getMessageVar(QString message)
{
    for(int i=0;i<mVars.count();++i) {
        if(mVars.at(i)->getMessage()==message) return mVars.at(i);
    }
    return QSharedPointer<MessageVar>(new MessageVar());
}

QStringList Controller::getAnalogVarsComments() const
{
    QStringList res;
    foreach (QSharedPointer<AnalogVar> v, anVars) {
        res.append(v->getComment());
    }
    return res;
}

QString Controller::getAnNameByComment(const QString &comment) const
{
    foreach (QSharedPointer<AnalogVar> v, anVars) {
        if(v->getComment()==comment) return v->getName();
    }
    return QString();
}

void Controller::deleteAnVar(const QString &anVarComment)
{
    for(int i=0;i<anVars.count();++i) {
        QSharedPointer<AnalogVar> v = anVars.at(i);
        if(v->getComment()==anVarComment) {
            QString vName = v->getName();
            anVars.remove(i);
            for(int j=0;j<dVars.count();++j) {
                QSharedPointer<DiscreteVar> dv = dVars.at(j);
                if(dv->getParentName()==vName) dv->setParentName("");
            }
            for(int j=0;j<mVars.count();++j) {
                QSharedPointer<MessageVar> mv = mVars.at(j);
                if(mv->getParentName()==vName) mv->setParentName("");
            }
            break;
        }
    }
}

void Controller::deleteAnVar(int num)
{
    if((num>=0)&&(num<anVars.count())) {
        QString comment = anVars.at(num)->getComment();
        deleteAnVar(comment);
    }
}

void Controller::deleteDiscrVar(const QString &dVarComment)
{
    for(int i=0;i<dVars.count();++i) {
        QSharedPointer<DiscreteVar> v = dVars.at(i);
        if(v->getComment()==dVarComment) {
            dVars.remove(i);
            break;
        }
    }
}

void Controller::deleteDiscrVar(int num)
{
    if((num>=0)&&(num<dVars.count())) {
        QString comment = dVars.at(num)->getComment();
        deleteDiscrVar(comment);
    }
}

void Controller::deleteMessageVar(const QString &message)
{
    for(int i=0;i<mVars.count();++i) {
        QSharedPointer<MessageVar> v = mVars.at(i);
        if(v->getMessage()==message) {
            mVars.remove(i);
            break;
        }
    }
}

void Controller::deleteMessageVar(int num)
{
    if((num>=0)&&(num<mVars.count())) {
        QString message = mVars.at(num)->getMessage();
        deleteMessageVar(message);
    }
}
