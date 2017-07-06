#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QDateTime>
#include <QDBusInterface>
#include <QtDBus>
#include <QtSql>
#include <QSql>

#define SERVICE_NAME "org.example.chat"

#define DATABASE_HOSTNAME "ChatDataBase"
#define DATABASE_NAME "Chat.db"

class ChatMain : public QObject
{
    Q_OBJECT

public:
    explicit ChatMain();
    virtual ~ChatMain();

    void updateHistory();
    void sendMessage(QString text);

    // store data in the SQL
    void storeDataIntoSQL(QString username,QString text, QDateTime time);


signals:

    void action(const QString &username,const QString &text);
    void message(const QString &username,const QString &text );

    void sendDataToQml(QString data);

public slots:
    void receiveMessageFromQml (QString text);
    void receiveUserNameFromQml(QString username);
    void messageSlot (QString username,QString text);
    void actionSlot(QString username,QString text);

     void loadDataFromSQL(QString key);

    void exitChat();

private:
    QString m_username;
    QStringList m_message;
    QDateTime m_nowTime ;
    QTime m_currentTime;
    QSqlQuery m_query;
    QSqlDatabase m_dataBase;
};

#endif // CHAT_H
