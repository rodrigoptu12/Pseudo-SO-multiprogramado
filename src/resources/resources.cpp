#include "resources.h"

bool Resources::availablePrinters1 = true;
bool Resources::availablePrinters2 = true;
bool Resources::availableScanners = true;
bool Resources::availableDrivers1 = true;
bool Resources::availableDrivers2 = true;
bool Resources::availableModems = true;

bool Resources::getAvailablePrinter(int printerId) {
  if (printerId == 1)
    return availablePrinters1;

  else if (printerId == 2)
    return availablePrinters2;

  return false;
}

bool Resources::getAvailableScanners() { return availableScanners; }

bool Resources::getAvailableDriver(int driverId) {
  if (driverId == 1)
    return availableDrivers1;

  else if (driverId == 2)
    return availableDrivers2;

  return false;
}

bool Resources::getAvailableModems() { return availableModems; }

void Resources::usePrinter(int printerId) {
  if (printerId <= 0 || printerId > 2) throw std::runtime_error("Invalid printer ID");

  if (printerId == 1)
    availablePrinters1 = false;
  else if (printerId == 2)
    availablePrinters2 = false;
}

void Resources::useScanner() {
  if (!availableScanners) throw std::runtime_error("No scanners available");

  availableScanners = false;
}

void Resources::useDriver(int driverId) {
  if (driverId <= 0 || driverId > 2) throw std::runtime_error("Invalid driver ID");

  if (driverId == 1)
    availableDrivers1 = false;
  else if (driverId == 2)
    availableDrivers2 = false;
}

void Resources::useModem() {
  if (!availableModems) throw std::runtime_error("No modems available");
  availableModems = false;
}

void Resources::freePrinter(int printerId) {
  if (printerId <= 0 || printerId > 2) throw std::runtime_error("Invalid printer ID");
  if (printerId == 1)
    availablePrinters1 = true;
  else if (printerId == 2)
    availablePrinters2 = true;
}

void Resources::freeScanner() { availableScanners = true; }

void Resources::freeDriver(int driverId) {
  if (driverId <= 0 || driverId > 2) throw std::runtime_error("Invalid driver ID");
  if (driverId == 1)
    availableDrivers1 = true;
  else if (driverId == 2)
    availableDrivers2 = true;
}

void Resources::freeModem() { availableModems = true; }
 