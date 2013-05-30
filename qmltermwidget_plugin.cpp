#include "qmltermwidget_plugin.h"
#include "qmlterminal.h"

#include <qqml.h>

void QmltermwidgetPlugin::registerTypes(const char *uri)
{
    // @uri org.qterminal.qmlterminal
    qmlRegisterType<QMLTerminal>(uri, 1, 0, "QMLTerminal");
}


