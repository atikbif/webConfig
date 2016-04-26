#ifndef DISPOBJECT_H
#define DISPOBJECT_H

#include "controller.h"
#include <QString>
#include <QVector>
#include <QSharedPointer>

class DispObject
{
    QString name;
    QString comment;
    int period;
    int waitTime;
    QVector<QSharedPointer<Controller> > plcList;
public:
    DispObject();
    QString getName() const;
    void setName(const QString &value);
    QString getComment() const;
    void setComment(const QString &value);
    int getPeriod() const;
    void setPeriod(int value);
    int getWaitTime() const;
    void setWaitTime(int value);
    bool addController(const Controller &c);
    void deleteController(const QString &cName);
    void deleteController(int num);
    int getControllerCount() const {return plcList.count();}
    QSharedPointer<Controller> getController(int num);
    QSharedPointer<Controller> getController(const QString &cName);
};

#endif // DISPOBJECT_H
