#include "utils.h"

std::vector<std::string> split(std::string str, char splitter) {
  std::vector<std::string> result;
  std::stringstream ss(str);
  std::string token;

  while (std::getline(ss, token, splitter)) {
    result.push_back(token);
  }

  return result;
}

ProgramArguments parseProgramArguments(int argc, char const *argv[]) {
  if (argc != 3) {
    std::cout << "Usage: ./main <processes.txt> <files.txt>" << std::endl;
    exit(1);
  }

  ProgramArguments programArguments;
  programArguments.processesFileName = argv[1];
  programArguments.filesFileName = argv[2];

  return programArguments;
}