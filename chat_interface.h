

#ifndef CHAT_INTERFACE_H
#define CHAT_INTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.example.chat
 */
class OrgExampleChatInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.example.chat"; }

public:
    OrgExampleChatInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgExampleChatInterface();

public Q_SLOTS: // METHODS
Q_SIGNALS: // SIGNALS
    void action(const QString &username, const QString &text);
    void message(const QString &username, const QString &text);
};

namespace org {
  namespace example {
    typedef ::OrgExampleChatInterface chat;
  }
}
#endif
