
#include "chat_interface.h"
/*
 * Implementation of interface class OrgExampleChatInterface
 */

OrgExampleChatInterface::OrgExampleChatInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

OrgExampleChatInterface::~OrgExampleChatInterface()
{
}

