CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++11 

SRCS = arquivo1.cpp arquivo2.cpp
OBJS = $(SRCS:.cpp=.o)
PROGRAM = nome_do_programa

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)
