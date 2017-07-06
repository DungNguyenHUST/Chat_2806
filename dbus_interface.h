

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

class DBusInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.example.chat"; }

public:
    DBusInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~DBusInterface();

public Q_SLOTS: // METHODS
Q_SIGNALS: // SIGNALS
    void action(const QString &username, const QString &text);
    void message(const QString &username, const QString &text);
};

namespace org {
  namespace example {
    typedef ::DBusInterface chat;
  }
}
#endif
