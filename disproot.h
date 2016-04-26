#ifndef DISPROOT_H
#define DISPROOT_H

#include "objectgroup.h"
#include <QVector>
#include <QSharedPointer>

class DispRoot
{
    QVector<QSharedPointer<ObjectGroup> > groups;
public:
    DispRoot();
    int getGroopCount() const {return groups.count();}
    QSharedPointer<ObjectGroup> getGroup(int num);
    QSharedPointer<ObjectGroup> getGroup(QString name);
    bool addGroup(const ObjectGroup &gr);
    void deleteGroup(const QString &grName);
    void deleteGroup(int num);
};

#endif // DISPROOT_H
