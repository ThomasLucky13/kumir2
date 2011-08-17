#ifndef BROWSER_PLUGIN_H
#define BROWSER_PLUGIN_H

#include "extensionsystem/kplugin.h"
#include "interfaces/browserinterface.h"

namespace Browser {

class Plugin
        : public ExtensionSystem::KPlugin
        , public Shared::BrowserInterface
{
    Q_OBJECT
    Q_INTERFACES(Shared::BrowserInterface)
public:
    Plugin();
    ~Plugin();
    Shared::BrowserComponent createBrowser(const QUrl &url, const QMap<QString, QObject *> manageableObjects);
protected:
    QString initialize(const QStringList &);
    void changeCurrentDirectory(const QString &path);
private:
    class Dir * m_directory;
};

} // namespace Browser

#endif // BROWSER_PLUGIN_H
