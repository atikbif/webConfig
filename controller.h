#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "analogvar.h"
#include "discretevar.h"
#include "messagevar.h"

#include <QString>
#include <QVector>
#include <QSharedPointer>

class Controller
{
    QString name;
    int port;
    QString ip;
    QVector<QSharedPointer<AnalogVar> > anVars;
    QVector<QSharedPointer<DiscreteVar> > dVars;
    QVector<QSharedPointer<MessageVar> > mVars;
public:
    Controller();
    int getAnVarCount() const {return anVars.count();}
    int getDiscrVarCount() const {return dVars.count();}
    int getMessageVarCount() const {return mVars.count();}
    bool addAnVar(const AnalogVar &var);
    bool addDiscreteVar(const DiscreteVar &var);
    bool addMessageVar(const MessageVar &var);
    QSharedPointer<AnalogVar> getAnalogVar(int num);
    QSharedPointer<AnalogVar> getAnalogVar(QString comment);
    QSharedPointer<DiscreteVar> getDiscreteVar(int num);
    QSharedPointer<DiscreteVar> getDiscreteVar(QString comment);
    QSharedPointer<MessageVar> getMessageVar(int num);
    QSharedPointer<MessageVar> getMessageVar(QString message);
    QStringList getAnalogVarsComments() const;
    QString getAnNameByComment(const QString &comment) const;
    void deleteAnVar(const QString &anVarComment);
    void deleteAnVar(int num);
    void deleteDiscrVar(const QString &dVarComment);
    void deleteDiscrVar(int num);
    void deleteMessageVar(const QString &message);
    void deleteMessageVar(int num);
    QString getName() const;
    void setName(const QString &value);
    int getPort() const;
    void setPort(int value);
    QString getIp() const;
    void setIp(const QString &value);
};

#endif // CONTROLLER_H
