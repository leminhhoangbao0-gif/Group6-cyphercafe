#include "TopUpWindow.h"
#include "ui_TopUpWindow.h"

#include <QMessageBox>

TopUpWindow::TopUpWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TopUpWindow)
{
    ui->setupUi(this);

    customerId = 0;
    balanceManager = nullptr;

    ui->txtAmount->setText("0");
}

TopUpWindow::~TopUpWindow()
{
    delete ui;
}

void TopUpWindow::setCustomer(int id)
{
    customerId = id;
}

void TopUpWindow::setBalanceManager(BalanceManager *manager)
{
    balanceManager = manager;
    updateBalanceLabel();
}

void TopUpWindow::updateBalanceLabel()
{
    if(balanceManager == nullptr)
        return;

    ui->lblBalance->setText(
        QString::number(balanceManager->getBalance(),'f',0)
        + " VND");
}

void TopUpWindow::on_btn10k_clicked()
{
    ui->txtAmount->setText("10000");
}

void TopUpWindow::on_btn20k_clicked()
{
    ui->txtAmount->setText("20000");
}

void TopUpWindow::on_btn50k_clicked()
{
    ui->txtAmount->setText("50000");
}

void TopUpWindow::on_btn100k_clicked()
{
    ui->txtAmount->setText("100000");
}

void TopUpWindow::on_btn200k_clicked()
{
    ui->txtAmount->setText("200000");
}

void TopUpWindow::on_btn500k_clicked()
{
    ui->txtAmount->setText("500000");
}

void TopUpWindow::on_btnConfirm_clicked()
{
    if(balanceManager == nullptr)
        return;

    double amount = ui->txtAmount->text().toDouble();

    double balance = balanceManager->getBalance();

    if(paymentManager.topUp(customerId,
                            balance,
                            amount))
    {
        balanceManager->setBalance(balance);

        updateBalanceLabel();

        QMessageBox::information(this,
                                 "Success",
                                 "Top up successful.");
    }
    else
    {
        QMessageBox::warning(this,
                             "Error",
                             "Invalid amount.");
    }
}

void TopUpWindow::on_btnClose_clicked()
{
    close();
}