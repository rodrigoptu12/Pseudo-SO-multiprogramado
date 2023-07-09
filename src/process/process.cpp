#include "process.h"

int Process::pidCounter = 0;

Process::Process(int startTimestamp, int priority, int cpuTime, int allocatedBlocks,
                 int requiredPrinterCode, int isScannerUsed, int isModemUsed, int diskNumber) {
  this->pid = pidCounter++;  // increment pidCounter and assign to pid
  this->startTimestamp = startTimestamp;
  this->priority = priority;
  this->cpuTime = cpuTime;
  this->allocatedBlocks = allocatedBlocks;
  this->requiredPrinterCode = requiredPrinterCode;
  this->isScannerUsed = isScannerUsed;
  this->isModemUsed = isModemUsed;
  this->diskNumber = diskNumber;

  this->memoryOffset = 0;
  this->printerAllocated = (requiredPrinterCode == 0 ? true : false);
  this->scannerAllocated = (isScannerUsed == 0 ? true : false);
  this->driverAllocated = (diskNumber == 0 ? true : false);
  this->modemAllocated = (isModemUsed == 0 ? true : false);
  // MemoryManager::isMemoryAvailable(allocatedBlocks, priority, &memoryOffset);
  // MemoryManager::addProcessToMemory(allocatedBlocks, priority, memoryOffset);
}

Process::~Process() {
  // MemoryManager::removeProcessFromMemory(allocatedBlocks, priority, memoryOffset);
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

void Process::decreaseCPUTimeByQuantum(int quantum) {
  this->cpuTime -= quantum;
  if (this->cpuTime < 0) this->cpuTime = 0;
}

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

bool Process::hasAllocatedResources() const {
  return this->printerAllocated && this->scannerAllocated && this->driverAllocated &&
         this->modemAllocated;
}

bool Process::hasFinished() const { return this->cpuTime == 0; }