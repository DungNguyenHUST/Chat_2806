#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QDateTime>
#include <QDBusInterface>
#include <QtDBus>
#include <QtSql>
#include <QSql>

#define SERVICE_NAME "lge.example.QtDBus.chatExample"

class Chat : public QObject
{
    Q_OBJECT

public:
    explicit Chat(QObject * parent,QString username, char* start);
    virtual ~Chat();

    void loadMessageFromSQL(QString username);
    void postMessage(QString message);
    void sendMessage(QString username,QString message);
    void storeMessage(QString username,QString message, QDateTime time);

signals:
    void action(QString username,QString message);
    void message(QString username,QString message );
    void sendToQml(QString username, QString message, QString time);

public slots:
    void receiveFromQml (QString message);
    void messageSlot (QString username,QString message);

private:
    QString m_start;
    QString m_username;
    QStringList m_message;
    QDBusInterface m_iface;
    QDateTime m_nowTime;
    QSqlQuery m_query;
    QSqlDatabase m_data;

};

#endif // CHAT_H
