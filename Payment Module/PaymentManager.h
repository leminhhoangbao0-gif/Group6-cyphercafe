#ifndef PAYMENTMANAGER_H
#define PAYMENTMANAGER_H

#include <QString>
#include "Transaction.h"

class PaymentManager
{
public:
    PaymentManager();

    // Top up
    bool topUp(int customerId,
               double &balance,
               double amount);

    // Deduct session cost
    bool deductMoney(int customerId,
                     double &balance,
                     double amount);

    // Payment
    bool processPayment(Transaction &transaction);

    // Receipt
    QString generateReceipt(const Transaction &transaction);

private:
    int nextTransactionId;
};

#endif // PAYMENTMANAGER_H