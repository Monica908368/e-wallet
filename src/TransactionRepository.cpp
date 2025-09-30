#include "TransactionRepository.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
TansactionRepository::TansactionRepository(std::string TrasactionFilePath) : m_TransactionFilePath(TrasactionFilePath) {}
TansactionRepository::~TansactionRepository() = default;

TansactionRepositoryCsv::TansactionRepositoryCsv(std::string TrasactionFilePath) : TansactionRepository(TrasactionFilePath) {}
TansactionRepositoryCsv::~TansactionRepositoryCsv() = default;
void TansactionRepositoryCsv::AddTransaction(long long senderId, long long receiverId, double amount) {  std::ofstream file(m_TransactionFilePath, std::ios::app);
        if (!file.is_open())
        {
            throw file_exception();
        }
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        char buffer[100];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now_time));

        file << senderId << "," << receiverId << "," << amount << "," << buffer << "\n";
        file.close();
     }
bool TansactionRepositoryCsv::GetUserTransactions(long long userId) {  bool AnyTransaction = false;
        std::ifstream file(m_TransactionFilePath);
        if (!file.is_open())
        {
            throw file_exception();
        }
        std::string line;
        while (std::getline(file, line))
        {   if(line.empty()) continue;
            std::istringstream ss_line(line);
            std::string container;
            long long senderId, receiverId;
            double amount;
            std::string timestamp;
            std::getline(ss_line, container, ',');
            senderId = std::stoll(container);
            std::getline(ss_line, container, ',');
            receiverId = std::stoll(container);
            std::getline(ss_line, container, ',');
            amount = std::stod(container);
            std::getline(ss_line, timestamp);
            if (senderId == userId || receiverId == userId)
            {
                AnyTransaction = true;
                std::cout << "Sender ID: " << senderId << ", Receiver ID: " << receiverId << ", Amount: " << amount <<", time: "<< timestamp<<std::endl;
            }
        }
        file.close();
        return AnyTransaction;
     }