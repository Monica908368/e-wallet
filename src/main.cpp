#include "PageAndOperationManager.h"

int main()
{
    std::string usersFile = "/home/monica/nti/cpp/project/my_project/users.csv";
    std::string transactionsFile = "/home/monica/nti/cpp/project/my_project/transactions.csv";
    PageAndOperationManager m(usersFile, transactionsFile);
    m.run();
}