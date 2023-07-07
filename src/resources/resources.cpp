#include "resources.h"

std::vector<bool> Resources::availablePrinters = {true, true};
bool Resources::availableScanners = true;
std::vector<bool> Resources::availableDrivers = {true, true};
bool Resources::availableModems = true;

bool Resources::getAvailablePrinter(int printerId) { return availablePrinters[printerId];} 

bool Resources::getAvailableScanners() { return availableScanners; }

bool Resources::getAvailableDriver(int driverId) { return availableDrivers[driverId]; }

bool Resources::getAvailableModems() { return availableModems; }

void Resources::usePrinter(int printerId) {
  if (!availablePrinters[printerId]) {
    throw std::runtime_error("No printers available");
  }
  availablePrinters[printerId] = false;
}

void Resources::useScanner() {
  if (!availableScanners) {
    throw std::runtime_error("No scanners available");
  }
  availableScanners = false;
}

void Resources::useDriver(int driverId) {
  if (!availableDrivers[driverId]) {
    throw std::runtime_error("No drivers available");
  }
  availablePrinters[driverId] = false;
}

void Resources::useModem() {
  if (!availableModems) {
    throw std::runtime_error("No modems available");
  }
  availableModems = false;
}

void Resources::freePrinter(int printerId) {
  if (availablePrinters[printerId]) {
    throw std::runtime_error("No printers to free");
  }
  availablePrinters[printerId] = true;
}

void Resources::freeScanner() {
  if (availableScanners) {
    throw std::runtime_error("No scanners to free");
  }
  availableScanners = true;
}

void Resources::freeDriver(int driverId) {
  if (availableDrivers[driverId]) {
    throw std::runtime_error("No drivers to free");
  }
  availableDrivers[driverId] = true;
}

void Resources::freeModem() {
  if (availableModems) {
    throw std::runtime_error("No modems to free");
  }
  availableModems = true;
}
