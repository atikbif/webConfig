#ifndef MESSAGEVAR_H
#define MESSAGEVAR_H

#include <QString>


class MessageVar
{
public:
    enum mesType {INFO,WARNING,ALARM};
private:
    QString name;
    QString message;
    mesType mType;
    QString parentName;
    int bitNum;
public:
    MessageVar();
    QString getName() const;
    void setName(const QString &value);
    QString getMessage() const;
    void setMessage(const QString &value);
    mesType getType() const;
    void setType(const mesType &type);
    QString getParentName() const;
    void setParentName(const QString &value);
    int getBitNum() const;
    void setBitNum(int value);
};

#endif // MESSAGEVAR_H
