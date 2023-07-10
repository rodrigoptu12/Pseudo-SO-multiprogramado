# Pseudo-SO-multiprogramado


# Documentação do Programa FileManager (file_manager.h)

Este programa serve como um gerenciador de arquivos. Ele é capaz de adicionar e remover arquivos de um sistema de arquivos simulado. Ele também é capaz de executar uma série de operações de arquivos em um determinado momento.

## Classe: `FileManager`

### Variáveis Estáticas:

1. `blocks` : Um vetor que representa os blocos de armazenamento, cada arquivo individual é representado por um caractere específico no vetor.
2. `totalBlocks` : Um inteiro representando o número total de blocos de memória.
3. `occupiedBlocks` : Um inteiro representando o número de blocos atualmente ocupados.
4. `filesOwner` : Um mapa onde a chave é um caractere representando um arquivo e o valor é um inteiro representando o ID do processo que possui o arquivo.
5. `fileOperations` : Um vetor de objetos `FileOperation` representando as operações que devem ser realizadas nos arquivos.

### Método: `void loadInitFile(const char* fileFileName)`

Este método carrega os valores iniciais de blocos, totalBlocks, arquivos e fileOperations de um determinado arquivo de texto.

### Método: `FileOperationResult addFile(int processOwner, char name, int quantityBlocks, int startBlock)`

Este método tenta adicionar um novo arquivo nos blocos de armazenamento disponíveis. Se não houver espaço suficiente, ou o arquivo já existir, ele falha com uma mensagem de erro apropriada.

### Método: `FileOperationResult removeFile(int processOwner, char name)`

Este método remove um arquivo dos blocos apenas se ele existir. Ele também remove a propriedade do arquivo.

### Método: `void removePIDFromFilesOwner(int processId)`

Este método remove todas as entradas de um determinado processo do mapa de propriedade de arquivos.

### Método: `bool addFileOperation(int processId, FileOperationType type, char name, int quantityBlocks)`

Este método cria uma nova operação de arquivo e a adiciona ao vetor de operações a serem realizadas.

### Método: `FileOperationsResult executeFileOperations()`

Este método executa todas as operações no vetor fileOperations e retorna os resultados.

### Método: `FileOperationResult executeFileOperation(FileOperation fileOperation)`

Este método executa uma única operação de arquivo. As operações podem ser criar ou deletar, e o método verifica e lida com uma variedade de condições e erros.

### Método: `std::vector<char> getBlocks()`

Um método getter que retorna o vetor de blocos que representa os blocos de armazenamento.


# Gerenciador de Processos (process_manager.h)

O Gerenciador de Processos é responsável por criar, executar e finalizar processos. Ele também é responsável por alocar recursos para processos que precisam deles.

## Funções

### Método: `loadInitFile(const char *processFileName)`

Esta função carrega um arquivo de inicialização que contém informações do processo. O arquivo é lido linha por linha, e cada linha é dividida por vírgulas para extrair detalhes do processo. Um novo processo é criado para cada linha no arquivo.

### Método: `sortProcessesByStartTimestamp()`

Esta função ordena os processos pelo seu timestamp de início.

### Método: `createProcess(int startTimestamp, int priority, int cpuTime, int allocatedBlocks, int requiredPrinterCode, int isScannerUsed, int isModemUsed, int diskNumber)`

Esta função cria um novo processo com os parâmetros fornecidos e o adiciona à lista de processos.

### Método: `deleteProcess(int pid)`

Esta função deleta um processo com o PID fornecido.

### Método: `createProcessesAndAddToReadyQueue(int startTimestamp, int priority, int cpuTime, int allocatedBlocks, int requiredPrinterCode, int isScannerUsed, int isModemUsed, int diskNumber)`

Esta função cria um novo processo e o adiciona à fila de prontos.

### Método: `getProcess(int pid)`

Esta função retorna um processo com o PID fornecido.

### Método: `getProcesses()`

Esta função retorna todos os processos.

### Método: `getProcessPriority(int pid)`

Esta função retorna a prioridade de um processo com o PID fornecido.

### Método: `processExists(int pid)`

Esta função verifica se um processo com o PID fornecido existe.

### Método: `runProcess(Process *process)`

Esta função executa um processo.

### Método: `runProcesses()`

Esta função executa todos os processos na fila.

### Método: `rotatePriority(Process *process)`

Esta função rotaciona a prioridade de um processo.

### Método: `allocateResourcesToProcessesInQueues()`

Esta função aloca recursos para processos nas filas.

### Método: `releaseResources(Process *process)`

Esta função libera os recursos de um processo.

### Método: `verifyResources(Process *process)`

Esta função verifica se um processo tem todos os recursos de que precisa.

### Método: `verifyPrintersResource(Process *process)`

Esta função verifica se um processo tem o recurso de impressora de que precisa.

### Método: `verifyScannersResource(Process *process)`

Esta função verifica se um processo tem o recurso de scanner de que precisa.

### Método: `verifyDriversResource(Process *process)`

Esta função verifica se um processo tem o recurso de driver de que precisa.

