#include "queues.h"

std::queue<Process*> Queues::realTimeQueue;
std::queue<Process*> Queues::userQueue1;
std::queue<Process*> Queues::userQueue2;
std::queue<Process*> Queues::userQueue3;

std::queue<Process*> Queues::printer1Queue;
std::queue<Process*> Queues::printer2Queue;
std::queue<Process*> Queues::scannerQueue;
std::queue<Process*> Queues::driver1Queue;
std::queue<Process*> Queues::driver2Queue;
std::queue<Process*> Queues::modemQueue;

Process* Queues::getNextProcess() {
  if (!realTimeQueue.empty()) {
    Process* process = realTimeQueue.front();
    realTimeQueue.pop();
    return process;
  } else if (!userQueue1.empty()) {
    Process* process = userQueue1.front();
    userQueue1.pop();
    return process;
  } else if (!userQueue2.empty()) {
    Process* process = userQueue2.front();
    userQueue2.pop();
    return process;
  } else if (!userQueue3.empty()) {
    Process* process = userQueue3.front();
    userQueue3.pop();
    return process;
  }
  throw std::runtime_error("All queues are empty");
}

void Queues::setGlobalQueue(std::vector<Process*> processes) {
  for (Process* process : processes) {
    addToReadyQueue(process);
  }
}

void Queues::addToReadyQueue(Process* process) {
  switch (process->getPriority()) {
    case 0:
      realTimeQueue.push(process);
      break;
    case 1:
      userQueue1.push(process);
      break;
    case 2:
      userQueue2.push(process);
      break;
    case 3:
      userQueue3.push(process);
      break;
  }
}

bool Queues::isEmpty() {
  return realTimeQueue.empty() && userQueue1.empty() && userQueue2.empty() && userQueue3.empty();
}

void Queues::addToPrinter1Queue(Process* process) { printer1Queue.push(process); }

void Queues::addToPrinter2Queue(Process* process) { printer2Queue.push(process); }

void Queues::addToScannerQueue(Process* process) { scannerQueue.push(process); }

void Queues::addToDriver1Queue(Process* process) { driver1Queue.push(process); }

void Queues::addToDriver2Queue(Process* process) { driver2Queue.push(process); }

void Queues::addToModemQueue(Process* process) { modemQueue.push(process); }

bool Queues::isPrinter1QueueEmpty() { return printer1Queue.empty(); }

bool Queues::isPrinter2QueueEmpty() { return printer2Queue.empty(); }

bool Queues::isScannerQueueEmpty() { return scannerQueue.empty(); }

bool Queues::isDriver1QueueEmpty() { return driver1Queue.empty(); }

bool Queues::isDriver2QueueEmpty() { return driver2Queue.empty(); }

bool Queues::isModemQueueEmpty() { return modemQueue.empty(); }

Process* Queues::getNextPrinter1Process() {
  if (printer1Queue.empty()) throw std::runtime_error("Printer 1 queue is empty");
  Process* process = printer1Queue.front();
  printer1Queue.pop();
  return process;
}

Process* Queues::getNextPrinter2Process() {
  if (printer2Queue.empty()) throw std::runtime_error("Printer 2 queue is empty");
  Process* process = printer2Queue.front();
  printer2Queue.pop();
  return process;
}

Process* Queues::getNextScannerProcess() {
  if (scannerQueue.empty()) throw std::runtime_error("Scanner queue is empty");
  Process* process = scannerQueue.front();
  scannerQueue.pop();
  return process;
}

Process* Queues::getNextDriver1Process() {
  if (driver1Queue.empty()) throw std::runtime_error("Driver 1 queue is empty");
  Process* process = driver1Queue.front();
  driver1Queue.pop();
  return process;
}

Process* Queues::getNextDriver2Process() {
  if (driver2Queue.empty()) throw std::runtime_error("Driver 2 queue is empty");
  Process* process = driver2Queue.front();
  driver2Queue.pop();
  return process;
}

Process* Queues::getNextModemProcess() {
  if (modemQueue.empty()) throw std::runtime_error("Modem queue is empty");
  Process* process = modemQueue.front();
  modemQueue.pop();
  return process;
}
