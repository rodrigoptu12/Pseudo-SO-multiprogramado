#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>  // cout, endl

#include "../memory/memory_manager.h"

// struct to store process waiting to be allocated in memory
struct WaitingProcess {
  int pid;
  int startTimestamp;
  int priority;
  int cpuTime;
  int allocatedBlocks;
  int requiredPrinterCode;
  int isScannerUsed;
  int isModemUsed;
  int diskNumber;
};

// class to store process information, it is created only when process is allocated in memory
class Process {
 private:
  static int pidCounter;  // counter of process IDs

  int pid;                  // process ID
  int startTimestamp;       // timestamp when process was created
  int priority;             // priority of process
  int cpuTime;              // CPU time used by process
  int allocatedBlocks;      // number of allocated memory blocks
  int requiredPrinterCode;  // code of required printer
  int isScannerUsed;        // if process uses scanner
  int isModemUsed;          // if process uses modem
  int diskNumber;           // number of disk used by process

  // attributes below are not passed by constructor
  int timeInCPU;          // time spent in CPU
  int memoryOffset;       // offset of memory block
  bool printerAllocated;  // if printer is allocated
  bool scannerAllocated;  // if scanner is allocated
  bool driverAllocated;   // if driver is allocated
  bool modemAllocated;    // if modem is allocated
 public:
  Process(int startTimestamp, int priority, int cpuTime, int allocatedBlocks,
          int requiredPrinterCode, int isScannerUsed, int isModemUsed, int diskNumber);
  ~Process();
  int getPID() const;
  int getStartTimestamp() const;
  int getPriority() const;
  int getCPUTime() const;
  int getAllocatedBlocks() const;
  int getRequiredPrinterCode() const;
  int getIsScannerUsed() const;
  int getIsModemUsed() const;
  int getDiskNumber() const;

  void updateCPUTimeByQuantum(int quantum);
  void setPrinterAllocated(bool printerAllocated);
  void setScannerAllocated(bool scannerAllocated);
  void setDriverAllocated(bool driverAllocated);
  void setModemAllocated(bool modemAllocated);
  void setPriority(int priority);

  bool getPrinterAllocated() const;
  bool getScannerAllocated() const;
  bool getDriverAllocated() const;
  bool getModemAllocated() const;
  int getTimeInCPU() const;

  bool hasAllocatedResources() const;  // verify if process has allocated resources
  bool hasFinished() const;            // verify if process has finished

  void processInfo() const;  // print process info
};

#endif  // PROCESS_H
