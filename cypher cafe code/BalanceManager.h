#ifndef BALANCEMANAGER_H
#define BALANCEMANAGER_H

class BalanceManager
{
public:
    BalanceManager();

    // Get current balance
    double getBalance() const;

    // Set balance
    void setBalance(double amount);

    // Increase balance
    bool increaseBalance(double amount);

    // Decrease balance
    bool decreaseBalance(double amount);

    // Check enough money
    bool hasEnoughBalance(double amount) const;

    // Reset balance
    void resetBalance();

private:
    double balance;
};

#endif // BALANCEMANAGER_H