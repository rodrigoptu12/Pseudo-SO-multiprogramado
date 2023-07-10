#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>
#include <map>        // map
#include <stdexcept>  // runtime_error

class Resources {
 private:
  static bool availablePrinters1;  // number of available printers
  static bool availablePrinters2;  // number of available printers
  static bool availableScanners;   // number of available scanners
  static bool availableDrivers1;   // number of available drivers
  static bool availableDrivers2;   // number of available drivers
  static bool availableModems;     // number of available modems

 public:
  static bool getAvailablePrinter(int printerId);
  static bool getAvailableScanners();
  static bool getAvailableDriver(int driverId);
  static bool getAvailableModems();

  static void usePrinter(int printerId);
  static void useScanner();
  static void useDriver(int driverId);
  static void useModem();

  static void freePrinter(int printerId);
  static void freeScanner();
  static void freeDriver(int driverId);
  static void freeModem();
};

#endif  // RESOURCES_H