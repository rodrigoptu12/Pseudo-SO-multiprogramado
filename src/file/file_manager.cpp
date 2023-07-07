#include "file_manager.h"

// initialize static variables

std::vector<char> FileManager::blocks;

int FileManager::totalBlocks = 0;

int FileManager::occupiedBlocks = 0;

std::map<char, int> FileManager::filesOwner;

std::vector<FileOperation> FileManager::fileOperations;

// methods

void FileManager::loadInitFile(const char* fileFileName) {
  // open file
  // get first and second line of files.txt
  std::ifstream files_file(fileFileName);
  if (!files_file.is_open()) throw std::runtime_error("Error opening files file");
  std::string line;

  std::getline(files_file, line);
  totalBlocks = std::stoi(line);
  std::getline(files_file, line);
  occupiedBlocks = std::stoi(line) + 2;  // +2 because of the first two lines

  blocks.resize(totalBlocks, NULL);  // initialize blocks with NULL

  int occupiedBlocksCounter = 0;  // counter to know how many occupied blocks we have already read
  // get files that are already in the file manager
  while (std::getline(files_file, line) && occupiedBlocks > occupiedBlocksCounter++) {
    std::vector<std::string> lineVector = split(line, ',');  // split line by comma

    char name = lineVector[0][0];
    int startBlock = std::stoi(lineVector[1]);
    int quantityBlocks = std::stoi(lineVector[2]);

    // add file to blocks
    addFile(NO_OWNER, name, quantityBlocks, startBlock);
  }

  // get file operations
  // create -> 0, 0, A, 5
  // delete -> 0, 1, X
  while (std::getline(files_file, line)) {
    std::vector<std::string> lineVector = split(line, ',');  // split line by comma

    int processId = std::stoi(lineVector[0]);
    FileOperationType type = (FileOperationType)std::stoi(lineVector[1]);
    char name = lineVector[2][0];
    int quantityBlocks = (type == CREATE ? std::stoi(lineVector[3]) : 0);

    addFileOperation(processId, type, name, quantityBlocks);
  }

  files_file.close();
}

FileOperationResult FileManager::addFile(int processOwner, char name, int quantityBlocks,
                                         int startBlock) {
  FileOperationResult fileOperationResult = {true, ""};
  int _startBlock = 0;
  int freeBlocksCounter = 0;  // counter to know how many blocks we have already read

  // add file to blocks using first-fit
  // example: if we have 10 blocks and we want to add a file with 3 blocks, we will search for 3
  // consecutive free blocks and add the file to these blocks
  for (int i = startBlock; i < totalBlocks; i++) {
    // EXTRA IF STATEMENT TO CHECK IF FILE ALREADY EXISTS (NO RELATION WITH FIRST-FIT)
    if (blocks[i] == name) {
      fileOperationResult.success = false;
      fileOperationResult.message = "O processo " + std::to_string(processOwner) +
                                    " não pode criar o arquivo " + name +
                                    " porque ele já existe no disco.";
      return fileOperationResult;
    }

    // if we find a NULL block, we increment freeBlocksCounter
    if (blocks[i] == NULL) {
      if (freeBlocksCounter == 0) _startBlock = i;
      freeBlocksCounter++;
      // if we find a non-NULL block, we reset freeBlocksCounter
    } else {
      freeBlocksCounter = 0;
    }

    // if we find the quantity of blocks we want, we add the file to these blocks
    if (freeBlocksCounter == quantityBlocks) {
      // add file to blocks
      for (int j = _startBlock; j < _startBlock + quantityBlocks; j++) blocks[j] = name;
      occupiedBlocks += quantityBlocks;
      filesOwner[name] = processOwner;

      // return success message
      fileOperationResult.success = true;
      fileOperationResult.message =
          "O processo " + std::to_string(processOwner) + " criou o arquivo " + name + " blocos:";
      for (int j = _startBlock; j < _startBlock + quantityBlocks; j++)
        fileOperationResult.message += " " + std::to_string(j);
      return fileOperationResult;
    }
  }

  // return error message
  fileOperationResult.success = false;
  fileOperationResult.message = "O processo " + std::to_string(processOwner) +
                                " não pode criar o arquivo " + name + " (falta de espaço).";

  return fileOperationResult;
}

FileOperationResult FileManager::removeFile(int processOwner, char name) {
  // check if file exists
  if (filesOwner.find(name) == filesOwner.end()) {
    FileOperationResult fileOperationResult = {false, "O processo " + std::to_string(processOwner) +
                                                          " não pode deletar o arquivo " + name +
                                                          " porque ele não existe."};
    return fileOperationResult;
  }

  // remove file from blocks
  for (int i = 0; i < totalBlocks; i++) {
    if (blocks[i] == name) {
      blocks[i] = NULL;
      occupiedBlocks--;
    }
  }

  filesOwner.erase(name);  // remove file from filesOwner

  FileOperationResult fileOperationResult = {
      true, "O processo " + std::to_string(processOwner) + " deletou o arquivo " + name + "."};
  return fileOperationResult;
}

bool FileManager::addFileOperation(int processId, FileOperationType type, char name,
                                   int quantityBlocks) {
  try {
    FileOperation fileOperation = {processId, type, name, quantityBlocks};
    fileOperations.push_back(fileOperation);
    return true;
  } catch (const std::exception& e) {
    return false;
  }
}

FileOperationsResult FileManager::executeFileOperations() {
  FileOperationsResult fileOperationsResult;
  fileOperationsResult.numberOfOperationsTriedToBeExecuted = fileOperations.size();

  while (!fileOperations.empty()) {
    FileOperation fileOperation = fileOperations.front();
    fileOperations.erase(fileOperations.begin());

    FileOperationResult fileOperationResult = executeFileOperation(fileOperation);
    fileOperationsResult.fileOperationResults.push_back(fileOperationResult);
  }

  return fileOperationsResult;
}

FileOperationResult FileManager::executeFileOperation(FileOperation fileOperation) {
  if (!ProcessManager::processExists(fileOperation.processId)) {
    FileOperationResult fileOperationResult = {
        false, "O processo " + std::to_string(fileOperation.processId) + " não existe."};
    return fileOperationResult;
  }

  switch (fileOperation.type) {
    case CREATE: {
      return addFile(fileOperation.processId, fileOperation.name, fileOperation.quantityBlocks, 0);
    }
    case DELETE: {
      // verify if process is real time (priority = 0) or if is the owner of the file
      if (ProcessManager::getProcessPriority(fileOperation.processId) != 0 &&
          filesOwner[fileOperation.name] != fileOperation.processId) {
        FileOperationResult fileOperationResult = {
            false, "O processo " + std::to_string(fileOperation.processId) +
                       " não tem permissão para deletar o arquivo " + fileOperation.name + "."};
        return fileOperationResult;
      }

      return removeFile(fileOperation.processId, fileOperation.name);
    }
  }
}

void FileManager::setProcessManager(ProcessManager* processManager) {
  FileManager::processManager = processManager;
}

// getters
std::vector<char> FileManager::getBlocks() { return blocks; }