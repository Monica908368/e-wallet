#pragma once
#include "User.h"
#include <vector>

class TansactionRepository
{
public:
    TansactionRepository(std::string TrasactionFilePath);
    virtual ~TansactionRepository();
    virtual void AddTransaction(long long senderId, long long receiverId, double amount) = 0;
    virtual bool GetUserTransactions(long long userId) = 0;

protected:
    std::string m_TransactionFilePath;
};

class TansactionRepositoryCsv : public TansactionRepository
{
public:
    TansactionRepositoryCsv(std::string TrasactionFilePath);
    ~TansactionRepositoryCsv() override;
    void AddTransaction(long long senderId, long long receiverId, double amount) override;
    bool GetUserTransactions(long long userId) override;
};

