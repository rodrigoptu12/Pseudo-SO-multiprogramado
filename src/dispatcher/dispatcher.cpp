#include "dispatcher.h"

#include <iostream>

Dispatcher::Dispatcher(const char* processesFileName, const char* filesFileName) {
  ProcessManager::loadInitFile(processesFileName);
  FileManager::loadInitFile(filesFileName);
}

void Dispatcher::run() {

  // run processes in queues
  ProcessManager::runProcesses();

  FileOperationsResult fileOperationsResult = FileManager::executeFileOperations();
  // print file operations result fileOperationsResult.fileOperationResults
  // if operation failed print in red color and if success print in green color
  int operationCounter = 1;
  for (FileOperationResult fileOperationResult : fileOperationsResult.fileOperationResults) {
    // set color
    std::cout << "\033[";
    if (fileOperationResult.success)
      std::cout << "32m";  // green
    else
      std::cout << "31m";  // red

    // print message
    std::cout << "Operacao " << operationCounter << " => "
              << (fileOperationResult.success ? "Sucesso" : "Falha") << std::endl;
    std::cout << fileOperationResult.message << std::endl;
    // reset color
    std::cout << "\033[0m";
    operationCounter++;
  }

  // print map of files
  FileManager::printBlocks();
}
