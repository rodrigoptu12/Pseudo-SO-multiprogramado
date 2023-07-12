#include "utils.h"

std::regex reNumber("[0-9]+");                      // regex to match numbers
std::regex reFile("[a-zA-Z], ?[0-9]+, ?[0-9]+ *");  // regex to match files lines ex: A, 1, 2 <name,
                                                    // start block, quantity blocks>
std::regex reAddFileOperation(
    "[0-9]+, ?[0-9]+, ?[a-zA-Z], ?[0-9]+ *");  // regex to match add file operation lines ex: 1, 0,
                                               // A, 2 <process, operation, file, quantity blocks>
std::regex reRemoveFileOperation(
    "[0-9]+, ?[0-9]+, ?[a-zA-Z] *");  // regex to match remove file operation lines ex: 1, 1, A
                                      // <process, operation, file>

// regex to match process lines ex: 1, 0, 0, 0, 0, 0, 0, 0 <start time, priority, cpu time, memory,
// size, printers, scanners, modems, cds>
std ::regex reProcess("[0-9]+, ?[0-9]+, ?[0-9]+, ?[0-9]+, ?[0-9]+, ?[0-9]+, ?[0-9]+, ?[0-9]+ *");

std::vector<std::string> split(std::string str, char splitter) {
  std::vector<std::string> result;
  std::stringstream ss(str);
  std::string token;

  while (std::getline(ss, token, splitter)) {
    result.push_back(token);
  }

  return result;
}

ProgramArguments parseProgramArguments(int argc, char const* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: ./main <processes.txt> <files.txt>" << std::endl;
    exit(1);
  }

  ProgramArguments programArguments;
  programArguments.processesFileName = argv[1];
  programArguments.filesFileName = argv[2];

  return programArguments;
}

std::string parseFilesFile(const char* fileFileName) {
  // open file
  std::ifstream files_file(fileFileName);
  if (!files_file.is_open()) throw std::runtime_error("Error opening files file");
  std::string line;

  std::string fileContent = "";

  // remove lines that don't match any regex
  while (std::getline(files_file, line)) {
    // if line matches any regex, add it to file content
    if (std::regex_match(line, reNumber) || std::regex_match(line, reFile) ||
        std::regex_match(line, reAddFileOperation) ||
        std::regex_match(line, reRemoveFileOperation)) {
      // remove spaces from line
      line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
      fileContent += line + "\n";
    }
  }

  // remove last \n
  fileContent.pop_back();

  // close file
  files_file.close();

  return fileContent;
}

std::string parseProcessesFile(const char* processesFileName) {
  // open file
  std::ifstream processes_file(processesFileName);
  if (!processes_file.is_open()) throw std::runtime_error("Error opening processes file");
  std::string line;

  std::string fileContent = "";

  // remove lines that don't match any regex
  while (std::getline(processes_file, line)) {
    // if line matches any regex, add it to file content
    if (std::regex_match(line, reProcess)) {
      // remove spaces from line
      line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
      fileContent += line + "\n";
    }
  }

  // remove last \n
  fileContent.pop_back();

  // close file
  processes_file.close();

  return fileContent;
}

bool compare(const std::string& a, const std::string& b) {
    std::istringstream ss_a(a), ss_b(b);
    int num_a, num_b;
    ss_a >> num_a;
    ss_b >> num_b;
    return num_a < num_b; 
}

std::string sortByTimeStamp (std::string fileContent) {
std::vector<std::string> linhas;
  std::stringstream ss(fileContent);
  std::string linha;
  while (std::getline(ss, linha, '\n')) {
    linhas.push_back(linha);
  }
  std::sort(linhas.begin(), linhas.end(), compare);
  std::string sortedFileContent;
  for (std::string linha : linhas) {
    sortedFileContent += linha + "\n";
  }
  return sortedFileContent;
}