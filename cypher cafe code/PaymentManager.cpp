#include "PaymentManager.h"

PaymentManager::PaymentManager()
{
    nextTransactionId = 1;
}

bool PaymentManager::topUp(int customerId,
                           double &balance,
                           double amount)
{
    if(amount <= 0)
        return false;

    balance += amount;

    Transaction transaction(
                nextTransactionId++,
                customerId,
                amount,
                Transaction::TopUp,
                "Success");

    transaction.processPayment();
    transaction.recordTransaction();

    return true;
}

bool PaymentManager::deductMoney(int customerId,
                                 double &balance,
                                 double amount)
{
    if(amount <= 0)
        return false;

    if(balance < amount)
        return false;

    balance -= amount;

    Transaction transaction(
                nextTransactionId++,
                customerId,
                amount,
                Transaction::Payment,
                "Success");

    transaction.processPayment();
    transaction.recordTransaction();

    return true;
}

bool PaymentManager::processPayment(Transaction &transaction)
{
    return transaction.processPayment();
}

QString PaymentManager::generateReceipt(const Transaction &transaction)
{
    return transaction.generateReceipt();
}