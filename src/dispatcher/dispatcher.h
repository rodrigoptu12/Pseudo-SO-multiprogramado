#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "../file/file_manager.h"
#include "../process/process_manager.h"

class Dispatcher {
 public:
  Dispatcher(const char* processesFileName, const char* filesFileName);

  void run();
};

#endif  // DISPATCHER_H
