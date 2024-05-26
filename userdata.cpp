#include "userdata.h"
#include "clientglobal.h"
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
    REF_CLIENT.getNetworkObj()->SendToServer("NR"+value);
}

QString UserData::getPasword() const
{
    return pasword;
}

void UserData::setPasword(const QString &value)
{
    pasword = value;
    REF_CLIENT.getNetworkObj()->SendToServer("NP"+value);
}

QString UserData::getTeam() const
{
    return team;
}

void UserData::setTeam(const QString &value)
{
    team = value;
}
