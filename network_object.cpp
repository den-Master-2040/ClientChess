#include "network_object.h"
#include "QDataStream"
#include "clientglobal.h"
network_object::network_object(QObject *parent) : QObject(parent)
{
    socket = new QSslSocket(this);
    connect(socket, &QSslSocket::readyRead, this, &network_object::slotReadyRead);
    t_connectToHost = new QTimer();
    connect(t_connectToHost, &QTimer::timeout, [this]()
    {
        if(socket->state()!=QSslSocket::ConnectedState)
        {
            socket->ignoreSslErrors();
            socket->connectToHostEncrypted(ip, port);
            qDebug()<< "ip: " << ip << " port: " << port;
            connect(socket, &QSslSocket::encrypted, [this](){
                //можно отправл[gять данные
                encrypted = true;
            });
            REF_CLIENT.getMainmenu()->setConnections(false);
        }
        else
        {
            REF_CLIENT.getMainmenu()->setConnections(true);
        }
    });
    t_connectToHost->start(1);

    t_readSocket = new QTimer();
    connect(t_readSocket, &QTimer::timeout, [this]()
    {
        if(encrypted)
            slotReadyRead();
    });
    t_readSocket->start(300);
}

void network_object::SendToServer(QString str)
{
    str.push_front(0x02);
    str.append(0x03);
    Data.clear();
    QDataStream out (&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << str;

    if(socket->state() == QSslSocket::ConnectedState){
        socket->write(Data);
        qDebug() << str;
    }
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
                REF_CLIENT.getMainmenu()->setNullGroup(false);

            if(message.at(1) == 'g')
            {
                QVector<group> groups;
                group lg;
                //groups.clear();
                int countUsers = 1;
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

                if(message.at(message.size()-1) == '2')
                    countUsers = 2;
                REF_CLIENT.getGroupsMenu()->setDataGroup(groups,countUsers);
                REF_CLIENT.setGroupsMenu();

            }
            }
            if(message.at(1) == 'C' && message.at(2) == 'T')
            {
                if(REF_CLIENT.getMainWindow()->getCurrentWidget_() == REF_CLIENT.getFormGame())
                {

                    REF_CLIENT.getFormGame()->clearMap();
                    REF_CLIENT.getFormGame()->chessMap.clear();
                    REF_CLIENT.getFormGame()->scene->clear();
                    REF_CLIENT.getGroupMenu()->setCurrentIndex_(0);
                    REF_CLIENT.getNetworkObj()->SendToServer("DG");
                    REF_CLIENT.setMainMenu();
                    break;
                }
                REF_CLIENT.getGroupMenu()->disconnectAnother();
            }
            else{
                REF_CLIENT.getMainmenu()->setNullGroup(true);
            }
            if(message.at(1) == 'M' && message.at(2) == 'M')
            {
                message.remove(0,3);
                REF_CLIENT.getGroupMenu()->setNameGroup(message);
            }
            break;
        }
        case 'C':
        {
            if(message.at(1) == 'U')
            {
                QString lsu;
                int i = 3;
                for(; i < message.size(); i++)
                    if(message.at(i) != ' ')
                        lsu += message.at(i);
                    else break;

                qDebug() << "login_secondUser: " << lsu;
                REF_CLIENT.setGroupMenu();
                REF_CLIENT.joinGroup();
                REF_CLIENT.getGroupMenu()->connectUser(lsu);
                QString namegroup;
                for(i++; i < message.size(); i++)
                {
                    namegroup+=message.at(i);
                }
                REF_CLIENT.getGroupMenu()->setNameGroup(namegroup);
            }

            if(message.at(1) == 'V')
            {
                QString lsu;
                int i = 3;
                for(; i < message.size(); i++)
                    if(message.at(i) != ' ')
                        lsu += message.at(i);
                    else break;

                qDebug() << "login_secondUser: " << lsu;
                QString lsu2;
                i++;
                for(; i < message.size(); i++)
                    if(message.at(i) != ' ')
                        lsu2 += message.at(i);
                    else break;

                qDebug() << "login_firstUser: " << lsu2;
                REF_CLIENT.setGroupMenu();
                REF_CLIENT.joinGroup();
                REF_CLIENT.getGroupMenu()->connectWithViewers(lsu, lsu2);

                QString namegroup;
                for(i++; i < message.size(); i++)
                {
                    namegroup+=message.at(i);
                }
                REF_CLIENT.getGroupMenu()->setNameGroup(namegroup);
            }
            break;
        }
        case 'T':
        {
            message.remove(0, 1);
            REF_CLIENT.getGroupMenu()->messageAnothetUser(message);
            break;
        }
        case 'H'://hod
        {
            //"HOD2344" // 23 Элемент в массиве сходил на 4 строку 4 позицию
            message.remove(0,3);
            int number = message.mid(0,2).toInt();

            int x = message.mid(2,1).toInt();
            int y = message.mid(3,1).toInt();

            qDebug() << "Number : "<< number << " x: " << x << " y: " << y;
            REF_CLIENT.getFormGame()->moveItem_(number, x, y);

            break;
        }
        case 'G':
        {
            if(message.at(1) == 'O')
            {
                REF_CLIENT.getFormGame()->setNameLb(REF_CLIENT.getGroupMenu()->nameAnotherPlayer,REF_CLIENT.getUserData()->getName());

                REF_CLIENT.getFormGame()->setPlayerMap();
                REF_CLIENT.getMainWindow()->setCurrentWidget_(REF_CLIENT.getFormGame());

            }
            if(message.at(2) == 'W'){
                REF_CLIENT.getUserData()->setTeam("white");
                REF_CLIENT.getFormGame()->setIsMyHod(true);
                REF_CLIENT.getFormGame()->setNameTeame("Вы играете за белых");
            }
            if(message.at(2) == 'B')
            {
                REF_CLIENT.getUserData()->setTeam("black");
                REF_CLIENT.getFormGame()->setIsMyHod(false);
                REF_CLIENT.getFormGame()->setNameTeame("Вы играете за черных");
            }
            if(message.at(2) == 'V')
            {
                REF_CLIENT.getUserData()->setTeam("none");
                REF_CLIENT.getFormGame()->setIsMyHod(false);
                REF_CLIENT.getFormGame()->setNameTeame("Вы зритель");
            }
            break;
        }
        case 'F':
        {
            qDebug() << "FAIL PASS";
            break;
        }
        case 'S':
        {
            if(message.at(1) == "L")
            {
                //succesfulLogin
                REF_CLIENT.getFormLogin()->succesfulLogin(); // устнавливаем логин и пароль
                REF_CLIENT.setMainMenu();                    // устанавливаем главное окно
                SendToServer("II");                          // запрашиваем данные 
            }
            break;

        }
        case 'N':
        {
            if(message.at(1) == "L")
            {
                //NotLogin
                REF_CLIENT.getFormLogin()->viewFalseLogPass();
            }
            break;
        }
        case 'U':
        {
            if(message.at(1) == 'D')
            {
                QString countHod;
                int i = 3;
                for(; i < message.size(); i++)
                {
                    if(message[i] != ' ')
                    {
                        countHod += message[i];
                    }
                    else break;
                }
                REF_CLIENT.getUserData()->countHod = countHod.toInt();
                i++;
                QString countFihgtFugure;
                for(; i < message.size(); i++)
                {
                    if(message[i] != ' ')
                    {
                        countFihgtFugure += message[i];
                    }
                    else break;
                }
                REF_CLIENT.getUserData()->countFihgtFugure = countFihgtFugure.toInt();
                i++;
                QString levelUser;
                for(; i < message.size(); i++)
                {
                    if(message[i] != ' ')
                    {
                        levelUser += message[i];
                    }
                    else break;
                }
                REF_CLIENT.getUserData()->levelUser = levelUser.toInt();
                i++;
                QString countWin;
                for(; i < message.size(); i++)
                {
                    if(message[i] != ' ')
                    {
                        countWin += message[i];
                    }
                    else break;
                }
                REF_CLIENT.getUserData()->countWin = countWin.toInt();
                i++;
                QString countDef;
                for(; i < message.size(); i++)
                {
                    if(message[i] != ' ')
                    {
                        countDef += message[i];
                    }
                    else break;
                }
                REF_CLIENT.getUserData()->countDef = countDef.toInt();
                i++;
                QString countDraw;
                for(; i < message.size(); i++)
                {
                    if(message[i] != ' ')
                    {
                        countDraw += message[i];
                    }
                    else break;
                }
                REF_CLIENT.getUserData()->countDraw = countDraw.toInt();
                REF_CLIENT.getFormUser()->updateStatistics();

            }
        }
        case 'M':
        {

            if(message.at(1) == 'M')
            {
                QString lsu;
                int i = 4;
                for(; i < message.size(); i++)
                    if(message.at(i) != ' ')
                        lsu += message.at(i);
                    else break;

                qDebug() << "login_secondUser: " << lsu;
                REF_CLIENT.setGroupMenu();
                REF_CLIENT.joinGroup();
                REF_CLIENT.getGroupMenu()->connectUser(lsu);
                QString namegroup;
                for(i++; i < message.size(); i++)
                {
                    namegroup+=message.at(i);
                }
                REF_CLIENT.getGroupMenu()->setNameGroup(namegroup);

                REF_CLIENT.getFormGame()->setNameLb(REF_CLIENT.getGroupMenu()->nameAnotherPlayer,REF_CLIENT.getUserData()->getName());

                REF_CLIENT.getFormGame()->setPlayerMap();
                REF_CLIENT.getMainWindow()->setCurrentWidget_(REF_CLIENT.getFormGame());
            }
            if(message.at(2) == 'W'){
                REF_CLIENT.getUserData()->setTeam("white");
                REF_CLIENT.getFormGame()->setIsMyHod(true);
                REF_CLIENT.getFormGame()->setNameTeame("Вы играете за белых");
            }
            if(message.at(2) == 'B')
            {
                REF_CLIENT.getUserData()->setTeam("black");
                REF_CLIENT.getFormGame()->setIsMyHod(false);
                REF_CLIENT.getFormGame()->setNameTeame("Вы играете за черных");
            }
        }
        case 'V':
        {
            //мы зритель, и нам пришёл ход
        
        }
        default:break;
    }
}

void network_object::loginToHost()
{
    SendToServer("Login, my login=" + login + " my token=" + token + " ");
}

void network_object::setipport(QString ip, int port)
{
    //t_connectToHost->stop();
    this->ip = ip;
    this->port = port;
    t_connectToHost->start(1);
}

void network_object::slotReadyRead()
{

    qDebug() << "socket->readBufferSize(): " << socket->readBufferSize();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_9);
    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "Read message for QDataStream...";
        QString str;
        in >> str;
        lastMessage = str;
        if(str != "")
            RequaredRecvMessage(str);
    }
    else
    {
        qDebug() << "fail to read message for QDataStream!";
    }

}
