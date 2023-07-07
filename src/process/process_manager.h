#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <algorithm>  // sort
#include <fstream>    // ifstream
#include <vector>     // vector

#include "../utils/utils.h"  // split
#include "process.h"

#include "../resources/resources.h"
#include "../queues/queues.h"

#define QUANTUM 1  // 1 millisecond

class ProcessManager {
 private:
  static std::vector<Process> processes;  // processes of process manager

 public:
  static void loadInitFile(const char *processFileName);

  static std::vector<Process> getProcesses();
  static int getProcessPriority(int pid);
  static bool processExists(int pid);

  static void sortProcessesByPriority();

  static void runProcess(Process *process);

  static void runProcesses();
};

#endif  // PROCESS_MANAGER_H