#include "PageAndOperationManager.h"
#include <iostream>
PageAndOperationManager::PageAndOperationManager(std::string &FilePath, std::string &TrasactionFilePath)
    : m_FilePath(FilePath), m_TransactionFilePath(TrasactionFilePath) {}
PageAndOperationManager::~PageAndOperationManager() = default;
void PageAndOperationManager::run() {  
    std::unique_ptr<Page> current = std::make_unique<LoginPageName>(m_FilePath, m_TransactionFilePath, m_CurrentUser);
        while (current)
        {
            clearScreen();
            current = current->handle();
        }
        
    }