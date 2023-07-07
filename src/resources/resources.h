#ifndef RESOURCES_H
#define RESOURCES_H

#include <stdexcept>  // runtime_error
#include <vector>     // vector

#define MAX_PRINTERS 2
#define MAX_SCANNERS 1
#define MAX_DRIVERS 2
#define MAX_MODEMS 1

class Resources {
 private:
  static std::vector<bool> availablePrinters;   // number of available printers
  static bool availableScanners;                // number of available scanners
  static std::vector<bool> availableDrivers;    // number of available drivers
  static bool availableModems;                  // number of available modems

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