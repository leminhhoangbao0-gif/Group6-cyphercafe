#ifndef SESSIONWINDOW_H
#define SESSIONWINDOW_H

#include "SessionManager.h"

#include <QMainWindow>

namespace Ui {
class SessionWindow;
}

class SessionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SessionWindow(SessionManager *sessionManager, QWidget *parent = nullptr);
    ~SessionWindow();

private slots:
    void refreshPcs();
    void refreshSessions();
    void startSelectedSession();
    void endSelectedSession();
    void lockSelectedPc();
    void unlockSelectedPc();
    void showError(const QString &message);

private:
    int selectedPcId() const;
    void configureTables();

    Ui::SessionWindow *ui;
    SessionManager *m_sessionManager;
};

#endif
