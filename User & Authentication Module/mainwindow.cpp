#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setCentralWidget(QWidget *widget)
{

    if (this->centralWidget()) {
        this->centralWidget()->setParent(nullptr);
    }

    QMainWindow::setCentralWidget(widget);
}