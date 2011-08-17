#ifndef BROWSER_COMPONENT_H
#define BROWSER_COMPONENT_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

#include "interfaces/browserinterface.h"

namespace Browser {

namespace Ui {
    class Component;
}

class Component
        : public QWidget
{
    Q_OBJECT

public:
    explicit Component(class Plugin * plugin);
    inline void setManageableObjects(const QMap<QString, QObject*> &os) {m_manageableObjects = os; }
    QWebPage * createChildPage();
    ~Component();
    QList<QAction*> toolbarActions();
    QList<QMenu*> menuActions();

public slots:
    void go(const QUrl & url);
    void evaluateCommand(const QString & method, const QVariantList & arguments);
protected:
    void showEvent(QShowEvent *e);
private:
    Ui::Component *ui;
    QMap<QString, QObject*> m_manageableObjects;
    QAction * a_separator;
    QAction * a_goBack;
    QAction * a_reloadStop;

    QMenu * menu_edit;
    class Plugin * m_plugin;

signals:
    void titleChanged(const QString & title);
    void newWindowCreated(const Shared::BrowserComponent &);

private slots:
    void addJavaScriptObjects();
    void handleReloadStop();
    void handleLoadStarted();
    void handleLoadFinished();
};


} // namespace Browser
#endif // BROWSER_COMPONENT_H
