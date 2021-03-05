#include "loglatedit.h"
#include "loglateditplugin.h"

#include <QtPlugin>

LogLatEditPlugin::LogLatEditPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void LogLatEditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LogLatEditPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LogLatEditPlugin::createWidget(QWidget *parent)
{
    return new LogLatEdit(parent);
}

QString LogLatEditPlugin::name() const
{
    return QLatin1String("LogLatEdit");
}

QString LogLatEditPlugin::group() const
{
    return QLatin1String("");
}

QIcon LogLatEditPlugin::icon() const
{
    return QIcon();
}

QString LogLatEditPlugin::toolTip() const
{
    return QLatin1String("");
}

QString LogLatEditPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool LogLatEditPlugin::isContainer() const
{
    return false;
}

QString LogLatEditPlugin::domXml() const
{
    return QLatin1String("<widget class=\"LogLatEdit\" name=\"logLatEdit\">\n</widget>\n");
}

QString LogLatEditPlugin::includeFile() const
{
    return QLatin1String("loglatedit.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(loglateditplugin, LogLatEditPlugin)
#endif // QT_VERSION < 0x050000
