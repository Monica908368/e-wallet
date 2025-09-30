#include "Pages.h"
#include <iostream>
#include <thread>
#include <chrono>
#include<memory>
Page::Page(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser) : m_FilePath(FilePath), m_TransactionFilePath(TrasactionFilePath), m_CurrentUser(currentuser) {}
Page::~Page() = default;

CheckBalancePage::CheckBalancePage(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser) : Page(FilePath, TrasactionFilePath, currentuser) {}
std::unique_ptr<Page> CheckBalancePage::handle() {  std::cout << "Your Balance equal " << m_CurrentUser.balance << std::endl;
        std::cout << "Enter(S)to chose another service or (Any other putton ) for quit: ";
        char choice;
        std::cin >> choice;
        if (choice == 'S' || choice == 's')
        {
            return std::make_unique<ServicesPage>(m_FilePath, m_TransactionFilePath, m_CurrentUser);
            ;
        }
        else
        {
            exit(0);
        } }


TransactionPage::TransactionPage(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser) : Page(FilePath, TrasactionFilePath, currentuser) {}
std::unique_ptr<Page> TransactionPage::handle() {
        TransactionService transaction(m_FilePath, m_TransactionFilePath, m_CurrentUser);
        std::string ReceiverUserName;
        double TransferredAmount;
        std::cout << "Enter the receiver username: ";
        std::cin >> ReceiverUserName;
        std::cout << "Enter the transferred amount: ";
        std::cin >> TransferredAmount;
        try
        {
            transaction.MakeTransaction(TransferredAmount, ReceiverUserName);
            std::cout << "The transfer was completed successfully" << std::endl;
            std::cout << "Enter(S)to chose another service or (Any other putton ) for quit:";
            char choice;
            std::cin >> choice;
            if (choice == 'S' || choice == 's')
            {
                return std::make_unique<ServicesPage>(m_FilePath, m_TransactionFilePath, m_CurrentUser);
                ;
            }
            else
            {
                exit(0);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return std::make_unique<TransactionPage>(m_FilePath, m_TransactionFilePath, m_CurrentUser);
        } }

TransactionHestoryPage::TransactionHestoryPage(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser) : Page(FilePath, TrasactionFilePath, currentuser) {}
std::unique_ptr<Page> TransactionHestoryPage::handle() { 
   
        TransactionService transaction(m_FilePath, m_TransactionFilePath, m_CurrentUser);
       try {
        if (!transaction.ShowUserTransactionHistory(m_CurrentUser.id)) {
            std::cout << "No previous transactions" << std::endl;
        }
    }
    catch (const file_exception& e) {
        std::cout<<"File closed or not exist"<<std::endl;
    }

        std::cout << "Enter(S)to chose another service or (Any other putton ) for quit: ";
        char choice;
        std::cin >> choice;
        if (choice == 'S' || choice == 's')
        {
            return std::make_unique<ServicesPage>(m_FilePath, m_TransactionFilePath, m_CurrentUser);
            
        }
        else
        {
            exit(0);
        } 
        
    }

ServicesPage::ServicesPage(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser) : Page(FilePath, TrasactionFilePath, currentuser) {}
std::unique_ptr<Page> ServicesPage::handle() 
    {
        std::cout << "Available Service" << std::endl;
        std::cout << "(T)Transaction" << std::endl;
        std::cout << "(B)Check Balance" << std::endl;
        std::cout << "(H)Transaction History" << std::endl;
        std::cout << "Your Choioce: ";
        char choice;
        std::cin >> choice;

        if (choice == 'T' || choice == 't')
        {
            return std::make_unique<TransactionPage>(m_FilePath, m_TransactionFilePath, m_CurrentUser);
        }
        else if (choice == 'B' || choice == 'b')
        {
            return std::make_unique<CheckBalancePage>(m_FilePath, m_TransactionFilePath, m_CurrentUser);
        }

        else if (choice == 'H' || choice == 'h')
        {
            return std::make_unique<TransactionHestoryPage>(m_FilePath, m_TransactionFilePath, m_CurrentUser);
        }
        else
        {
            std::cout << "Undifind choice.please only enter T,B or H" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return std::make_unique<ServicesPage>(m_FilePath, m_TransactionFilePath, m_CurrentUser);
        }
    }

LoginPagePassword::LoginPagePassword(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser) : Page(FilePath, TrasactionFilePath, currentuser) {}
std::unique_ptr<Page> LoginPagePassword::handle() { 
    std::cout << "==============WELLCOME==============" << std::endl;
        std::cout << "Enter your username: " << m_CurrentUser.username << std::endl;
        std::string password;
        std::cout<< "Enter your password: ";
        std::cin >> password;
        UserService userService(m_FilePath, m_CurrentUser);
        if (userService.CheckPassword(password))
        {
            return std::make_unique<ServicesPage>(m_FilePath, m_TransactionFilePath, m_CurrentUser);
        }
        else
        {
            std::cout << "Incorrect password" << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));
            return std::make_unique<LoginPagePassword>(m_FilePath, m_TransactionFilePath, m_CurrentUser);
        }
    } 

LoginPageName::LoginPageName(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser) : Page(FilePath, TrasactionFilePath, currentuser) {}
std::unique_ptr<Page> LoginPageName::handle() { std::cout << "==============WELLCOME==============" << std::endl;
        std::string name;
        std::cout << "Enter your username: ";
        std::cin >> name;
        UserService userService(m_FilePath, m_CurrentUser);
        if (userService.GetCurrentUserByName(name))
        {

            return std::make_unique<LoginPagePassword>(m_FilePath, m_TransactionFilePath, m_CurrentUser);
        }
        else
        {

            // std::cout << "User not found. Press Enter to try again.";
            return std::make_unique<LoginPageName>(m_FilePath, m_TransactionFilePath, m_CurrentUser);
        }
    }

