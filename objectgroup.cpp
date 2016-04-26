#include "objectgroup.h"

QString ObjectGroup::getName() const
{
    return name;
}

void ObjectGroup::setName(const QString &value)
{
    name = value;
}

ObjectGroup::ObjectGroup():name("")
{

}

QSharedPointer<DispObject> ObjectGroup::getObject(int num)
{
    if((num>=0)&&(num<getObjCount())) {
        return objects.at(num);
    }
    DispObject *ptr = new DispObject();
    return QSharedPointer<DispObject>(ptr);
}

QSharedPointer<DispObject> ObjectGroup::getObject(QString obName)
{
    for(int i=0;i<objects.count();++i) {
        if(objects.at(i)->getName()==obName) return objects.at(i);
    }
    DispObject *ptr = new DispObject();
    return QSharedPointer<DispObject>(ptr);
}

bool ObjectGroup::addObject(const DispObject &ob)
{
    foreach (QSharedPointer<DispObject> obi, objects) {
        if(obi->getName()==ob.getName()) return false;
    }
    QSharedPointer<DispObject> ptr = QSharedPointer<DispObject>(new DispObject(ob));
    objects.append(ptr);
    return true;
}

void ObjectGroup::deleteObject(const QString &obName)
{
    for(int i=0;i<objects.count();i++) {
        QSharedPointer<DispObject> ptr = objects.at(i);
        if(ptr->getName()==obName) {
            objects.remove(i);
            break;
        }
    }
}

void ObjectGroup::deleteObject(int num)
{
    if((num>=0)&&(num<objects.count())) {
        QString obName = objects.at(num)->getName();
        deleteObject(obName);
    }
}
