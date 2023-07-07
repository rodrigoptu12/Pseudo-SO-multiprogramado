#include "process_manager.h"

std::vector<Process> ProcessManager::processes;

void ProcessManager::loadInitFile(const char *processFileName) {
  // open file
  std::ifstream process_file(processFileName);
  if (!process_file.is_open()) throw std::runtime_error("Error opening process file");

  std::string line;

  while (std::getline(process_file, line)) {
    // split line by comma
    std::vector<std::string> lineVector = split(line, ',');

    int startTimestamp = std::stoi(lineVector[0]);
    int priority = std::stoi(lineVector[1]);
    int cpuTime = std::stoi(lineVector[2]);
    int allocatedBlocks = std::stoi(lineVector[3]);
    int requiredPrinterCode = std::stoi(lineVector[4]);
    int isScannerUsed = std::stoi(lineVector[5]);
    int isModemUsed = std::stoi(lineVector[6]);
    int diskNumber = std::stoi(lineVector[7]);

    Process process(startTimestamp, priority, cpuTime, allocatedBlocks, requiredPrinterCode,
                    isScannerUsed, isModemUsed, diskNumber);
    processes.push_back(process);
  }

  process_file.close();
}

std::vector<Process> ProcessManager::getProcesses() { return processes; }

int ProcessManager::getProcessPriority(int pid) {
  for (Process process : processes) {
    if (process.getPID() == pid) return process.getPriority();
  }
  return -1;
}

bool ProcessManager::processExists(int pid) {
  for (Process process : processes) {
    if (process.getPID() == pid) return true;
  }
  return false;
}

void ProcessManager::sortProcessesByPriority() {
  // 0 should be the highest priority
  std::sort(processes.begin(), processes.end(),
            [](Process a, Process b) { return a.getPriority() < b.getPriority(); });
}

void ProcessManager::runProcess(Process *process) {
  // should run process for QUANTUM milliseconds

  // verify if process needs resources
  if (process->getRequiredPrinterCode() != 0) {
    // process needs printer
    bool printerAvailable = Resources::getAvailablePrinter(process->getRequiredPrinterCode());

    if (printerAvailable) {
      // printer is available
      Resources::usePrinter(process->getRequiredPrinterCode());
      process->setPrinterUsage(true);
    } else {
      // printer is not available
      // put process in printer queue
      Queues::addPrinterQueue(process->getRequiredPrinterCode(), process->getPID());
      return;
    }
  }
  // colocar outras filas

  // run process for QUANTUM milliseconds
  if (process->getPriority() == 0) {
    while (process->getCPUTime() > 0) process->decreaseCPUTime();
  } else {
    process->decreaseCPUTime();
  }
}

void ProcessManager::runProcesses() {
  for (Process process : processes) {
    runProcess(&process);

    // verify if process has finished
    if (process.getCPUTime() == 0) {
      if (process.getRequiredPrinterCode() != 0) {
        // process used printer
        Resources::freePrinter(process.getRequiredPrinterCode());


      }
      // liberar recursos, verificar filas de recursos e liberar memória

      // remove process from processes
      processes.erase(std::remove(processes.begin(), processes.end(), process), processes.end());
    }
  }
}