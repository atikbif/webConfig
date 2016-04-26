#include "disproot.h"

DispRoot::DispRoot()
{

}

QSharedPointer<ObjectGroup> DispRoot::getGroup(int num)
{
    if((num>=0)&&(num<getGroopCount())) {
        return groups.at(num);
    }
    return QSharedPointer<ObjectGroup>(new ObjectGroup());
}

QSharedPointer<ObjectGroup> DispRoot::getGroup(QString name)
{
    for(int i=0;i<groups.count();++i) {
        if(groups.at(i)->getName()==name) return groups.at(i);
    }
    return QSharedPointer<ObjectGroup>(new ObjectGroup());
}

bool DispRoot::addGroup(const ObjectGroup &gr)
{
    foreach (QSharedPointer<ObjectGroup> obGr, groups) {
        if(obGr->getName()==gr.getName()) return false;
    }
    QSharedPointer<ObjectGroup> ptr = QSharedPointer<ObjectGroup>(new ObjectGroup(gr));
    groups.append(ptr);
    return true;
}

void DispRoot::deleteGroup(const QString &grName)
{
    for(int i=0;i<groups.count();++i) {
        QSharedPointer<ObjectGroup> gr = groups.at(i);
        if(gr->getName()==grName) {
            groups.remove(i);
            break;
        }
    }
}

void DispRoot::deleteGroup(int num)
{
    if((num>=0)&&(num<groups.count())) {
        QString grName = groups.at(num)->getName();
        deleteGroup(grName);
    }
}
