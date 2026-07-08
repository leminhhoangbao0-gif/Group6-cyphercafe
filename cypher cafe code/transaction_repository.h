#ifndef TRANSACTION_REPOSITORY_H
#define TRANSACTION_REPOSITORY_H

#include <QList>
#include <QSqlDatabase>
#include "Transaction.h"

class TransactionRepository
{
public:
    TransactionRepository(QSqlDatabase database);

    bool addTransaction(const Transaction &transaction);

    bool updateTransaction(const Transaction &transaction);

    bool deleteTransaction(int transactionId);

    QList<Transaction> getAllTransactions();

    QList<Transaction> getTransactionsByCustomer(int customerId);

    Transaction getTransactionById(int transactionId);

private:
    QSqlDatabase db;
};

#endif // TRANSACTION_REPOSITORY_H