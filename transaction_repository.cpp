#include "transaction_repository.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

TransactionRepository::TransactionRepository(QSqlDatabase database)
{
    db = database;
}

bool TransactionRepository::addTransaction(const Transaction &transaction)
{
    QSqlQuery query(db);

    query.prepare(
        "INSERT INTO Transaction "
        "(TransactionID, CustomerID, Amount, Type, Status, Date) "
        "VALUES "
        "(:id,:customer,:amount,:type,:status,:date)");

    query.bindValue(":id",
                    transaction.getTransactionId());

    query.bindValue(":customer",
                    transaction.getCustomerId());

    query.bindValue(":amount",
                    transaction.getAmount());

    query.bindValue(":type",
                    (int)transaction.getType());

    query.bindValue(":status",
                    transaction.getStatus());

    query.bindValue(":date",
                    transaction.getDateTime());

    if(!query.exec())
    {
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}

bool TransactionRepository::updateTransaction(const Transaction &transaction)
{
    QSqlQuery query(db);

    query.prepare(
        "UPDATE Transaction SET "
        "Amount=:amount,"
        "Type=:type,"
        "Status=:status,"
        "Date=:date "
        "WHERE TransactionID=:id");

    query.bindValue(":amount",
                    transaction.getAmount());

    query.bindValue(":type",
                    (int)transaction.getType());

    query.bindValue(":status",
                    transaction.getStatus());

    query.bindValue(":date",
                    transaction.getDateTime());

    query.bindValue(":id",
                    transaction.getTransactionId());

    if(!query.exec())
    {
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}

bool TransactionRepository::deleteTransaction(int transactionId)
{
    QSqlQuery query(db);

    query.prepare(
        "DELETE FROM Transaction "
        "WHERE TransactionID=:id");

    query.bindValue(":id", transactionId);

    if(!query.exec())
    {
        qDebug() << query.lastError().text();
        return false;
    }

    return true;
}

QList<Transaction> TransactionRepository::getAllTransactions()
{
    QList<Transaction> list;

    QSqlQuery query(db);

    query.exec(
        "SELECT * FROM Transaction "
        "ORDER BY Date DESC");

    while(query.next())
    {
        Transaction t;

        t.setTransactionId(query.value("TransactionID").toInt());
        t.setCustomerId(query.value("CustomerID").toInt());
        t.setAmount(query.value("Amount").toDouble());

        t.setType(
            (Transaction::Type)
            query.value("Type").toInt());

        t.setStatus(query.value("Status").toString());

        t.setDateTime(query.value("Date").toDateTime());

        list.append(t);
    }

    return list;
}

QList<Transaction> TransactionRepository::getTransactionsByCustomer(int customerId)
{
    QList<Transaction> list;

    QSqlQuery query(db);

    query.prepare(
        "SELECT * FROM Transaction "
        "WHERE CustomerID=:customer "
        "ORDER BY Date DESC");

    query.bindValue(":customer", customerId);

    query.exec();

    while(query.next())
    {
        Transaction t;

        t.setTransactionId(query.value("TransactionID").toInt());
        t.setCustomerId(query.value("CustomerID").toInt());
        t.setAmount(query.value("Amount").toDouble());

        t.setType(
            (Transaction::Type)
            query.value("Type").toInt());

        t.setStatus(query.value("Status").toString());

        t.setDateTime(query.value("Date").toDateTime());

        list.append(t);
    }

    return list;
}

Transaction TransactionRepository::getTransactionById(int transactionId)
{
    Transaction t;

    QSqlQuery query(db);

    query.prepare(
        "SELECT * FROM Transaction "
        "WHERE TransactionID=:id");

    query.bindValue(":id", transactionId);

    if(query.exec())
    {
        if(query.next())
        {
            t.setTransactionId(query.value("TransactionID").toInt());
            t.setCustomerId(query.value("CustomerID").toInt());
            t.setAmount(query.value("Amount").toDouble());

            t.setType(
                (Transaction::Type)
                query.value("Type").toInt());

            t.setStatus(query.value("Status").toString());

            t.setDateTime(query.value("Date").toDateTime());
        }
    }

    return t;
}