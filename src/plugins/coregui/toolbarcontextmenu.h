#ifndef COREGUI_TOOLBARCONTEXTMENU_H
#define COREGUI_TOOLBARCONTEXTMENU_H

#include "widgets/actionproxy.h"
#include "extensionsystem/settings.h"

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSet>

namespace CoreGUI {

class ToolbarContextMenu : public QWidget
{
    Q_OBJECT
public:
    explicit ToolbarContextMenu(QWidget *parent = 0);
    void addProxy(Widgets::ActionProxy * proxyItem);
    void addSeparator();
    void finalize();

    void setSettingsObject(ExtensionSystem::SettingsPtr settings, const QString &settingsPrefix);
    void setExplicitImportNames(const QSet<QString> explicitItemNames);

    void saveSettings() const;
    void loadSettings();

    static Qt::CheckState defaultVisible(const QString & objectName);
    static Qt::CheckState f2cs(float value);
    static float cs2f(Qt::CheckState state);

    bool isItemVisible(Qt::CheckState state, const QString & objectName) const;


protected Q_SLOTS:
    void toggleProxyButtonVisible(int iState);
    void reset();
    void showAll();

protected:
    void paintEvent(QPaintEvent *event);
    QList<Widgets::ActionProxy*> items_;
    QSet<QString> forcedItemNames_;

    QGridLayout * grid_;
    int currentRow_;
    int currentColumn_;
    QPushButton * btnClose_;
    QPushButton * btnReset_;
    QPushButton * btnShowAll_;
    ExtensionSystem::SettingsPtr settings_;
    QString settingsPrefix_;
    QSet<QString> explicitImportNames_;
    bool ignoreStateChange_;

};

} // namespace CoreGUI

#endif // COREGUI_TOOLBARCONTEXTMENU_H
