#includ"Transaction.h"

transaction::Transaction()
{
    transactionId=0;
    customerId=0;
    amount=0;
    transactiontype= topup;
    status="pending";
    transactiondate=Qdatetime::currentdatetime();
}

transaction::transaction(int id,
                        int customer,
                        double money,
                        type type,
                        const Qstring&st)
{
    transactionId = id;
    customerId = customer;
    amount = money;
    transactiontype = type;
    status = st;
    transactiondate = Qdatetime::currentdatetime();
}

int transaction::getTransactionId() const
{
    return transactionId;
}

int Transaction::getCustomerId() const
{
    return customerId;
}

double Transaction::getAmount() const
{
    return amount;
}
Transaction::Type Transaction::getType() const
{
    return transactiontype;
}
QString Transaction::getStatus() const
{
    return status;
}
Qdatetime Transaction::getStatus() const
{
    return transactionDate;
}
void Transaction::setTransactionId(int id)
{
    transactionId = id;
}
void Transaction::setCustomerId(int id)
{
    customerId = id;
}

void Transaction::setAmount(double money)
{
    amount = money;
}

void Transaction::setType(type type)
{
    transactionType = type;
}

void transaction::setStatus(const Qstring &st)
{
    status = st;
}

void transaction::setDatetime(const Qdatetime &date)
{
    transactionDate = date;
}

bool transaction::process payment()
{
    if(amount <= 0)
    {
        status = "failed";
        return false;
    }
    status = "Success";
    transactionDate = Qdatetime::currentDatetime();
    return true;
}

Qstring transaction:generateReceipt() const
{
    Qstring typeString;
    switch(transactionType)
    {
     case TopUp:
        typeString = "Top Up";
        break;

    case Payment:
        typeString = "Payment";
        break;

    case Refund:
        typeString = "Refund";
        break;
    }

    QString receipt;
    receipt +=""=========== RECEIPT ===========\n";
    receipt += "Transaction ID : " + QString::number(transactionId) + "\n";
    receipt += "Customer ID    : " + QString::number(customerId) + "\n";
    receipt += "Type           : " + typeString + "\n";
    receipt += "Amount         : " + QString::number(amount,'f',2) + " VND\n";
    receipt += "Status         : " + status + "\n";
    receipt += "Date           : " + transactionDate.toString("dd/MM/yyyy hh:mm:ss") + "\n";
    receipt += "================================";

    return receipt;
}

void transaction::recordTransaction()
{
transactiondate = Qdatetime::currentDatetime();
}
    
