#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#define RT_PROCESS_MEMORY_SIZE 64
#define USER_PROCESS_MEMORY_SIZE 960

#include <vector>

class MemoryManager {
 private:
  static std::vector<int> userProcessMemory;  // int will be the pid of the process
  static std::vector<int> rtProcessMemory;    // int will be the pid of the process

 public:
  // Verifica se há memória suficiente disponível para o processo especificado.
  // Se o processo for em tempo real (prioridade 0), ele verifica a memória do processo em tempo
  // real. Se o processo for um processo do usuário (prioridade diferente de 0), ele verifica a
  // memória do processo do usuário.
  static bool isMemoryAvailable(int blocks, int priority, int* offset);

  // Verifica se o tamanho do processo é maior que o tamanho da memória.
  static bool isProcessSizeGreaterThanMemorySize(int blocks, int priority);

  // Adiciona o processo à memória e retorna o offset da memória onde o processo foi alocado.
  static int addProcessToMemory(int blocks, int priority, int offset);

  // Remove o processo da memória.
  static void removeProcessFromMemory(int blocks, int priority, int offset);
};

#endif