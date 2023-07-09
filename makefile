CXX = g++ # Compilador
CXXFLAGS = -Wall -Wextra -g -std=c++11  # Flags de compilação

TARGET = dispatcher# Nome do executável
PFILE = processes.txt # Arquivos de entrada
FFILE = files.txt # Arquivos de entrada

OBJ_DIR = obj
SRC_DIR = src

$(shell mkdir -p $(OBJ_DIR)) # Cria a pasta obj se ela não existir

SOURCES := $(shell find $(SRC_DIR) -name '*.cpp') # Encontra todos os arquivos .cpp
OBJECTS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SOURCES:.cpp=.o)) # Substitui src por obj e .cpp por .o

.PHONY: all clean # Indica que essas regras não são arquivos

all: $(TARGET)
	$(info $(shell echo -e "\033[0;33m$(SOURCES)\033[0m")) 
	$(info $(shell echo -e "\033[0;32m$(OBJECTS)\033[0m"))

$(TARGET): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@


run: $(TARGET)
	./$(TARGET) $(PFILE) $(FFILE)

clean:
	rm -rf $(TARGET) $(OBJ_DIR)
