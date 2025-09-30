#pragma once
#include "User.h"
#include "UserRepository.h"

class UserService
{
public:
    UserService(std::string &FilePath, User &currentuser);
    ~UserService();
    bool GetCurrentUserByName(std::string name);
    bool CheckPassword(std::string password);
    User GetCurrentUser() const;

private:
    UserRepositoryCSV m_Repository;
    std::string &m_FilePath;
    User &m_CurrentUser;
};
