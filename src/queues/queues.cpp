#include "queues.h"

void Queues::addToRealTimeQueue(const Process& process) { realTimeQueue.push(process); }

void Queues::addToUserQueue1(const Process& process) { userQueue1.push(process); }

void Queues::addToUserQueue2(const Process& process) { userQueue2.push(process); }

void Queues::addToUserQueue3(const Process& process) { userQueue3.push(process); }

Process Queues::getNextProcess() {
  if (!realTimeQueue.empty()) {
    Process process = realTimeQueue.front();
    realTimeQueue.pop();
    return process;
  } else if (!userQueue1.empty()) {
    Process process = userQueue1.front();
    userQueue1.pop();
    return process;
  } else if (!userQueue2.empty()) {
    Process process = userQueue2.front();
    userQueue2.pop();
    return process;
  } else if (!userQueue3.empty()) {
    Process process = userQueue3.front();
    userQueue3.pop();
    return process;
  }
}

void Queues::setQueue(const std::vector<Process>& processes) {
  for (auto process : processes) {
    if (process.getPriority() == 0) {
      addToRealTimeQueue(process);
    } else if (process.getPriority() == 1) {
      addToUserQueue1(process);
    } else if (process.getPriority() == 2) {
      addToUserQueue2(process);
    } else if (process.getPriority() == 3) {
      addToUserQueue3(process);
    }
  }
}

bool Queues::isEmpty() {
  return realTimeQueue.empty() && userQueue1.empty() && userQueue2.empty() && userQueue3.empty();
}

void Queues::addToPrinter1Queue(const Process& process) { printer1Queue.push(process); }

void Queues::addToPrinter2Queue(const Process& process) { printer2Queue.push(process); }

void Queues::addToScannerQueue(const Process& process) { scannerQueue.push(process); }

void Queues::addToDriver1Queue(const Process& process) { driver1Queue.push(process); }

void Queues::addToDriver2Queue(const Process& process) { driver2Queue.push(process); }

void Queues::addToModemQueue(const Process& process) { modemQueue.push(process); }

bool Queues::isPrinter1QueueEmpty() { return printer1Queue.empty(); }

bool Queues::isPrinter2QueueEmpty() { return printer2Queue.empty(); }

bool Queues::isScannerQueueEmpty() { return scannerQueue.empty(); }

bool Queues::isDriver1QueueEmpty() { return driver1Queue.empty(); }

bool Queues::isDriver2QueueEmpty() { return driver2Queue.empty(); }

bool Queues::isModemQueueEmpty() { return modemQueue.empty(); }

Process Queues::getNextPrinter1Process() {
  if (!printer1Queue.empty()) {
    Process process = printer1Queue.front();
    printer1Queue.pop();
    return process;
  }
}

Process Queues::getNextPrinter2Process() {
  if (!printer2Queue.empty()) {
    Process process = printer2Queue.front();
    printer2Queue.pop();
    return process;
  }
}

Process Queues::getNextScannerProcess() {
  if (!scannerQueue.empty()) {
    Process process = scannerQueue.front();
    scannerQueue.pop();
    return process;
  }
}

Process Queues::getNextDriver1Process() {
  if (!driver1Queue.empty()) {
    Process process = driver1Queue.front();
    driver1Queue.pop();
    return process;
  }
}

Process Queues::getNextDriver2Process() {
  if (!driver2Queue.empty()) {
    Process process = driver2Queue.front();
    driver2Queue.pop();
    return process;
  }
}

Process Queues::getNextModemProcess() {
  if (!modemQueue.empty()) {
    Process process = modemQueue.front();
    modemQueue.pop();
    return process;
  }
}
