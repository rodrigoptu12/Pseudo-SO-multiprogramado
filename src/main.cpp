#include <chrono>
#include <iostream>

#include "dispatcher/dispatcher.h"
#include "utils/utils.h"

int main(int argc, char const *argv[]) {
  auto startTime = std::chrono::high_resolution_clock::now();
  ProgramArguments programArguments = parseProgramArguments(argc, argv);

  Dispatcher dispatcher(programArguments.processesFileName, programArguments.filesFileName);

  dispatcher.run();
  
  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

  std::cout << "Tempo de execução: " << duration << " ms" << std::endl;
  return 0;
}