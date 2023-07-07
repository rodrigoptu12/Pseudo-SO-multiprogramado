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
  this->printerUsage = false;
  this->scannerUsage = false;
  this->driverUsage = false;
  this->modemUsage = false;
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

void Process::decreaseCPUTime() {
  this->cpuTime--;
  if (this->cpuTime < 0) this->cpuTime = 0;
}

void Process::setPrinterUsage(bool printerUsage) { this->printerUsage = printerUsage; }

void Process::setScannerUsage(bool scannerUsage) { this->scannerUsage = scannerUsage; }

void Process::setDriverUsage(bool driverUsage) { this->driverUsage = driverUsage; }

void Process::setModemUsage(bool modemUsage) { this->modemUsage = modemUsage; }