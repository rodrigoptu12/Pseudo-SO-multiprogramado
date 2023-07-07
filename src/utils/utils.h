#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <sstream>
#include <string>
#include <iostream>

// split string by splitter
std::vector<std::string> split(std::string str, char splitter);

struct ProgramArguments {
  const char* processesFileName;
  const char* filesFileName;
};

// parse program arguments
ProgramArguments parseProgramArguments(int argc, char const *argv[]);

#endif  // UTILS_H