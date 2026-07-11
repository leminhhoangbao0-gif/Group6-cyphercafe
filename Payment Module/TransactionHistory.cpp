#include "TransactionHistory.h"
#include "ui_TransactionHistory.h"

#include <QTableWidgetItem>
#include <QMessageBox>

TransactionHistory::TransactionHistory(TransactionRepository *repo,
                                       QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TransactionHistory)
{
    ui->setupUi(this);

    repository = repo;

    ui->tableWidget->setColumnCount(6);

    ui->tableWidget->setHorizontalHeaderLabels(
    {
        "ID",
        "Customer",
        "Amount",
        "Type",
        "Status",
        "Date"
    });

    loadTransactions();
}

TransactionHistory::~TransactionHistory()
{
    delete ui;
}

QString TransactionHistory::typeToString(Transaction::Type type)
{
    switch(type)
    {
    case Transaction::TopUp:
        return "Top Up";

    case Transaction::Payment:
        return "Payment";

    case Transaction::Refund:
        return "Refund";
    }

    return "";
}

void TransactionHistory::loadTransactions()
{
    QList<Transaction> list =
            repository->getAllTransactions();

    ui->tableWidget->setRowCount(list.size());

    for(int i=0;i<list.size();i++)
    {
        Transaction t = list.at(i);

        ui->tableWidget->setItem(i,0,
                new QTableWidgetItem(
                    QString::number(
                        t.getTransactionId())));

        ui->tableWidget->setItem(i,1,
                new QTableWidgetItem(
                    QString::number(
                        t.getCustomerId())));

        ui->tableWidget->setItem(i,2,
                new QTableWidgetItem(
                    QString::number(
                        t.getAmount(),'f',0)));

        ui->tableWidget->setItem(i,3,
                new QTableWidgetItem(
                    typeToString(
                        t.getType())));

        ui->tableWidget->setItem(i,4,
                new QTableWidgetItem(
                    t.getStatus()));

        ui->tableWidget->setItem(i,5,
                new QTableWidgetItem(
                    t.getDateTime().toString(
                        "dd/MM/yyyy hh:mm")));
    }

    ui->tableWidget->resizeColumnsToContents();
}

void TransactionHistory::on_btnRefresh_clicked()
{
    loadTransactions();
}

void TransactionHistory::on_btnReceipt_clicked()
{
    int row = ui->tableWidget->currentRow();

    if(row < 0)
    {
        QMessageBox::warning(
                    this,
                    "Warning",
                    "Please select a transaction.");

        return;
    }

    int id = ui->tableWidget
            ->item(row,0)
            ->text()
            .toInt();

    Transaction t =
            repository->getTransactionById(id);

    QMessageBox::information(
                this,
                "Receipt",
                t.generateReceipt());
}