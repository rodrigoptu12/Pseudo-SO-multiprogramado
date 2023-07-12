#include "process_manager.h"

std::vector<Process *> ProcessManager::processes;

void ProcessManager::loadInitFile(const char *processFileName) {
  // open file
  std::string fileContent = parseProcessesFile(processFileName);  // parse file
  std::istringstream process_file(fileContent);  // convert content to stream to read line by line

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

    createProcess(startTimestamp, priority, cpuTime, allocatedBlocks, requiredPrinterCode,
                  isScannerUsed, isModemUsed, diskNumber);
  }

  // sort processes by start timestamp
  sortProcessesByStartTimestamp();
  Queues::setGlobalQueue(processes);
}

void ProcessManager::sortProcessesByStartTimestamp() {
  std::sort(processes.begin(), processes.end(), [](Process *process1, Process *process2) -> bool {
    return process1->getStartTimestamp() < process2->getStartTimestamp();
  });
}

int ProcessManager::createProcess(int startTimestamp, int priority, int cpuTime,
                                  int allocatedBlocks, int requiredPrinterCode, int isScannerUsed,
                                  int isModemUsed, int diskNumber) {
  try {
    Process *process = new Process(startTimestamp, priority, cpuTime, allocatedBlocks,
                                   requiredPrinterCode, isScannerUsed, isModemUsed, diskNumber);

    processes.push_back(process);
    return process->getPID();
  } catch (std::runtime_error &e) {
    if (strcmp(e.what(), "NOT_ENOUGH_MEMORY_AVAILABLE_AT_THE_MOMENT") == 0) {
      WaitingProcess *waitingProcess = new WaitingProcess;
      waitingProcess->startTimestamp = startTimestamp;
      waitingProcess->priority = priority;
      waitingProcess->cpuTime = cpuTime;
      waitingProcess->allocatedBlocks = allocatedBlocks;
      waitingProcess->requiredPrinterCode = requiredPrinterCode;
      waitingProcess->isScannerUsed = isScannerUsed;
      waitingProcess->isModemUsed = isModemUsed;
      waitingProcess->diskNumber = diskNumber;

      Queues::addToWaitMemoryQueue(waitingProcess);
      // process will be created later
      return -1;  // error creating process, not enough memory available
    }
    // process will not be created
    return -1;  // error creating process, process size is greater than memory size
  }
}

void ProcessManager::deleteProcess(int pid) {
  Process *process = nullptr;
  for (long unsigned int i = 0; i < processes.size(); i++) {
    if (processes[i]->getPID() == pid) {
      process = processes[i];
      processes.erase(processes.begin() + i);
      break;
    }
  }
  if (process != nullptr) delete process;
  FileManager::removePIDFromFilesOwner(pid);
}

int ProcessManager::createProcessesAndAddToReadyQueue(int startTimestamp, int priority, int cpuTime,
                                                      int allocatedBlocks, int requiredPrinterCode,
                                                      int isScannerUsed, int isModemUsed,
                                                      int diskNumber) {
  int pid = createProcess(startTimestamp, priority, cpuTime, allocatedBlocks, requiredPrinterCode,
                          isScannerUsed, isModemUsed, diskNumber);
  if (pid != -1) {
    Process *process = getProcess(pid);

    ProcessState processState = verifyResources(process);  // if has resources, process is ready

    if (processState == READY) {
      Queues::addToReadyQueue(process);
    }
  }
  return pid;
}

Process *ProcessManager::getProcess(int pid) {
  for (Process *process : processes) {
    if (process->getPID() == pid) return process;
  }
  return nullptr;
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
    while (!process->hasFinished()) {
      process->updateCPUTimeByQuantum(QUANTUM);
      std::this_thread::sleep_for(CHRONO_1MS);  // simulate process running
      std::cout << "  P" << process->getPID() << " instruction "
                << process->getTimeInCPU() / QUANTUM << std::endl;
    }

  } else {
    process->updateCPUTimeByQuantum(QUANTUM);
    std::this_thread::sleep_for(CHRONO_1MS);  // simulate process running
    std::cout << "  P" << process->getPID() << " instruction " << process->getTimeInCPU() / QUANTUM
              << std::endl;
  }

  return (process->hasFinished() ? FINISHED : READY);
}

