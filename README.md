# Pseudo-SO-multiprogramado

# Documentação do Programa FileManager (file_manager.h)

Este programa serve como um gerenciador de arquivos. Ele é capaz de adicionar e remover arquivos de um sistema de arquivos simulado. Ele também é capaz de executar uma série de operações de arquivos em um determinado momento.

## Classe: `FileManager`

### Variáveis
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

# Gerenciador de Memória (memory_manager.h)

O gerenciador de memória é usado para gerenciar a memória para processos em tempo real e processos de usuário.

## Variáveis Estáticas

1. `userProcessMemory`: Esta variável representa a memória do processo do usuário. Ela é um vetor de inteiros, onde cada inteiro é o PID de um processo. A quantidade de memória disponível para processos do usuário é definida como 960 blocos.

2. `rtProcessMemory`: Esta variável representa a memória do processo em tempo real. Ela é um vetor de inteiros, onde cada inteiro é o PID de um processo. A quantidade de memória disponível para processos em tempo real é definida como 64 blocos.

## Funções

### isMemoryAvailable(int blocks, int priority, int\* offset)

Esta função verifica se há memória suficiente disponível para o processo especificado. Se o processo for em tempo real (prioridade 0), ele verifica a memória do processo em tempo real. Se o processo for um processo do usuário (prioridade diferente de 0), ele verifica a memória do processo do usuário.

### addProcessToMemory(int blocks, int priority, int offset)

Esta função adiciona o processo à memória e retorna o offset da memória onde o processo foi alocado.

### removeProcessFromMemory(int blocks, int priority, int offset)

Esta função remove o processo da memória.

# Gerenciador de Processos (process_manager.h)

O Gerenciador de Processos é responsável por criar, executar e finalizar processos. Ele também é responsável por alocar recursos para processos que precisam deles.

## Variáveis

1. `processes` : Esta variável representa os processos do gerenciador de processos. Ela é um vetor de ponteiros para Process, onde cada Process é um processo no sistema operacional.

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

# Processos (process.h)

A classe Process representa um processo no contexto de uma simulação de um sistema operacional. Abaixo, você encontrará uma descrição das variáveis e funções que compõem a classe Process.

## Variáveis

1. `pidCounter`: É um contador de ID's de processo que garante a unicidade do ID de cada processo (pid).

2. `pid`: É o ID único de cada processo. Atribuído através do pidCounter.

3. `startTimestamp`: Representa o carimbo de data/hora de quando o processo foi criado.

4. `priority`: A prioridade do processo.

5. `cpuTime`: Representa o tempo que o processo gastou na CPU.

6. `allocatedBlocks`: Representa o número de blocos de memória alocados para o processo.

7. `requiredPrinterCode`: Indica o código da impressora que o processo irá utilizar.

8. `isScannerUsed`: Sinaliza se o processo faz uso de um scanner.

9. `isModemUsed`: Sinaliza se o processo faz uso de um modem.

10. `diskNumber`: Representa o número do disco que o processo irá utilizar.

11. `timeInCPU`: Representa o tempo total que o processo passou na CPU.

12. `memoryOffset`: Representa o offset do bloco de memória para o processo.

13. `printerAllocated`: Sinaliza se uma impressora foi alocada para o processo.

14. `scannerAllocated`: Sinaliza se um scanner foi alocado para o processo.

15. `driverAllocated`: Sinaliza se um driver foi alocado para o processo.

16. `modemAllocated`: Sinaliza se um modem foi alocado para o processo.

## Funções

### Método: `Process()`

Construtor da classe. Inicializa as variáveis com os valores fornecidos.

### Método: `~Process()`

Destrutor da classe.

### Método: `getPID()`

Retorna o ID do processo.

### Método: `getStartTimestamp()`

Retorna o carimbo de data/hora de início do processo.

### Método: `getPriority()`

Retorna a prioridade do processo.

### Método: `geCPUTime()`

Retorna o tempo de CPU usado pelo processo.

### Método: `getAllocatedBlocks()`

