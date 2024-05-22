#include "network_object.h"
#include "QDataStream"
#include "clientglobal.h"
network_object::network_object(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &network_object::slotReadyRead);
    //connect(socket, &QTcpSocket::disconnect, socket, &QTcpSocket::deleteLater);
    socket->connectToHost("89.179.126.139", 2323);
    t_connectToHost = new QTimer();
    connect(t_connectToHost, &QTimer::timeout, [this]()
    {
        if(socket->state()!=QTcpSocket::ConnectedState)
        {
            //qDebug() << "unconnected state";
            socket->connectToHost("127.0.0.1", 2323);
            SendToServer("Login, my login=" + login + " my token=" + token + " ");
            REF_CLIENT.getMainmenu()->setConnections(false);
        }
        else
        {
            REF_CLIENT.getMainmenu()->setConnections(true);
            //t_connectToHost->stop();
        }
    });
    t_connectToHost->start(100);
}

void network_object::SendToServer(QString str)
{
    Data.clear();
    QDataStream out (&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << str;

    //qDebug() << socket->state();
    //qDebug() << "SendMsg : " << Data;
    socket->write(Data);
    //qDebug() << socket->state();
}

void network_object::RequaredRecvMessage(QString message)
{
    qDebug() << "RequaredRecvMessage, msg = " << message;
    if(message.size() > 0)
    switch (message.at(0).unicode()) {
        case 'Y':
        {
            message.remove(0,1);
            mysocketDescriptor = message.toInt();
            break;
        }
        case 'O':
        {
            if(message.at(1) == 'k')
            {
                REF_CLIENT.createGroup_();
            }
            break;
        }
        case 'I':
        {
            if(message.at(1) == 'S')
            {
                message.remove(0,2);
                size_users = message.toInt();
                REF_CLIENT.getMainmenu()->setCountUsers(size_users);
            }
            break;
        }
        case 'D':
        {
            if(message.size() > 2){
            if(message.at(1) == 'g')
            {
                QVector<group> groups;
                group lg;
                //groups.clear();
                for(int i = 0; i < message.size(); i++)
                {


                    if(message.at(i) == 'I')
                    {
                        QString index;
                        for(i++;message.at(i) != ' '; i++)
                            index+=message.at(i);

                        lg.id = index.toInt();
                        i++;
                    }

                    if(message.at(i) == 'G')
                    {
                        QString name_group;
                        for(i++;message.at(i) != ' '; i++)
                            name_group+=message.at(i);

                        lg.name = name_group;
                        i++;
                    }

                    if(message.at(i) == 'U')
                    {
                        QString user_login;
                        for(i++;message.at(i) != ' '; i++)
                            user_login+=message.at(i);

                        lg.name_first_user = user_login;

                    }
                    if(lg.id != -1 && lg.name != "" && lg.name_first_user != "")
                    {
                        groups.push_back(lg);
                        lg.id = -1;
                        lg.name = "";
                        lg.name_first_user = "";
                    }
                }
                REF_CLIENT.getGroupsMenu()->setDataGroup(groups);
                REF_CLIENT.setGroupsMenu();

            }
            } //else
                //emit signalendDataGroup();
            break;
        }
        case 'C':
        {
            if(message.at(1) == 'U')
            {
                QString lsu;
                for(int i = 3; i < message.size(); i++)
                    lsu += message.at(i);

                login_secondUser = lsu;
                qDebug() << "login_secondUser: " << login_secondUser;
                //emit signalSecondLogin();
            }
            break;
        }
        case 'T':
        {
            message.remove(0, 1);
            messageToUser = message;
            //emit signalRecvMessageFromAnotherUser();
            break;
        }
        case 'H'://hod
        {
            message.remove(0,1);
            hod = message;
            //emit signalHod();
            break;
        }
        default:break;
    }
}

void network_object::loginToHost()
{
    SendToServer("Login, my login=" + login + " my token=" + token + " ");
}

void network_object::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_9);
    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "Read message for QDataStream...";
        QString str;
        in >> str;
        lastMessage = str;
        RequaredRecvMessage(str);
    }
    else
    {
        qDebug() << "fail to read message for QDataStream!";
    }
}
