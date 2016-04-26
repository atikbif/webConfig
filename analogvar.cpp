#include "analogvar.h"

QString AnalogVar::getName() const
{
    return name;
}

void AnalogVar::setName(const QString &value)
{
    name = value;
}

QString AnalogVar::getComment() const
{
    return comment;
}

void AnalogVar::setComment(const QString &value)
{
    comment = value;
}

AnalogVar::displPriority AnalogVar::getDPrior() const
{
    return dPrior;
}

void AnalogVar::setDPrior(const displPriority &value)
{
    dPrior = value;
}

int AnalogVar::getAddress() const
{
    return address;
}

void AnalogVar::setAddress(int value)
{
    address = value;
}

int AnalogVar::getScaleMin() const
{
    return scaleMin;
}

void AnalogVar::setScaleMin(int value)
{
    scaleMin = value;
}

int AnalogVar::getScaleMax() const
{
    return scaleMax;
}

void AnalogVar::setScaleMax(int value)
{
    scaleMax = value;
}

int AnalogVar::getNormMin() const
{
    return normMin;
}

void AnalogVar::setNormMin(int value)
{
    normMin = value;
}

int AnalogVar::getNormMax() const
{
    return normMax;
}

void AnalogVar::setNormMax(int value)
{
    normMax = value;
}

float AnalogVar::getCoeff() const
{
    return coeff;
}

void AnalogVar::setCoeff(float value)
{
    coeff = value;
}

AnalogVar::AnalogVar():name(""),comment(""),dPrior(NORMAL),address(0),
    scaleMin(0),scaleMax(65535),normMin(0),normMax(65535),coeff(1.0)
{

}
