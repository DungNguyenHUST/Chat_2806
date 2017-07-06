
#include "dbus_interface.h"
/*
 * Implementation of interface class OrgExampleChatInterface
 */

DBusInterface::DBusInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

DBusInterface::~DBusInterface()
{
}

