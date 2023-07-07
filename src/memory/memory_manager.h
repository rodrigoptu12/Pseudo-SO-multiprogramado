#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "../process/process_manager.h"

#define RT_PROCESS_MEMORY_SIZE 64
#define USER_PROCESS_MEMORY_SIZE 960

class MemoryManager {
 private:
  static int userProcessMemory;
  static int rtProcessMemory;

  // Retorna a memória atual do processo do usuário.
  static int getUserProcessMemoryAvailable();

  // Retorna a memória atual do processo em tempo real.
  static int getRTProcessMemoryAvailable();

 public:
  // Verifica se há memória suficiente disponível para o processo especificado.
  // Se o processo for em tempo real (prioridade 0), ele verifica a memória do processo em tempo
  // real. Se o processo for um processo do usuário (prioridade diferente de 0), ele verifica a
  // memória do processo do usuário.
  static bool isMemoryAvailable(Process& process);

  // Verifica se a solicitação de memória do processo fornecido é válida.
  // Se o processo for em tempo real (prioridade 0), verifica se a requisição de memória não
  // excede o tamanho total da memória do processo em tempo real. Se o processo for um processo de
  // usuário (prioridade não 0), ele verifica se a solicitação de memória não excede o tamanho total
  // da memória do processo do usuário.
  static bool isMemoryRequestValid(Process& process);

  // Retorna o tamanho total da memória do processo
  static void addProcessToMemory(int blocks, int ProcessMemory);

  // Retorna o tamanho total da memória do processo
  static void removeProcessFromMemory(int blocks, int ProcessMemory);
};

#endif
