#pragma once
#include "Pages.h"

class PageAndOperationManager
{
public:
    PageAndOperationManager(std::string &FilePath, std::string &TrasactionFilePath);
    ~PageAndOperationManager();
    void run();

private:
    std::string &m_FilePath;
    std::string &m_TransactionFilePath;
    User m_CurrentUser;
};