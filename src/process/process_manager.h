#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <algorithm>  // sort
#include <chrono>     // chrono
#include <fstream>    // ifstream
#include <vector>     // vector

#include "../queues/queues.h"
#include "../resources/resources.h"
#include "../utils/utils.h"  // split
#include "process.h"

#define QUANTUM 1

enum ProcessState { READY = 0, RUNNING = 1, BLOCKED = 2, FINISHED = 3 };

class ProcessManager {
 private:
  static std::vector<Process*> processes;  // processes of process manager

  static ProcessState verifyResources(
      Process *process);  // verify if process has the required resources

  static void releaseResources(Process *process);  // release resources of process

  static void allocateResourcesToProcessesInQueues();  // allocate resources to processes in queues

  static void rotatePriority(Process *process);  // rotate priority of process

 public:
  static void loadInitFile(const char *processFileName);

  static std::vector<Process*>* getProcesses();

  static int getProcessPriority(int pid);

  static bool processExists(int pid);

  static ProcessState runProcess(Process *process);

  static void runProcesses();
};

#endif  // PROCESS_MANAGER_H