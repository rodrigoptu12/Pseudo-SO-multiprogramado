#include "memory_manager.h"

int MemoryManager::rtProcessMemory = 0;
int MemoryManager::userProcessMemory = 0;

bool MemoryManager::isMemoryAvailable(Process& process) {
  if (process.getPriority() == 0) {
    return process.getAllocatedBlocks() <= getRTProcessMemoryAvailable();
  } else {
    return process.getAllocatedBlocks() <= getUserProcessMemoryAvailable();
  }
}

bool MemoryManager::isMemoryRequestValid(Process& process) {
  if (process.getPriority() == 0) {
    return process.getAllocatedBlocks() <= RT_PROCESS_MEMORY_SIZE;
  } else {
    return process.getAllocatedBlocks() <= USER_PROCESS_MEMORY_SIZE;
  }
}

void MemoryManager::addProcessToMemory(int blocks, int ProcessMemory) { ProcessMemory += blocks; }
void MemoryManager::removeProcessFromMemory(int blocks, int ProcessMemory) {
  ProcessMemory -= blocks;
}

int MemoryManager::getUserProcessMemoryAvailable() {
  return USER_PROCESS_MEMORY_SIZE - userProcessMemory;
}
int MemoryManager::getRTProcessMemoryAvailable() {
  return RT_PROCESS_MEMORY_SIZE - rtProcessMemory;
}
