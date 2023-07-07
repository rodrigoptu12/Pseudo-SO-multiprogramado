#include <iostream>

#include "file/file_manager.h"
#include "process/process_manager.h"

int main(int argc, char const *argv[]) {
  ProgramArguments programArguments = parseProgramArguments(argc, argv);

  ProcessManager::loadInitFile(programArguments.processesFileName);
  FileManager::loadInitFile(programArguments.filesFileName);

  return 0;
}