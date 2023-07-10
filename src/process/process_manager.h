#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <algorithm>  // sort
#include <chrono>     // chrono
#include <fstream>    // ifstream
#include <thread>     // this_thread::sleep_for
#include <vector>     // vector

#include "../file/file_manager.h"
#include "../queues/queues.h"
#include "../resources/resources.h"
#include "../utils/utils.h"  // split
#include "process.h"

#define QUANTUM 1
#define CHRONO_1MS std::chrono::milliseconds(QUANTUM)

enum ProcessState { READY = 0, RUNNING = 1, BLOCKED = 2, FINISHED = 3 };

class ProcessManager {
 private:
  static std::vector<Process *> processes;  // processes of process manager

  static ProcessState verifyResources(Process *process);  // verify if process has the  resources

  static void releaseResources(Process *process);  // release resources of process

  static void allocateResourcesToProcessesInQueues();  // allocate resources to processes in queues

  static void rotatePriority(Process *process);  // rotate priority of process

  static void sortProcessesByStartTimestamp();  // sort processes by start timestamp

  static void deleteProcess(int pid);

  static int createProcess(int startTimestamp, int priority, int cpuTime, int allocatedBlocks,
                           int requiredPrinterCode, int isScannerUsed, int isModemUsed,
                           int diskNumber);

  static bool verifyPrintersResource(Process *process);
  static bool verifyScannersResource(Process *process);
  static bool verifyDriversResource(Process *process);
  static bool verifyModemsResource(Process *process);

  static ProcessState runProcess(Process *process);

  static std::vector<Process *> *getProcesses();

  static Process *getProcess(int pid);

 public:
  static void loadInitFile(const char *processFileName);

  static int getProcessPriority(int pid);

  static bool processExists(int pid);

  // create process and add to ready queue
  static int createProcessesAndAddToReadyQueue(int startTimestamp, int priority, int cpuTime,
                                               int allocatedBlocks, int requiredPrinterCode,
                                               int isScannerUsed, int isModemUsed, int diskNumber);

  static void runProcesses();
};

#endif  // PROCESS_MANAGER_H