#include "userdata.h"

UserData::UserData(QObject *parent) : QObject(parent)
{

}

QString UserData::getName() const
{
    return name;
}

void UserData::setName(const QString &value)
{
    name = value;
}

QString UserData::getPasword() const
{
    return pasword;
}

void UserData::setPasword(const QString &value)
{
    pasword = value;
}
