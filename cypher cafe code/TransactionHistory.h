#ifndef TRANSACTIONHISTORY_H
#define TRANSACTIONHISTORY_H

#include <QDialog>

#include "transaction_repository.h"

namespace Ui {
class TransactionHistory;
}

class TransactionHistory : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionHistory(TransactionRepository *repository,
                                QWidget *parent = nullptr);

    ~TransactionHistory();

    void loadTransactions();

private slots:

    void on_btnRefresh_clicked();

    void on_btnReceipt_clicked();

private:

    QString typeToString(Transaction::Type type);

    Ui::TransactionHistory *ui;

    TransactionRepository *repository;
};

#endif // TRANSACTIONHISTORY_H