void ProcessManager::runProcesses() {
  int previousPID = -1, color = 0;
  while (!Queues::isEmpty()) {
    Process *process = Queues::getNextProcess();

    ProcessState processState = verifyResources(process);  // if has resources, process is ready

    // change color of text if pid is different from previous pid
    // color alternates between blue (0) and green (1)
    if (process->getPID() != previousPID) {
      color = (color == 0 ? 1 : 0);
      previousPID = process->getPID();
    }
    std::cout << "\033[1;" << (color == 0 ? "34m" : "32m");

    std::cout << "dispatcher =>" << std::endl;
    process->processInfo();
    std::cout << std::endl;

    std::cout << "process " << process->getPID() << " =>" << std::endl;
    std::cout << "  P" << process->getPID() << " ";

    if (processState == READY) {
      std::cout << "STARTED" << std::endl;
      processState = runProcess(process);
    } else if (processState == BLOCKED) {
      std::cout << "BLOCKED" << std::endl;
    }

    switch (processState) {
      case READY:
        rotatePriority(process);
        Queues::addToReadyQueue(process);
        break;
      case FINISHED:
        std::cout << "  P" << process->getPID() << " return SIGINT" << std::endl;
        releaseResources(process);
        allocateResourcesToProcessesInQueues();
        deleteProcess(process->getPID());
        allocateMemoryToProcessesInQueueIfPossible();
        break;
      case BLOCKED:
        break;
      case RUNNING:
        break;
    }

    std::cout << "\033[0m";
    std::cout << "----------------------------------------" << std::endl;
  }
}

void ProcessManager::rotatePriority(Process *process) {
  switch (process->getPriority()) {
    break;
    case 2:
      process->setPriority(1);
      break;
    case 3:
      process->setPriority(2);
      break;
  }
}

// MEMORY METHODS
void ProcessManager::allocateMemoryToProcessesInQueueIfPossible() {
  // if there are waiting processes, try to allocate them
  if (!Queues::isWaitMemoryQueueEmpty()) {
    WaitingProcess *waitingProcess = Queues::getNextWaitMemoryProcess();
    int pid = createProcessesAndAddToReadyQueue(
        waitingProcess->startTimestamp, waitingProcess->priority, waitingProcess->cpuTime,
        waitingProcess->allocatedBlocks, waitingProcess->requiredPrinterCode,
        waitingProcess->isScannerUsed, waitingProcess->isModemUsed, waitingProcess->diskNumber);
    if (pid == -1) {  // process was not created
      Queues::addToWaitMemoryQueue(waitingProcess);
    } else {  // process was created
      delete waitingProcess;
    }
  }
}

// RESOURCES METHODS

void ProcessManager::allocateResourcesToProcessesInQueues() {
  // if printer 1 queue is not empty and printer 1 is available
  if (!Queues::isPrinter1QueueEmpty() && Resources::getAvailablePrinter(1)) {
    Process *process = Queues::getNextPrinter1Process();
    Resources::usePrinter(1);
    process->setPrinterAllocated(true);
    if (process->hasAllocatedResources()) Queues::addToReadyQueue(process);
  }
  // if printer 2 queue is not empty and printer 2 is available
  if (!Queues::isPrinter2QueueEmpty() && Resources::getAvailablePrinter(2)) {
    Process *process = Queues::getNextPrinter2Process();
    Resources::usePrinter(2);
    process->setPrinterAllocated(true);
    if (process->hasAllocatedResources()) Queues::addToReadyQueue(process);
  }
  // if scanner queue is not empty and scanner is available
  if (!Queues::isScannerQueueEmpty() && Resources::getAvailableScanners()) {
    Process *process = Queues::getNextScannerProcess();
    Resources::useScanner();
    process->setScannerAllocated(true);
    if (process->hasAllocatedResources()) Queues::addToReadyQueue(process);
  }
  // if driver 1 queue is not empty and driver 1 is available
  if (!Queues::isDriver1QueueEmpty() && Resources::getAvailableDriver(1)) {
    Process *process = Queues::getNextDriver1Process();
    Resources::useDriver(1);
    process->setDriverAllocated(true);
    if (process->hasAllocatedResources()) Queues::addToReadyQueue(process);
  }
  // if driver 2 queue is not empty and driver 2 is available
  if (!Queues::isDriver2QueueEmpty() && Resources::getAvailableDriver(2)) {
    Process *process = Queues::getNextDriver2Process();
    Resources::useDriver(2);
    process->setDriverAllocated(true);
    if (process->hasAllocatedResources()) Queues::addToReadyQueue(process);
  }
  // if modem queue is not empty and modem is available
  if (!Queues::isModemQueueEmpty() && Resources::getAvailableModems()) {
    Process *process = Queues::getNextModemProcess();
    Resources::useModem();
    process->setModemAllocated(true);
    if (process->hasAllocatedResources()) Queues::addToReadyQueue(process);
  }
}

