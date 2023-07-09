#ifndef QUEUES_H
#define QUEUES_H

#include <queue>
#include <stdexcept>  // runtime_error

#include "../process/process.h"

class Queues {
 private:
  static std::queue<Process*> realTimeQueue;
  static std::queue<Process*> userQueue1;
  static std::queue<Process*> userQueue2;
  static std::queue<Process*> userQueue3;

  static std::queue<Process*> printer1Queue;
  static std::queue<Process*> printer2Queue;
  static std::queue<Process*> scannerQueue;
  static std::queue<Process*> driver1Queue;
  static std::queue<Process*> driver2Queue;
  static std::queue<Process*> modemQueue;

 public:
  // Rersources queues
  static void addToPrinter1Queue(Process* process);
  static void addToPrinter2Queue(Process* process);
  static void addToScannerQueue(Process* process);
  static void addToDriver1Queue(Process* process);
  static void addToDriver2Queue(Process* process);
  static void addToModemQueue(Process* process);

  static bool isPrinter1QueueEmpty();
  static bool isPrinter2QueueEmpty();
  static bool isScannerQueueEmpty();
  static bool isDriver1QueueEmpty();
  static bool isDriver2QueueEmpty();
  static bool isModemQueueEmpty();

  static Process* getNextPrinter1Process();
  static Process* getNextPrinter2Process();
  static Process* getNextScannerProcess();
  static Process* getNextDriver1Process();
  static Process* getNextDriver2Process();
  static Process* getNextModemProcess();

  // Process queues
  static void addToReadyQueue(Process* process);
  static bool isEmpty();
  static Process* getNextProcess();

  // Set queues
  static void setGlobalQueue(std::vector<Process*> processes);
};

#endif  // QUEUES_H
