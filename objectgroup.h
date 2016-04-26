#ifndef OBJECTGROUP_H
#define OBJECTGROUP_H

#include "dispobject.h"
#include <QString>
#include <QSharedPointer>
#include <QVector>

class ObjectGroup
{
    QString name;
    QVector<QSharedPointer<DispObject> > objects;
public:
    ObjectGroup();
    int getObjCount() const {return objects.count();}
    QSharedPointer<DispObject> getObject(int num);
    QSharedPointer<DispObject> getObject(QString obName);
    bool addObject(const DispObject &ob);
    void deleteObject(const QString &obName);
    void deleteObject(int num);
    QString getName() const;
    void setName(const QString &value);
};

#endif // OBJECTGROUP_H
