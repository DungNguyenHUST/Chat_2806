#include "chat.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QCoreApplication>
#include <QDBusInterface>

Chat::Chat(QObject *parent,QString username, char * start):
    QObject(parent),m_iface(SERVICE_NAME+ QString (start),"/","",QDBusConnection::sessionBus())
{
    m_start = start;
    m_username = username;
    qDebug()<< username;
    m_data= QSqlDatabase::addDatabase("QSQLITE");
    m_data.setDatabaseName("chat.sql");
    m_data.open();
    m_query= QSqlQuery(m_data);
    m_query.exec("create table if not exists tableMessage\
                                (id integer primary key,\ username varchar(50),\ message varchar(255),\ time timestamp\)\
                                " );
      QDBusConnection::sessionBus().registerObject("/", this);
      QDBusConnection::sessionBus().connect(QString(),QString(),SERVICE_NAME,"message",this,SLOT(messageSlot(QString,QString)));
}

Chat::~Chat()
{

}

void Chat::loadMessageFromSQL(QString username)
{
m_query = QSqlQuery("SELECT *FROM tableMessage");
    while(m_query.next())
    {
    sendToQml(m_query.value(1).toString(),m_query.value(2).toString(),m_query.value(3).toString());
    }
}
// receive message from QML
void Chat::receiveFromQml(QString message)
{
   sendMessage(m_username,message);
   qDebug()<<message;
}

void Chat::messageSlot(QString username, QString message)
{
    QString msg(QLatin1String ("<%1 %2"));
    msg = msg.arg(username,message);
    m_message.append(msg);
    if (m_message.count()>100)
    {
        m_message.removeFirst();
    }
}
// send message in DBUS
void Chat::sendMessage(QString username,QString message)
{
    if (m_iface.isValid())
    {
        QDBusReply <QString> reply = m_iface.call("sendMessage",username,message);
        if (!reply.isValid())
        {
        fprintf(stderr,"%s\n",qPrintable(QDBusConnection::sessionBus().lastError().message()));
        }
    }
    QDBusMessage msg = QDBusMessage::createSignal("/",SERVICE_NAME,"message");
    QDBusConnection::sessionBus().send(msg);
    postMessage(message);

}

//post message in QML
void Chat::postMessage(QString message)
{
m_nowTime = QDateTime::currentDateTime();
storeMessage(m_username,message,m_nowTime);
loadMessageFromSQL(m_username);
}

void Chat::storeMessage(QString username, QString message, QDateTime time)
{
    time  = QDateTime::currentDateTime();
    m_query.prepare("INSERT INTO tableMessage(username, message, time) \
                    values(:username,:message,:time)");

    m_query.bindValue(":username", username);
    m_query.bindValue(":message", message);
    m_query.bindValue(":time", time);
    m_query.exec();

}

int main(int argc, char *argv[])
{
    char *start;
    QGuiApplication app(argc, argv);

    QString username = "";
    Chat chat(0,username,start);
    QQmlApplicationEngine chatWindow;
    chatWindow.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QQmlContext*context = chatWindow.rootContext();
    context->setContextProperty("chat",&chat);
    if (!QDBusConnection::sessionBus().isConnected())
    {
        qWarning("Cannot connect to the DBus .\n");
        return 1;
    }
    if (QSqlDatabase::drivers().isEmpty())
    {
        qWarning("Cannot found database. \n");
        return 1;
    }

    return app.exec();
}

