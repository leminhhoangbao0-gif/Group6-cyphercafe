#include "loginscreen.h"
#include "ui_loginscreen.h"
#include "mainwindow.h"
#include "navigationmanager.h"
#include "posview.h"
#include <QPushButton>

loginscreen::loginscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginscreen)
{
    ui->setupUi(this);

    connect(ui->btnLogin, &QPushButton::clicked, this, &loginscreen::on_btnLogin_clicked);
}
loginscreen::~loginscreen()
{
    delete ui;
}

void loginscreen::on_btnLogin_clicked()
{

    MainWindow* mainWin = qobject_cast<MainWindow*>(this->window());

    if (mainWin) {

        posview *pos = new posview();
        mainWin->setCentralWidget(pos);
    }
}