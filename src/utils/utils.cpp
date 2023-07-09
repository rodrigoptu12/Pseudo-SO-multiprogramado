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

/*
for (Process process : processes) {
    std::cout << "PID: " << process.getPID() << std::endl;
    std::cout << "Start Timestamp: " << process.getStartTimestamp() << std::endl;
    std::cout << "Priority: " << process.getPriority() << std::endl;
    std::cout << "CPU Time: " << process.getCPUTime() << std::endl;
    std::cout << "Allocated Blocks: " << process.getAllocatedBlocks() << std::endl;
    std::cout << "Required Printer Code: " << process.getRequiredPrinterCode() << std::endl;
    std::cout << "Is Scanner Used: " << process.getIsScannerUsed() << std::endl;
    std::cout << "Is Modem Used: " << process.getIsModemUsed() << std::endl;
    std::cout << "Disk Number: " << process.getDiskNumber() << std::endl;

    // Para imprimir os atributos adicionais que não são passados pelo construtor
    std::cout << "Printer Allocated: " << process.getPrinterAllocated() << std::endl;
    std::cout << "Scanner Allocated: " << process.getScannerAllocated() << std::endl;
    std::cout << "Driver Allocated: " << process.getDriverAllocated() << std::endl;
    std::cout << "Modem Allocated: " << process.getModemAllocated() << std::endl;

    std::cout << std::endl;
  }
*/
