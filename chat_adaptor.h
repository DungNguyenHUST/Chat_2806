
#ifndef CHAT_ADAPTOR_H
#define CHAT_ADAPTOR_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

class ChatAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.example.chat")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.example.chat\">\n"
"    <signal name=\"message\">\n"
"      <arg direction=\"out\" type=\"s\" name=\"nickname\"/>\n"
"      <arg direction=\"out\" type=\"s\" name=\"text\"/>\n"
"    </signal>\n"
"    <signal name=\"action\">\n"
"      <arg direction=\"out\" type=\"s\" name=\"nickname\"/>\n"
"      <arg direction=\"out\" type=\"s\" name=\"text\"/>\n"
"    </signal>\n"
"  </interface>\n"
        "")
public:
    ChatAdaptor(QObject *parent);
    virtual ~ChatAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
Q_SIGNALS: // SIGNALS

    void action(const QString &username, const QString &text);
    void message(const QString &username, const QString &text);
};

#endif
