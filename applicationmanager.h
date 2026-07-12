#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include <QObject>
#include "navigationmanager.h"

class MainWindow;

class applicationmanager : public QObject
{
    Q_OBJECT
public:
    explicit applicationmanager(QObject *parent = nullptr);
    void initialize();

private:
    MainWindow *m_mainWindow;
    navigationmanager m_navManager;
};

#endif // APPLICATIONMANAGER_H