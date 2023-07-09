#include "memory_manager.h"

std::vector<int> MemoryManager::userProcessMemory(USER_PROCESS_MEMORY_SIZE, -1);
std::vector<int> MemoryManager::rtProcessMemory(RT_PROCESS_MEMORY_SIZE, -1);

bool MemoryManager::isMemoryAvailable(int blocks, int priority, int* offset) {
  if (priority == 0) {
    // Check if there is enough contiguous memory for the process
    for (int i = 0; i < RT_PROCESS_MEMORY_SIZE; i++) {
      if (rtProcessMemory[i] == -1) {
        int j = i;  // j is the index of the first non-null element
        // Find the index of the last non-null element
        while (rtProcessMemory[j] == -1 && j < RT_PROCESS_MEMORY_SIZE) {
          j++;
        }
        if (j - i >= blocks) {  // If there is enough contiguous memory, return true
          *offset = i;  // Return the offset of the memory where the process will be allocated
          return true;
        }
        i = j;
      }
    }
  } else {
    // Check if there is enough contiguous memory for the process
    for (int i = 0; i < USER_PROCESS_MEMORY_SIZE; i++) {
      if (userProcessMemory[i] == -1) {
        int j = i;  // j is the index of the first non-null element
        // Find the index of the last non-null element
        while (userProcessMemory[j] == -1 && j < USER_PROCESS_MEMORY_SIZE) {
          j++;
        }
        if (j - i >= blocks) {  // If there is enough contiguous memory, return true
          *offset = i;  // Return the offset of the memory where the process will be allocated
          return true;
        }
        i = j;
      }
    }
  }

  return false;
}

int MemoryManager::addProcessToMemory(int blocks, int priority, int offset) {
  if (priority == 0) {
    for (int i = offset; i < offset + blocks; i++) {
      rtProcessMemory[i] = 1;
    }
  } else {
    for (int i = offset; i < offset + blocks; i++) {
      userProcessMemory[i] = 1;
    }
  }

  return offset;
}

void MemoryManager::removeProcessFromMemory(int blocks, int priority, int offset) {
  if (priority == 0) {
    for (int i = offset; i < offset + blocks; i++) {
      rtProcessMemory[i] = -1;
    }
  } else {
    for (int i = offset; i < offset + blocks; i++) {
      userProcessMemory[i] = -1;
    }
  }
}
