#ifndef ANALOGVAR_H
#define ANALOGVAR_H

#include <QString>

class AnalogVar
{
public:
    enum displPriority {DONTDISPLAY,LOW,NORMAL,HIGH};
private:
    QString name;
    QString comment;
    displPriority dPrior;
    int address;
    int scaleMin;
    int scaleMax;
    int normMin;
    int normMax;
    float coeff;
public:
    AnalogVar();
    QString getName() const;
    void setName(const QString &value);
    QString getComment() const;
    void setComment(const QString &value);
    displPriority getDPrior() const;
    void setDPrior(const displPriority &value);
    int getAddress() const;
    void setAddress(int value);
    int getScaleMin() const;
    void setScaleMin(int value);
    int getScaleMax() const;
    void setScaleMax(int value);
    int getNormMin() const;
    void setNormMin(int value);
    int getNormMax() const;
    void setNormMax(int value);
    float getCoeff() const;
    void setCoeff(float value);
};

#endif // ANALOGVAR_H
