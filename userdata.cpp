#include "userdata.h"
#include "clientglobal.h"
#include <QDataStream>

UserData::UserData(QObject *parent) : QObject(parent)
{

}

void UserData::loginingAutherization()
{
    //проверяем авторизацию по файлику. Файла нет или он пустой -  мы не авторизованы
    fileLogPass.setFileName("dataUser.txt");

    if(fileLogPass.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString datauser =  fileLogPass.readAll();

        if(datauser == "")
            REF_CLIENT.getMainWindow()->setCurrentWidget_(REF_CLIENT.getFormLogin());

    }
    else
    {
        REF_CLIENT.getMainWindow()->setCurrentWidget_(REF_CLIENT.getFormLogin());
    }


    fileLogPass.close();
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

void UserData::sendUserData()
{

    //int countHod          = 0; //всего количество ходов
    //int countFihgtFugure  = 0;//уничтоженные фигуры
    //int levelUser         = 0;
    //int countWin          = 0;//победы
    //int countDef          = 0;//поражения
    //int countDraw         = 0;//ничьи
    QString data;

    data += "UD " + QString::number(countHod)         + " "
                  + QString::number(countFihgtFugure) + " "
                  + QString::number(levelUser)        + " "
                  + QString::number(countWin)         + " "
                  + QString::number(countDef)         + " "
                  + QString::number(countDraw)        + " ";
    REF_CLIENT.getNetworkObj()->SendToServer(data);
}
