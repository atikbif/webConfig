#include "messagevar.h"

QString MessageVar::getName() const
{
    return name;
}

void MessageVar::setName(const QString &value)
{
    name = value;
}

QString MessageVar::getMessage() const
{
    return message;
}

void MessageVar::setMessage(const QString &value)
{
    message = value;
}

MessageVar::mesType MessageVar::getType() const
{
    return mType;
}

void MessageVar::setType(const mesType &type)
{
    mType = type;
}

QString MessageVar::getParentName() const
{
    return parentName;
}

void MessageVar::setParentName(const QString &value)
{
    parentName = value;
}

int MessageVar::getBitNum() const
{
    return bitNum;
}

void MessageVar::setBitNum(int value)
{
    if((value>=0)&&(value<16)) bitNum = value;
}

MessageVar::MessageVar():name(""),message(""),mType(INFO),parentName(""),bitNum(0)
{

}
