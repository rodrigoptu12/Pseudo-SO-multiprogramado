#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "../process/process.h"
#include "../file/file_manager.h"
#include "../process/process_manager.h"

class Dispatcher {
 private:

 public:
 
  Dispatcher(const char* processesFileName, const char* filesFileName);
  void dispatch(Process process);
  

  void run();
};

#endif  // DISPATCHER_H
