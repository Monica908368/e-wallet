#pragma once
#include "User.h"
#include <string>

class UserRepository
{
public:
UserRepository(std::string &FilePath);
virtual ~UserRepository() = default;
virtual User GetUserById(long long id) = 0;
virtual User GetUserByName(std::string &name) = 0;
virtual void UpdateUser(const User &user) = 0;

protected:
std::string &m_FilePath;
};

class UserRepositoryCSV : public UserRepository
{
public:
UserRepositoryCSV(std::string &FilePath);
~UserRepositoryCSV() override;
User GetUserById(long long id) override;
User GetUserByName(std::string &name) override;
void UpdateUser(const User &user) override;
};

