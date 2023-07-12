#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// split string by splitter
std::vector<std::string> split(std::string str, char splitter);

struct ProgramArguments {
  const char* processesFileName;
  const char* filesFileName;
};

// parse program arguments
ProgramArguments parseProgramArguments(int argc, char const* argv[]);

// function to parse files file removing empty lines, spaces and invalid lines (lines that don't
// match any expected pattern)
std::string parseFilesFile(const char* fileFileName);
// function to parse processes file removing empty lines, spaces and invalid lines (lines that don't
// match any expected pattern)
std::string parseProcessesFile(const char* processesFileName);

bool compare(const std::string& a, const std::string& b);

std::string sortByTimeStamp (std::string fileContent);


#endif  // UTILS_H