#include "UserService.h"
#include <thread>
#include <iostream>



UserService::UserService(std::string &FilePath, User &currentuser) : m_FilePath(FilePath), m_Repository(FilePath), m_CurrentUser(currentuser) {}
UserService::~UserService() = default;
bool UserService::GetCurrentUserByName(std::string name) { 
    try
        {
            m_CurrentUser = m_Repository.GetUserByName(name);
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return false;
        }  }
bool UserService::CheckPassword(std::string password) { return m_CurrentUser.password == password; }
User UserService::GetCurrentUser() const { return m_CurrentUser; }

