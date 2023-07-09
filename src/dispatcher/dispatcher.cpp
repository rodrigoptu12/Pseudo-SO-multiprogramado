#include "dispatcher.h"

#include <iostream>

Dispatcher::Dispatcher(const char* processesFileName, const char* filesFileName) {
  ProcessManager::loadInitFile(processesFileName);
  FileManager::loadInitFile(filesFileName);
}

void Dispatcher::run() {
  // get processes
  std::vector<Process*>* processes = ProcessManager::getProcesses();

  // print pid from processes

  Queues::setGlobalQueue(*processes);  // sort processes by start timestamp
  for (Process* process : *processes) {
    std::cout << process->getPID() << std::endl;
  }

  FileOperationsResult fileOperationsResult = FileManager::executeFileOperations();

  // run processes in queues
  ProcessManager::runProcesses();

  // print file operations result fileOperationsResult.fileOperationResults
  int operationCounter = 1;
  for (FileOperationResult fileOperationResult : fileOperationsResult.fileOperationResults) {
    std::string successMessage = "Operacao " + std::to_string(operationCounter) + " => Sucesso";
    std::string failMessage = "Operacao " + std::to_string(operationCounter) + " => Falha";
    std::cout << (fileOperationResult.success ? successMessage : failMessage) << std::endl;
    std::cout << fileOperationResult.message << std::endl;
    operationCounter++;
  }
}
