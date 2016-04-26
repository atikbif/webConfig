#include "discretevar.h"

QString DiscreteVar::getName() const
{
    return name;
}

void DiscreteVar::setName(const QString &value)
{
    name = value;
}

DiscreteVar::displPriority DiscreteVar::getDPrior() const
{
    return dPrior;
}

void DiscreteVar::setDPrior(const displPriority &value)
{
    dPrior = value;
}

QString DiscreteVar::getParentName() const
{
    return parentName;
}

void DiscreteVar::setParentName(const QString &value)
{
    parentName = value;
}

int DiscreteVar::getBitNum() const
{
    return bitNum;
}

void DiscreteVar::setBitNum(int value)
{
    if((value>=0)&&(value<16)) bitNum = value;
}

QString DiscreteVar::getComment() const
{
    return comment;
}

void DiscreteVar::setComment(const QString &value)
{
    comment = value;
}

DiscreteVar::DiscreteVar():name(""),comment(""),dPrior(NORMAL),parentName(""),bitNum(0)
{

}
