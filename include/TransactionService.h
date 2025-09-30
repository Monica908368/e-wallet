#pragma once
#include "TransactionRepository.h"
#include "UserService.h"

class TransactionService
{
public:
    TransactionService(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser);
    ~TransactionService();
    bool MakeTransaction(double mount, std::string &receiverName);
    bool ShowUserTransactionHistory(long long userId);

private:
    UserRepositoryCSV m_UserRepo;
    TansactionRepositoryCsv m_TransactionRepo;
    std::string &m_FilePath;
    std::string &m_TransactionFilePath;
    User &m_CurrentUser;
};

