#include "process_manager.h"

std::vector<Process *> ProcessManager::processes;

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

    Process *process = new Process(startTimestamp, priority, cpuTime, allocatedBlocks,
                                   requiredPrinterCode, isScannerUsed, isModemUsed, diskNumber);

    processes.push_back(process);
  }

  process_file.close();
}

std::vector<Process *> *ProcessManager::getProcesses() { return &processes; }

int ProcessManager::getProcessPriority(int pid) {
  for (Process *process : processes) {
    if (process->getPID() == pid) return process->getPriority();
  }
  return -1;
}

bool ProcessManager::processExists(int pid) {
  for (Process *process : processes) {
    if (process->getPID() == pid) return true;
  }
  return false;
}

ProcessState ProcessManager::runProcess(Process *process) {
  if (process->getPriority() == 0) {
    while (!process->hasFinished()) process->decreaseCPUTimeByQuantum(QUANTUM);

  } else {
    process->decreaseCPUTimeByQuantum(QUANTUM);
  }

  return (process->hasFinished() ? FINISHED : READY);
}

void ProcessManager::runProcesses() {
  while (!Queues::isEmpty()) {
    Process *process = Queues::getNextProcess();

    // run process
    ProcessState processState =
        verifyResources(process);  // if process does not have required resources

    if (processState == READY) processState = runProcess(process);

    switch (processState) {
      case READY:
        rotatePriority(process);
        Queues::addToReadyQueue(process);
        break;
      case FINISHED:
        releaseResources(process);
        allocateResourcesToProcessesInQueues();
        // delete process
        for (long unsigned int i = 0; i < processes.size(); i++) {
          if (processes[i]->getPID() == process->getPID()) {
            processes.erase(processes.begin() + i);
            break;
          }
        }
        delete process;
        break;
      case BLOCKED:
        break;
      case RUNNING:
        break;
    }
  }
}

void ProcessManager::rotatePriority(Process *process) {
  switch (process->getPriority()) {
    break;
    case 1:
      process->setPriority(3);
      break;
    case 2:
      process->setPriority(1);
      break;
    case 3:
      process->setPriority(2);
      break;
  }
}

void ProcessManager::allocateResourcesToProcessesInQueues() {
  if (!Queues::isPrinter1QueueEmpty() && Resources::getAvailablePrinter(1)) {
    Process *process = Queues::getNextPrinter1Process();
    Resources::usePrinter(1);
    process->setPrinterAllocated(true);
    if (process->hasAllocatedResources()) Queues::addToReadyQueue(process);
  }

  if (!Queues::isPrinter2QueueEmpty() && Resources::getAvailablePrinter(2)) {
    Process *process = Queues::getNextPrinter2Process();
    Resources::usePrinter(2);
    process->setPrinterAllocated(true);
    if (process->hasAllocatedResources()) Queues::addToReadyQueue(process);
  }

  if (!Queues::isScannerQueueEmpty() && Resources::getAvailableScanners()) {
    Process *process = Queues::getNextScannerProcess();
    Resources::useScanner();
    process->setScannerAllocated(true);
    if (process->hasAllocatedResources()) Queues::addToReadyQueue(process);
  }

  if (!Queues::isDriver1QueueEmpty() && Resources::getAvailableDriver(1)) {
    Process *process = Queues::getNextDriver1Process();
    Resources::useDriver(1);
    process->setDriverAllocated(true);
    if (process->hasAllocatedResources()) Queues::addToReadyQueue(process);
  }

  if (!Queues::isDriver2QueueEmpty() && Resources::getAvailableDriver(2)) {
    Process *process = Queues::getNextDriver2Process();
    Resources::useDriver(2);
    process->setDriverAllocated(true);
    if (process->hasAllocatedResources()) Queues::addToReadyQueue(process);
  }

  if (!Queues::isModemQueueEmpty() && Resources::getAvailableModems()) {
    Process *process = Queues::getNextModemProcess();
    Resources::useModem();
    process->setModemAllocated(true);
    if (process->hasAllocatedResources()) Queues::addToReadyQueue(process);
  }
}

void ProcessManager::releaseResources(Process *process) {
  // release printer
  if (process->getPrinterAllocated()) {
    Resources::freePrinter(process->getRequiredPrinterCode());
  }

  // release scanner
  if (process->getScannerAllocated()) {
    Resources::freeScanner();
  }

  // release driver
  if (process->getDriverAllocated()) {
    Resources::freeDriver(process->getDiskNumber());
  }

  // release modem
  if (process->getModemAllocated()) {
    Resources::freeModem();
  }
}

ProcessState ProcessManager::verifyResources(Process *process) {
  bool resourcesAvailable = true;

  // verify if process has the required printer
  if (process->getRequiredPrinterCode() != 0 && !process->getPrinterAllocated()) {
    // get if printer is available
    bool printerAvailable = Resources::getAvailablePrinter(process->getRequiredPrinterCode());

    if (printerAvailable) {
      Resources::usePrinter(process->getRequiredPrinterCode());  // use printer
      process->setPrinterAllocated(true);                        // set printer as allocated
    } else {
      switch (process->getRequiredPrinterCode()) {
        case 1:
          Queues::addToPrinter1Queue(process);  // add process to printer 1 queue
          break;
        case 2:
          Queues::addToPrinter2Queue(process);  // add process to printer 2 queue
          break;
      }
      resourcesAvailable = false;
    }
  }

  // verify if process uses scanner
  if (process->getIsScannerUsed() && !process->getScannerAllocated()) {
    // process uses scanner
    bool scannerAvailable = Resources::getAvailableScanners();

    if (scannerAvailable) {
      Resources::useScanner();             // use scanner
      process->setScannerAllocated(true);  // set scanner as allocated
    } else {
      Queues::addToScannerQueue(process);  // add process to scanner queue
      resourcesAvailable = false;
    }
  }

  // verify if process uses driver
  if (process->getDiskNumber() != 0 && !process->getDriverAllocated()) {
    // process uses driver
    bool driverAvailable = Resources::getAvailableDriver(process->getDiskNumber());

    if (driverAvailable) {
      Resources::useDriver(process->getDiskNumber());  // use driver
      process->setDriverAllocated(true);               // set driver as allocated
    } else {
      switch (process->getDiskNumber()) {
        case 1:
          Queues::addToDriver1Queue(process);  // add process to driver 1 queue
          break;
        case 2:
          Queues::addToDriver2Queue(process);  // add process to driver 2 queue
          break;
      }
      resourcesAvailable = false;
    }
  }

  // verify if process uses modem
  if (process->getIsModemUsed() && !process->getModemAllocated()) {
    // process uses modem
    bool modemAvailable = Resources::getAvailableModems();

    if (modemAvailable) {
      Resources::useModem();             // use modem
      process->setModemAllocated(true);  // set modem as allocated
    } else {
      Queues::addToModemQueue(process);  // add process to modem queue
      resourcesAvailable = false;
    }
  }

  return resourcesAvailable ? READY : BLOCKED;
}
