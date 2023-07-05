CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g

SRCS = arquivo1.c arquivo2.c
OBJS = $(SRCS:.c=.o)
PROGRAM = nome_do_programa

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
$(CC) $(CFLAGS) -c $<

run: $(PROGRAM)
./$(PROGRAM)

clean:
rm -f $(PROGRAM) $(OBJS)
