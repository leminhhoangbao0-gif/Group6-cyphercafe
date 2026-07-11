#include "applicationmanager.h"
#include "mainwindow.h"

applicationmanager::applicationmanager(QObject *parent) : QObject(parent)
{
    m_mainWindow = nullptr;
}

void applicationmanager::initialize()
{
    m_mainWindow = new MainWindow();
    m_navManager.setMainWindow(m_mainWindow);

    m_navManager.switchToLogin();

    m_mainWindow->show();
}