### Método: `verifyModemsResource(Process *process)`

Esta função verifica se um processo tem o recurso de modem de que precisa.



# Filas (queues.h)

As filas são usadas para gerenciar processos em um sistema operacional ou aplicativo similar.

## Funções

### Método: `getNextProcess()`

Esta função retorna o próximo processo da fila. Ela verifica cada fila na ordem: realTimeQueue, userQueue1, userQueue2, userQueue3. Se todas as filas estiverem vazias, ela lança um erro.

### Método: `setGlobalQueue(std::vector<Process*> processes)`

Esta função adiciona todos os processos fornecidos à fila de prontos.

### Método: `addToReadyQueue(Process* process)`

Esta função adiciona um processo à fila de prontos, dependendo de sua prioridade.

### Método: `isEmpty()`

Esta função verifica se todas as filas estão vazias.

### Método: `addToPrinter1Queue(Process* process)`

Esta função adiciona um processo à fila da impressora 1.

### Método: `addToPrinter2Queue(Process* process)`

Esta função adiciona um processo à fila da impressora 2.

### Método: `addToScannerQueue(Process* process)`

Esta função adiciona um processo à fila do scanner.

### Método: `addToDriver1Queue(Process* process)`

Esta função adiciona um processo à fila do driver 1.

### Método: `addToDriver2Queue(Process* process)`

Esta função adiciona um processo à fila do driver 2.

### Método: `addToModemQueue(Process* process)`

Esta função adiciona um processo à fila do modem.

### Método: `isPrinter1QueueEmpty()`

Esta função verifica se a fila da impressora 1 está vazia.

### Método: `isPrinter2QueueEmpty()`

Esta função verifica se a fila da impressora 2 está vazia.

### Método: `isScannerQueueEmpty()`

Esta função verifica se a fila do scanner está vazia.

### Método: `isDriver1QueueEmpty()`

Esta função verifica se a fila do driver 1 está vazia.

### Método: `isDriver2QueueEmpty()`

Esta função verifica se a fila do driver 2 está vazia.

### Método: `isModemQueueEmpty()`

Esta função verifica se a fila do modem está vazia.

### Método: `getNextPrinter1Process()`

Esta função retorna o próximo processo da fila da impressora 1. Se a fila estiver vazia, ela lança um erro.

### Método: `getNextPrinter2Process()`

Esta função retorna o próximo processo da fila da impressora 2. Se a fila estiver vazia, ela lança um erro.

### Método: `getNextScannerProcess()`

Esta função retorna o próximo processo da fila do scanner. Se a fila estiver vazia, ela lança um erro.

### Método: `getNextDriver1Process()`

Esta função retorna o próximo processo da fila do driver 1. Se a fila estiver vazia, ela lança um erro.

### Método: `getNextDriver2Process()`

Esta função retorna o próximo processo da fila do driver 2. Se a fila estiver vazia, ela lança um erro.

### Método: `getNextModemProcess()`

Esta função retorna o próximo processo da fila do modem. Se a fila estiver vazia, ela lança um erro.



# Recursos (resources.h)

Os recursos são usados para gerenciar a disponibilidade de impressoras, scanners, drivers e modems.

## Funções

### Método: `getAvailablePrinter(int printerId)`

Esta função retorna se a impressora com o ID fornecido está disponível.

### Método: `getAvailableScanners()`

Esta função retorna se o scanner está disponível.

### Método: `getAvailableDriver(int driverId)`

Esta função retorna se o driver com o ID fornecido está disponível.

### Método: `getAvailableModems()`

Esta função retorna se o modem está disponível.

### Método: `usePrinter(int printerId)`

Esta função usa a impressora com o ID fornecido. Se a impressora não estiver disponível ou o ID for inválido, ela lança um erro.

### Método: `useScanner()`

Esta função usa o scanner. Se o scanner não estiver disponível, ela lança um erro.

### Método: `useDriver(int driverId)`

Esta função usa o driver com o ID fornecido. Se o driver não estiver disponível ou o ID for inválido, ela lança um erro.

### Método: `useModem()`

Esta função usa o modem. Se o modem não estiver disponível, ela lança um erro.

### Método: `freePrinter(int printerId)`

Esta função libera a impressora com o ID fornecido. Se o ID for inválido, ela lança um erro.

### Método: `freeScanner()`

Esta função libera o scanner.

### Método: `freeDriver(int driverId)`

Esta função libera o driver com o ID fornecido. Se o ID for inválido, ela lança um erro.

### Método: `freeModem()`

Esta função libera o modem.



# Utilitários (utils.h)

Os utilitários são usados para fornecer funções auxiliares que são comumente usadas em todo o programa.

## Funções

### Método: `split(std::string str, char splitter)`

Esta função divide uma string em um vetor de strings com base em um caractere delimitador.

### Método: `parseProgramArguments(int argc, char const *argv[])`

Esta função analisa os argumentos do programa. Se o número de argumentos não for 3, ela imprime uma mensagem de uso e sai do programa.

