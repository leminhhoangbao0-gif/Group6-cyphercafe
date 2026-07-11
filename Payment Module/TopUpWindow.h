#ifndef TOPUPWINDOW_H
#define TOPUPWINDOW_H

#include <QDialog>

#include "PaymentManager.h"
#include "BalanceManager.h"

namespace Ui {
class TopUpWindow;
}

class TopUpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TopUpWindow(QWidget *parent = nullptr);
    ~TopUpWindow();

    void setCustomer(int customerId);
    void setBalanceManager(BalanceManager *manager);

private slots:

    void on_btn10k_clicked();
    void on_btn20k_clicked();
    void on_btn50k_clicked();
    void on_btn100k_clicked();
    void on_btn200k_clicked();
    void on_btn500k_clicked();

    void on_btnConfirm_clicked();
    void on_btnClose_clicked();

private:

    void updateBalanceLabel();

    Ui::TopUpWindow *ui;

    PaymentManager paymentManager;

    BalanceManager *balanceManager;

    int customerId;
};

#endif // TOPUPWINDOW_H