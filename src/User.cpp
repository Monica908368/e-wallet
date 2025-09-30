#include "User.h"
#include <iostream>
#include <cstdlib>

void clearScreen()
{
#ifdef _WIN32
system("cls");
#else
system("clear");
#endif
}

const char *not_found_exception::what() const noexcept
{
return "User not found";
}

const char *file_exception::what() const noexcept
{
return "File closed , empty or not exist ";
}

const char *not_found_receiver_exception::what() const noexcept
{
return "Receiver not found";
}

const char *balance_not_enough::what() const noexcept
{
return "You don't have enough balance";
}

