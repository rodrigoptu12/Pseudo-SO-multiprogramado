#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <fstream>  // ifstream
#include <map>      // map
#include <vector>   // vector

#include "../process/process_manager.h"
#include "../utils/utils.h"  // split

#define NO_OWNER -1

enum FileOperationType { CREATE = 0, DELETE = 1 };

struct FileOperation {
  int processId;
  FileOperationType type;
  char name;
  int quantityBlocks;
};

struct FileOperationResult {
  bool success;
  std::string message;
};

struct FileOperationsResult {
  // results of file operations
  std::vector<FileOperationResult> fileOperationResults;
  // number of operations that were tried to be executed
  int numberOfOperationsTriedToBeExecuted;
};

// uses contiguous allocation and first-fit
class FileManager {
 private:
  static std::vector<char> blocks;  // blocks of file manager ["X", "X", "X", ..., "Y", "Y", "Z"]
  static int totalBlocks;           // total blocks of file manager
  static int occupiedBlocks;        // occupied blocks of file manager

  static std::map<char, int> filesOwner;  // map of files and their owners <file name, process id>
  static std::vector<FileOperation> fileOperations;  // operations of file manager to be executed

  // add file to blocks using first-fit
  static FileOperationResult addFile(int processOwner, char name, int quantityBlocks,
                                     int startBlock);
  // remove file from blocks
  static FileOperationResult removeFile(int processOwner, char name);

  // execute file operation
  static FileOperationResult executeFileOperation(FileOperation fileOperation);

 public:
  // load init file
  static void loadInitFile(const char* fileFileName);

  // add file operation (in a real system, its equivalent to a system call from a process)
  static bool addFileOperation(int processId, FileOperationType type, char name,
                               int quantityBlocks);

  static void removePIDFromFilesOwner(int pid);

  // execute file operations
  static FileOperationsResult executeFileOperations();

  // get blocks current state
  static void printBlocks();
};

#endif  // FILE_MANAGER_H