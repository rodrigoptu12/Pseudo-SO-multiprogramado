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
  std::ifstream files_file(fileFileName);
  if (!files_file.is_open()) throw std::runtime_error("Error opening files file");
  std::string line;
  // get total blocks and occupied blocks
  std::getline(files_file, line);
  totalBlocks = std::stoi(line);
  std::getline(files_file, line);
  int filesSaved = std::stoi(line);

  blocks.resize(totalBlocks, '0');  // initialize blocks with 0

  int fileSaveCounter = 0;  // counter to know how many occupied blocks we have already read

  // get files that are already in the file manager
  while (filesSaved > fileSaveCounter++ && std::getline(files_file, line)) {
    std::vector<std::string> lineVector = split(line, ',');  // split line by comma

    char name = lineVector[0][0];
    int startBlock = std::stoi(lineVector[1]);
    int quantityBlocks = std::stoi(lineVector[2]);

    addFile(NO_OWNER, name, quantityBlocks, startBlock);
  }

  // get file operations
  while (std::getline(files_file, line)) {
    std::vector<std::string> lineVector = split(line, ',');  // split line by comma

    int processId = std::stoi(lineVector[0]);
    FileOperationType type = (FileOperationType)std::stoi(lineVector[1]);

    // remove spaces from name
    lineVector[2].erase(std::remove(lineVector[2].begin(), lineVector[2].end(), ' '),
                        lineVector[2].end());

    char name = lineVector[2][0];

    int quantityBlocks = (type == CREATE ? std::stoi(lineVector[3]) : 0);

    addFileOperation(processId, type, name, quantityBlocks);
  }

  files_file.close();
}

FileOperationResult FileManager::addFile(int processOwner, char name, int quantityBlocks,
                                         int startBlock) {
  FileOperationResult fileOperationResult = {true, ""};

  // check if file already exists
  for (int i = 0; i < totalBlocks; i++) {
    if (blocks[i] == name) {
      fileOperationResult.success = false;
      fileOperationResult.message = "O processo " + std::to_string(processOwner) +
                                    " não pode criar o arquivo " + name +
                                    " porque ele já existe no disco.";
      return fileOperationResult;
    }
  }

  // add file to blocks using first-fit
  // example: if we have 10 blocks and we want to add a file with 3 blocks, we will search for 3
  // consecutive free blocks and add the file to these blocks
  int _startBlock = 0;
  int freeBlocksCounter = 0;  // counter to know how many blocks we have already read
  for (int i = startBlock; i < totalBlocks; i++) {
    // if we find a 0 block, we increment freeBlocksCounter
    if (blocks[i] == '0') {
      if (freeBlocksCounter == 0) _startBlock = i;
      freeBlocksCounter++;
      // if we find a non-0 block, we reset freeBlocksCounter
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
      std::string message =
          "O processo " + std::to_string(processOwner) + " criou o arquivo " + name;
      if (quantityBlocks == 1)
        message += " (bloco: ";
      else
        message += " (blocos: ";
      for (int j = _startBlock; j < _startBlock + quantityBlocks; j++) {
        message += std::to_string(j);
        if (j < _startBlock + quantityBlocks - 2) {
          message += ", ";
        } else if (j == _startBlock + quantityBlocks - 2) {
          message += " e ";
        } else {
          message += ").";
        }
      }

      fileOperationResult.success = true;
      fileOperationResult.message = message;
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
      blocks[i] = '0';
      occupiedBlocks--;
    }
  }

  filesOwner.erase(name);  // remove file from filesOwner

  FileOperationResult fileOperationResult = {
      true, "O processo " + std::to_string(processOwner) + " deletou o arquivo " + name + "."};
  return fileOperationResult;
}

void FileManager::removePIDFromFilesOwner(int processId) {
  for (auto it = filesOwner.begin(); it != filesOwner.end(); ++it) {
    if (it->second == processId) {
      it->second = NO_OWNER;  // remove process from filesOwner
    }
  }
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
    default: {
      FileOperationResult fileOperationResult = {
          false, "O tipo de operação " + std::to_string(fileOperation.type) + " não existe."};
      return fileOperationResult;
    }
  }
}

// getters
void FileManager::printBlocks() {
  std::cout << "Mapa de ocupacao do disco: " << std::endl;
  for (auto it = blocks.begin(); it != blocks.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}