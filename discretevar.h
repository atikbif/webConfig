#ifndef DISCRETEVAR_H
#define DISCRETEVAR_H

#include <QString>

class DiscreteVar
{
public:
    enum displPriority {DONTDISPLAY,LOW,NORMAL,HIGH};
private:
    QString name;
    QString comment;
    displPriority dPrior;
    QString parentName;
    int bitNum;
public:
    DiscreteVar();
    QString getName() const;
    void setName(const QString &value);
    displPriority getDPrior() const;
    void setDPrior(const displPriority &value);
    QString getParentName() const;
    void setParentName(const QString &value);
    int getBitNum() const;
    void setBitNum(int value);
    QString getComment() const;
    void setComment(const QString &value);
};

#endif // DISCRETEVAR_H
