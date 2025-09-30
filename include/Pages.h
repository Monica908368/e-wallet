#pragma once
#include "UserService.h"
#include "TransactionService.h"
#include <string>
#include <memory>


class Page
{
public:
    Page(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser);
    virtual ~Page();
    virtual std::unique_ptr<Page> handle() = 0;

protected:
    std::string &m_FilePath;
    std::string &m_TransactionFilePath;
    User &m_CurrentUser;
};

class CheckBalancePage : public Page
{
public:
    CheckBalancePage(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser);
    std::unique_ptr<Page> handle() override;
};

class TransactionPage : public Page
{
public:
    TransactionPage(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser);
    std::unique_ptr<Page> handle() override;
};

class TransactionHestoryPage : public Page
{
public:
    TransactionHestoryPage(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser);
    std::unique_ptr<Page> handle() override;
};

class ServicesPage : public Page
{
public:
    ServicesPage(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser);
    std::unique_ptr<Page> handle() override;
};

class LoginPagePassword : public Page
{
public:
    LoginPagePassword(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser);
    std::unique_ptr<Page> handle() override;
};

class LoginPageName : public Page
{
public:
    LoginPageName(std::string &FilePath, std::string &TrasactionFilePath, User &currentuser);
    std::unique_ptr<Page> handle() override;
};