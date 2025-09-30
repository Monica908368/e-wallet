#pragma once
#include <string>
#include <exception>

// User struct
struct User
{
std::string username;
std::string password;
long long id;
double balance;
};

// Exceptions
class not_found_exception : public std::exception
{
public:
const char *what() const noexcept override;
};

class file_exception : public std::exception
{
public:
const char *what() const noexcept override;
};

class not_found_receiver_exception : public std::exception
{
public:
const char *what() const noexcept override;
};

class balance_not_enough : public std::exception
{
public:
const char *what() const noexcept override;
};

// Utility
void clearScreen();

