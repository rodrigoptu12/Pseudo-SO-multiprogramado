#include "process.h"

int Process::pidCounter = 0;

Process::Process(int startTimestamp, int priority, int cpuTime, int allocatedBlocks,
                 int requiredPrinterCode, int isScannerUsed, int isModemUsed, int diskNumber) {
  this->pid = pidCounter;
  this->startTimestamp = startTimestamp;
  this->priority = priority;
  this->cpuTime = cpuTime;
  this->allocatedBlocks = allocatedBlocks;
  this->requiredPrinterCode = requiredPrinterCode;
  this->isScannerUsed = isScannerUsed;
  this->isModemUsed = isModemUsed;
  this->diskNumber = diskNumber;

  this->memoryOffset = 0;
  this->timeInCPU = 0;
  this->printerAllocated = false;
  this->scannerAllocated = false;
  this->driverAllocated = false;
  this->modemAllocated = false;

  // Check if process size is greater than memory size and throw exception if it is (process will
  // not be allocated)
  if (MemoryManager::isProcessSizeGreaterThanMemorySize(allocatedBlocks, priority)) {
    throw std::runtime_error("PROCESS_SIZE_GREATER_THAN_MEMORY_SIZE");
  }

  // Allocate memory for process
  if (MemoryManager::isMemoryAvailable(allocatedBlocks, priority, &memoryOffset)) {
    MemoryManager::addProcessToMemory(allocatedBlocks, priority, memoryOffset);
  } else {
    throw std::runtime_error("NOT_ENOUGH_MEMORY_AVAILABLE_AT_THE_MOMENT");
  }
  pidCounter++;  // increment process ID counter for next process
}

Process::~Process() {
  MemoryManager::removeProcessFromMemory(this->allocatedBlocks, this->priority, this->memoryOffset);
}

int Process::getPID() const { return this->pid; }

int Process::getStartTimestamp() const { return this->startTimestamp; }

int Process::getPriority() const { return this->priority; }

int Process::getCPUTime() const { return this->cpuTime; }

int Process::getAllocatedBlocks() const { return this->allocatedBlocks; }

int Process::getRequiredPrinterCode() const { return this->requiredPrinterCode; }

int Process::getIsScannerUsed() const { return this->isScannerUsed; }

int Process::getIsModemUsed() const { return this->isModemUsed; }

int Process::getDiskNumber() const { return this->diskNumber; }

void Process::updateCPUTimeByQuantum(int quantum) { this->timeInCPU += quantum; }

void Process::setPrinterAllocated(bool printerAllocated) {
  this->printerAllocated = printerAllocated;
}

void Process::setScannerAllocated(bool scannerAllocated) {
  this->scannerAllocated = scannerAllocated;
}

void Process::setPriority(int priority) { this->priority = priority; }

void Process::setDriverAllocated(bool driverAllocated) { this->driverAllocated = driverAllocated; }

void Process::setModemAllocated(bool modemAllocated) { this->modemAllocated = modemAllocated; }

bool Process::getPrinterAllocated() const { return this->printerAllocated; }

bool Process::getScannerAllocated() const { return this->scannerAllocated; }

bool Process::getDriverAllocated() const { return this->driverAllocated; }

bool Process::getModemAllocated() const { return this->modemAllocated; }

int Process::getTimeInCPU() const { return this->timeInCPU; }

bool Process::hasAllocatedResources() const {
  bool printerAllocated = this->requiredPrinterCode == 0 ? true : this->printerAllocated;
  bool scannerAllocated = this->isScannerUsed == 0 ? true : this->scannerAllocated;
  bool driverAllocated = this->diskNumber == 0 ? true : this->driverAllocated;
  bool modemAllocated = this->isModemUsed == 0 ? true : this->modemAllocated;

  return printerAllocated && scannerAllocated && driverAllocated && modemAllocated;
}

bool Process::hasFinished() const { return this->timeInCPU >= this->cpuTime; }

void Process::processInfo() const {
  std::cout << "  PID: " << this->pid << std::endl;
  std::cout << "  offset: " << this->memoryOffset << std::endl;
  std::cout << "  blocks: " << this->allocatedBlocks << std::endl;
  std::cout << "  priority: " << this->priority << std::endl;
  std::cout << "  time: " << this->cpuTime << std::endl;
  std::cout << "  printers: " << this->requiredPrinterCode << std::endl;
  std::cout << "  scanners: " << this->isScannerUsed << std::endl;
  std::cout << "  modems: " << this->isModemUsed << std::endl;
  std::cout << "  drives: " << this->diskNumber << std::endl;
  std::cout << "  Extra info: " << std::endl;
  std::cout << "    printerAllocated: " << this->printerAllocated << std::endl;
  std::cout << "    scannerAllocated: " << this->scannerAllocated << std::endl;
  std::cout << "    driverAllocated: " << this->driverAllocated << std::endl;
  std::cout << "    modemAllocated: " << this->modemAllocated << std::endl;
  std::cout << "    timeInCPU: " << this->timeInCPU << std::endl;
}