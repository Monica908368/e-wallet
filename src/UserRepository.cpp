#include "UserRepository.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>

UserRepository::UserRepository(std::string &FilePath) : m_FilePath(FilePath) {}

UserRepositoryCSV::UserRepositoryCSV(std::string &FilePath) : UserRepository(FilePath) {}
UserRepositoryCSV::~UserRepositoryCSV() = default;

User UserRepositoryCSV::GetUserById(long long id)
{
std::fstream file(m_FilePath);
if (!file.is_open() || file.peek() == std::ifstream::traits_type::eof())
{
throw file_exception();
}
std::string line;
while (std::getline(file, line))
{if(line.empty()) continue;
if(line.empty()) continue;
std::istringstream ss_line(line);
User user;
std::string container;
std::getline(ss_line, container, ',');
user.id = std::stoll(container);
if (user.id == id)
{
std::getline(ss_line, container, ',');
user.username = container;
std::getline(ss_line, container, ',');
user.balance = std::stod(container);
std::getline(ss_line, user.password, ',');
file.close();
return user;
}
}
file.close();
throw not_found_exception();
}

User UserRepositoryCSV::GetUserByName(std::string &name)
{
std::fstream file(m_FilePath);
if (!file.is_open() || file.peek() == std::ifstream::traits_type::eof())
{
throw file_exception();
}
std::string line;
while (std::getline(file, line))
{ if(line.empty()) continue;
std::istringstream ss_line(line);
User user;
std::string container;
std::getline(ss_line, container, ',');
user.id = std::stoll(container);
std::getline(ss_line, container, ',');
user.username = container;
if (user.username == name)
{
std::getline(ss_line, container, ',');
user.balance = std::stod(container);
std::getline(ss_line, user.password, ',');
file.close();
return user;
}
}
file.close();
throw not_found_exception();
}

void UserRepositoryCSV::UpdateUser(const User &user)
{
std::fstream file(m_FilePath);
if (!file.is_open() || file.peek() == std::ifstream::traits_type::eof())
{

throw file_exception();
}
std::string line;
std::ofstream tempFile("temp.csv");
bool found = false;
while (std::getline(file, line))
{ if(line.empty()) continue;
std::istringstream ss_line(line);
std::string string_id;
std::getline(ss_line, string_id, ',');
long long id = std::stoll(string_id);
if (id == user.id)
{
tempFile << user.id << "," << user.username << "," << user.balance << "," << user.password << "\n";
found = true;
}
else
{
tempFile << line << "\n";
}
}
file.close();
tempFile.close();
std::remove("last_version.csv");
std::rename(m_FilePath.c_str(), "last_version.csv");
std::rename("temp.csv", m_FilePath.c_str());
if (!found)
{
throw not_found_exception();
}
}

