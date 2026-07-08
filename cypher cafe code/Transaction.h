#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>

class Transaction
{
public:
    enum Type
    {
        TopUp,
        Payment,
        Refund
    };

    Transaction();

    Transaction(int id,
                int customerId,
                double amount,
                Type type,
                const QString &status);

    int getTransactionId() const;
    int getCustomerId() const;
    double getAmount() const;
    Type getType() const;
    QString getStatus() const;
    QDateTime getDateTime() const;

    void setTransactionId(int id);
    void setCustomerId(int id);
    void setAmount(double amount);
    void setType(Type type);
    void setStatus(const QString &status);
    void setDateTime(const QDateTime &date);

    bool processPayment();
    QString generateReceipt() const;
    void recordTransaction();

private:
    int transactionId;
    int customerId;
    double amount;
    Type transactionType;
    QString status;
    QDateTime transactionDate;
};

#endif // TRANSACTION_H