void ProcessManager::releaseResources(Process *process) {
  // release printer
  if (process->getPrinterAllocated()) Resources::freePrinter(process->getRequiredPrinterCode());

  // release scanner
  if (process->getScannerAllocated()) Resources::freeScanner();

  // release driver
  if (process->getDriverAllocated()) Resources::freeDriver(process->getDiskNumber());

  // release modem
  if (process->getModemAllocated()) Resources::freeModem();
}

ProcessState ProcessManager::verifyResources(Process *process) {
  bool printerAvailable = verifyPrintersResource(process);
  bool scannerAvailable = verifyScannersResource(process);
  bool driverAvailable = verifyDriversResource(process);
  bool modemAvailable = verifyModemsResource(process);

  bool resourcesAvailable =
      printerAvailable && scannerAvailable && driverAvailable && modemAvailable;

  return resourcesAvailable ? READY : BLOCKED;
}

/*
 * Resources verification methods
 */
bool ProcessManager::verifyPrintersResource(Process *process) {
  if (process->getRequiredPrinterCode() == 0) {  // process does not require printer
    return true;
  } else if (!process->getPrinterAllocated()) {  // printer is not allocated
    bool printerAvailable = Resources::getAvailablePrinter(process->getRequiredPrinterCode());

    if (printerAvailable) {
      Resources::usePrinter(process->getRequiredPrinterCode());  // use printer
      process->setPrinterAllocated(true);                        // set printer as allocated
      return true;
    } else {
      switch (process->getRequiredPrinterCode()) {
        case 1:
          Queues::addToPrinter1Queue(process);  // add process to printer 1 queue
          break;
        case 2:
          Queues::addToPrinter2Queue(process);  // add process to printer 2 queue
          break;
      }
      return false;
    }
  }
  return true;
}

bool ProcessManager::verifyScannersResource(Process *process) {
  if (!process->getIsScannerUsed()) {  // process does not require scanner
    return true;
  } else if (!process->getScannerAllocated()) {  // scanner is not allocated
    bool scannerAvailable = Resources::getAvailableScanners();

    if (scannerAvailable) {
      Resources::useScanner();             // use scanner
      process->setScannerAllocated(true);  // set scanner as allocated
      return true;
    } else {
      Queues::addToScannerQueue(process);  // add process to scanner queue
      return false;
    }
  }
  return true;
}

bool ProcessManager::verifyDriversResource(Process *process) {
  if (process->getDiskNumber() == 0) {  // process does not require driver
    return true;
  } else if (!process->getDriverAllocated()) {  // driver is not allocated
    bool driverAvailable = Resources::getAvailableDriver(process->getDiskNumber());
    if (driverAvailable) {
      Resources::useDriver(process->getDiskNumber());  // use driver
      process->setDriverAllocated(true);               // set driver as allocated
      return true;
    } else {
      switch (process->getDiskNumber()) {
        case 1:
          Queues::addToDriver1Queue(process);  // add process to driver 1 queue
          break;
        case 2:
          Queues::addToDriver2Queue(process);  // add process to driver 2 queue
          break;
      }
      return false;
    }
  }
  return true;
}

bool ProcessManager::verifyModemsResource(Process *process) {
  if (!process->getIsModemUsed()) {  // process does not require modem
    return true;
  } else if (!process->getModemAllocated()) {  // modem is not allocated
    bool modemAvailable = Resources::getAvailableModems();

    if (modemAvailable) {
      Resources::useModem();             // use modem
      process->setModemAllocated(true);  // set modem as allocated
      return true;
    } else {
      Queues::addToModemQueue(process);  // add process to modem queue
      return false;
    }
  }
  return true;
}