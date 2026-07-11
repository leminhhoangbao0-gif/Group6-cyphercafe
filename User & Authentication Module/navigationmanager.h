#ifndef NAVIGATIONMANAGER_H
#define NAVIGATIONMANAGER_H

#include <QObject>

class MainWindow;
class loginscreen;
class posview;

class navigationmanager : public QObject
{
    Q_OBJECT
public:
    explicit navigationmanager(QObject *parent = nullptr);
    void setMainWindow(MainWindow *mainWindow);

    void switchToLogin();
    void switchToPOS();

private:
    MainWindow *m_mainWindow;
    loginscreen *m_loginScreen;
    posview *m_posView;
};

#endif // NAVIGATIONMANAGER_H