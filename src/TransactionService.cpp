#include "TransactionService.h"
#include <iostream>

TransactionService::TransactionService(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser)
    : m_FilePath(FilePath), m_UserRepo(FilePath), m_TransactionFilePath(TrasactionFilePath), m_TransactionRepo(TrasactionFilePath), m_CurrentUser(currentuser) {}
TransactionService::~TransactionService() = default;
bool TransactionService::MakeTransaction(double mount, std::string &receiverName) { if (m_CurrentUser.balance < mount)
        {
            throw balance_not_enough();
        }
        User receiver;
        try
        {
            receiver = m_UserRepo.GetUserByName(receiverName);
        }
        catch (const std::exception &e)
        {
            throw not_found_receiver_exception();
        }
        m_CurrentUser.balance -= mount;
        receiver.balance += mount;
        m_UserRepo.UpdateUser(m_CurrentUser);
        m_UserRepo.UpdateUser(receiver);
        m_TransactionRepo.AddTransaction(m_CurrentUser.id, receiver.id, mount);
        return true;
    }
bool TransactionService::ShowUserTransactionHistory(long long userId) { return m_TransactionRepo.GetUserTransactions(userId); }
