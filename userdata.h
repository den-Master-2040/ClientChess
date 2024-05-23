#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>

class UserData : public QObject
{
    Q_OBJECT
public:
    explicit UserData(QObject *parent = nullptr);

    QString getName() const;
    void setName(const QString &value);

    QString getPasword() const;
    void setPasword(const QString &value);

private:
    QString name = "NEWCLIENTDEN";
    QString pasword = "";

};

#endif // USERDATA_H
