#include "chat.h"
#include "chat_adaptor.h"
#include "chat_interface.h"
#include <QApplication>
#include <QMessageBox>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QCoreApplication>
#include <QDBusInterface>

ChatMain::ChatMain()
{
    m_username = "username";
    // create SQLite and open database
    m_dataBase= QSqlDatabase::addDatabase("QSQLITE");
    m_dataBase.setHostName(DATABASE_HOSTNAME);
    m_dataBase.setDatabaseName(DATABASE_NAME);
    m_dataBase.open();
    m_query= QSqlQuery(m_dataBase);
    m_query.exec("create table if not exists tableMessage\
                                (id integer primary key,\ username varchar(255),\ text varchar(255),\ time timestamp)\
                                " );

     // add dbus interface and initial dbus
     new ChatAdaptor(this);
     QDBusConnection::sessionBus().registerObject("/", this);
     org::example::chat *iface;
     iface = new org::example::chat(QString(), QString(), QDBusConnection::sessionBus(), this);
     QDBusConnection::sessionBus().connect(QString(), QString(), "org.example.chat", "message", this, SLOT(messageSlot(QString,QString)));
     connect(iface, SIGNAL(action(QString,QString)), this, SLOT(actionSlot(QString,QString)));
}

ChatMain::~ChatMain()
{
    m_dataBase.close();
}

// store in QString list after send click
void ChatMain::updateHistory()
{
    QString current = m_message.last();
    m_nowTime  = QDateTime::currentDateTime();
    sendDataToQml(">>"+ m_nowTime.toString() +">"+ current );
}
// receive message from QML
void ChatMain :: receiveMessageFromQml(QString text)
{
    m_nowTime  = QDateTime::currentDateTime();
    storeDataIntoSQL(m_username,text,m_nowTime);
    sendMessage(text);
    if (text == "exit")
    {
        exitChat();
    }
}
// set user name after receive from QML
void ChatMain :: receiveUserNameFromQml(QString username)
{
   emit action(username,QLatin1String (" JOINED TO THE CHAT ROOM"));
   m_username = username;
}

void ChatMain::messageSlot(QString username, QString text)
{
    QString msg(QLatin1String ("<%1 %2"));
    msg = msg.arg(username,text);
    m_message.append(msg);

    if (m_message.count() >100)
    {
        m_message.removeFirst();
    }
    updateHistory();
}

void ChatMain::actionSlot(QString username, QString text)
{
    QString msg( QLatin1String("* %1 %2") );
    msg = msg.arg(username,text);
    m_message.append(msg);
    if (m_message.count() > 100)
    {
        m_message.removeFirst();
    }
    updateHistory();
}

void ChatMain::exitChat()
{
    emit action(m_username,QLatin1String (" LEAVE THE CHAT ROOM"));
    QApplication::quit();
}

// send message in DBUS
void ChatMain::sendMessage(QString text)
{
    QDBusMessage msg = QDBusMessage::createSignal("/", "org.example.chat", "message");
    msg<<m_username<<text;
    QDBusConnection::sessionBus().send(msg);
}
// store meesage in SQL, insert into table
void ChatMain::storeDataIntoSQL( QString username,QString text, QDateTime time)
{
    username = m_username;
    m_query.prepare("INSERT INTO tableMessage( username,text, time)\ values(:username, :text , :time)") ;
    m_query.bindValue(":username",username);
    m_query.bindValue(":text", text);
    m_query.bindValue(":time", time);
    m_query.exec();
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    ChatMain chatMain;
    QQmlApplicationEngine chatWindow;
    chatWindow.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QQmlContext*context = chatWindow.rootContext();
    context->setContextProperty("chatMain",&chatMain);

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

