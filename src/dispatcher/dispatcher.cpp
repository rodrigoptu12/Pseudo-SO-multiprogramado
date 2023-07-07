#include "dispatcher.h"

Dispatcher::Dispatcher(const char* processesFileName, const char* filesFileName) {
  ProcessManager::loadInitFile(processesFileName);
  FileManager::loadInitFile(filesFileName);
}

void Dispatcher::dispatch(Process process) {
  // Implementação do despachante
  std::cout << "Dispatching process " << process.getPID() << std::endl;
}

void Dispatcher::run() {
  // Implementação do escalonador
  std::cout << "Running dispatcher" << std::endl;
  std::vector<Process> processes = ProcessManager::getProcesses();
  for (int i = 0; i < processes.size(); i++) {
    dispatch(processes[i]);
  }
  
}
