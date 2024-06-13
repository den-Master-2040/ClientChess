#ifndef NETWORK_OBJECT_H
#define NETWORK_OBJECT_H

#include <QSslSocket>
#include <QObject>
#include <QTimer>



class network_object : public QObject
{
    Q_OBJECT
public:
    explicit network_object(QObject *parent = nullptr);

    void SendToServer(QString str);
    void RequaredRecvMessage(QString message);

    void loginToHost();
    void setipport(QString ip, int port);


    QByteArray Data;
    QSslSocket *socket= nullptr;
    int mysocketDescriptor = -1; // дескриптор который присвоил нам сервер

    QTimer *t_result_ping = nullptr;
    QTimer *t_readSocket = nullptr;
    QString ip = "89.179.126.139";
    int port = 2323;
    QTimer *t_connectToHost = nullptr;
    QString lastMessage;
    QString login = "DEN_CHIK_";
    QString token = "1qaz";
    int size_users = -1;
    QString messageToUser;
    QString hod;
    bool encrypted = false;
signals:
public slots:
    void slotReadyRead();

};

#endif // NETWORK_OBJECT_H
