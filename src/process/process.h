#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>  // cout, endl

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
  int memoryOffset;   // offset of memory block
  bool printerUsage;  // if process uses printer
  bool scannerUsage;  // if process uses scanner
  bool driverUsage;   // if process uses driver
  bool modemUsage;    // if process uses modem
 public:
  Process(int startTimestamp, int priority, int cpuTime, int allocatedBlocks,
          int requiredPrinterCode, int isScannerUsed, int isModemUsed, int diskNumber);
  int getPID() const;
  int getStartTimestamp() const;
  int getPriority() const;
  int getCPUTime() const;
  int getAllocatedBlocks() const;
  int getRequiredPrinterCode() const;
  int getIsScannerUsed() const;
  int getIsModemUsed() const;
  int getDiskNumber() const;

  void decreaseCPUTime();  // decrease CPU time by 1 ms
  void setPrinterUsage(bool printerUsage);
  void setScannerUsage(bool scannerUsage);
  void setDriverUsage(bool driverUsage);
  void setModemUsage(bool modemUsage);
};

#endif  // PROCESS_H
