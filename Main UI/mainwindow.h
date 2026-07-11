#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "navigationmanager.h" // Đảm bảo có include này

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setCentralWidget(QWidget *widget);


    navigationmanager* getNavigationManager() { return &m_navManager; }

private:
    Ui::MainWindow *ui;
    navigationmanager m_navManager;
};

#endif // MAINWINDOW_H
