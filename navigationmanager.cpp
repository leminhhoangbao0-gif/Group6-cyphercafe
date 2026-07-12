#include "navigationmanager.h"
#include "mainwindow.h"
#include "loginscreen.h"
#include "posview.h"

navigationmanager::navigationmanager(QObject *parent) : QObject(parent)
{
    m_mainWindow = nullptr;
    m_loginScreen = nullptr;
    m_posView = nullptr;
}

void navigationmanager::setMainWindow(MainWindow *mainWindow)
{
    m_mainWindow = mainWindow;
}

void navigationmanager::switchToLogin()
{
    if (!m_mainWindow) return;

    if (!m_loginScreen) {
        m_loginScreen = new loginscreen(m_mainWindow);
    }


    m_mainWindow->setCentralWidget(m_loginScreen);
    m_loginScreen->show();
}

void navigationmanager::switchToPOS()
{
    if (!m_mainWindow) return;


    if (!m_posView) {
        m_posView = new posview(m_mainWindow);
    }


    m_mainWindow->setCentralWidget(m_posView);
    m_posView->show();
}