Retorna o número de blocos de memória `alocados para o processo.

### Método: `getRequiredPrinterCode()`

Retorna o código da impressora necessária pelo processo.

### Método: `getIsScannerUsed()`

Retorna se o processo utiliza um scanner.

### Método: `getIsModemUsed()`

Retorna se o processo usa um modem.

### Método: `getDiskNumber()`

Retorna o número do disco usado pelo processo.

### Método: `updateCPUTimeByQuantum(int quantum)`

Atualiza o tempo de CPU do processo pelo quantum passado como argumento.

### Método: `setPrinterAllocated(bool printerAllocated)`

Define se uma impressora foi alocada para o processo.

### Método: `setScannerAllocated(bool scannerAllocated)`

Define se um scanner foi alocado para o processo.

### Método: `setDriverAllocated(bool driverAllocated)`

Define se um driver foi alocado para o processo.

### Método: `setModemAllocated(bool modemAllocated)`

Define se um modem foi alocado para o processo.

### Método: `setPriority(int priority)`

Define a prioridade do processo.

### Método: `getPrinterAllocated()`

Retorna se uma impressora foi alocada para o processo.

### Método: `getScannerAllocated()`

Retorna se um scanner foi alocado para o processo.

### Método: `getDriverAllocated()`

Retorna se um driver foi alocado para o processo.

### Método: `getModemAllocated()`

Retorna se um modem foi alocado para o processo.

### Método: `getTimeInCPU()`

Retorna o tempo total gasto pelo processo na CPU.

### Método: `hasAllocatedResources()`

Verifica se o processo tem recursos alocados.

### Método: `hasFinished()`

Verifica se o processo terminou.

### Método: `processInfo()`

Imprime as informações do processo.

# Filas (queues.h)

As filas são usadas para gerenciar processos em um sistema operacional ou aplicativo similar.

## Variaveis

1. `realTimeQueue`: Esta fila armazena processos em tempo real.

2. `userQueue1`, `userQueue2`, `userQueue3`: Estas filas armazenam processos de usuários. A divisão em três filas pode ser usada para implementar um esquema de prioridades entre os processos de usuários.

3. `printer1Queue`, `printer2Queue`: Estas filas armazenam processos que estão aguardando para usar as impressoras 1 e 2, respectivamente.

4. `scannerQueue`: Esta fila armazena processos que estão aguardando para usar o scanner.

5. `driver1Queue`, `driver2Queue`: Estas filas armazenam processos que estão aguardando para usar os drivers 1 e 2, respectivamente.
6. `modemQueue`: Esta fila armazena processos que estão aguardando para usar o modem.

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

## Variáveis

1. `availablePrinters1 e availablePrinters2`: Estas são variáveis booleanas que representam a disponibilidade de duas impressoras no sistema. Se o valor for verdadeiro, a impressora correspondente está disponível; se for falso, a impressora está em uso.

2. `availableScanners`: Esta é uma variável booleana que representa a disponibilidade de um scanner no sistema. Se o valor for verdadeiro, o scanner está disponível; se for falso, o scanner está em uso.

3. `availableDrivers1 e availableDrivers2`: Estas são variáveis booleanas que representam a disponibilidade de dois drivers no sistema. Se o valor for verdadeiro, o driver correspondente está disponível; se for falso, o driver está em uso.

4. `availableModems`: Esta é uma variável booleana que representa a disponibilidade de um modem no sistema. Se o valor for verdadeiro, o modem está disponível; se for falso, o modem está em uso.

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

### Variáveis na estrutura ProgramArguments

1. `processesFileName`: Esta é uma variável do tipo const char* que representa o nome do arquivo que contém as informações dos processos.
   
2 .`filesFileName`: Esta é uma variável do tipo const char* que representa o nome do arquivo que contém as informações dos arquivos.


# Dispatcher (Dispatcher.h) 

Este arquivo define a classe `Dispatcher`, que é responsável por gerenciar os processos de execução e arquivos a partir das informações obtidas dos arquivos especificados. 

- `processesFileName`: O nome do arquivo que contém as informações dos processos. Essas informações serão usadas pelo `Dispatcher` para gerenciar os processos em sua execução.
- `filesFileName`: O nome do arquivo que contém as informações dos arquivos. O `Dispatcher` usará essas informações para realizar operações relacionadas aos arquivos.

## Métodos

### `void run();`

Este método é usado para iniciar o `Dispatcher`. Quando este método é chamado, o `Dispatcher` começa a gerenciar os processos e arquivos de acordo com as informações fornecidas nos arquivos especificados no momento da criação do `Dispatcher`.

