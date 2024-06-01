#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>
#include <QFile>
class UserData : public QObject
{
    Q_OBJECT
public:

    explicit UserData(QObject *parent = nullptr);

    void loginingAutherization();

    QString getName() const;
    void setName(const QString &value);

    QString getPasword() const;
    void setPasword(const QString &value);

    QString getTeam() const;
    void setTeam(const QString &value);

    void sendUserData();

    int countHod          = 0; //всего количество ходов
    int countFihgtFugure  = 0;//уничтоженные фигуры
    int levelUser         = 0;
    int countWin          = 0;//победы
    int countDef          = 0;//поражения
    int countDraw         = 0;//ничьи

private:
    QFile fileLogPass;
    QString name    = "NEWCLIENTDEN";
    QString pasword = "";
    QString team    = "";


};

#endif // USERDATA_H
