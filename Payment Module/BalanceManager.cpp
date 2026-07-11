#include "BalanceManager.h"

BalanceManager::BalanceManager()
{
    balance = 0.0;
}

double BalanceManager::getBalance() const
{
    return balance;
}

void BalanceManager::setBalance(double amount)
{
    if(amount >= 0)
        balance = amount;
}

bool BalanceManager::increaseBalance(double amount)
{
    if(amount <= 0)
        return false;

    balance += amount;
    return true;
}

bool BalanceManager::decreaseBalance(double amount)
{
    if(amount <= 0)
        return false;

    if(balance < amount)
        return false;

    balance -= amount;
    return true;
}

bool BalanceManager::hasEnoughBalance(double amount) const
{
    return balance >= amount;
}

void BalanceManager::resetBalance()
{
    balance = 0.0;
}