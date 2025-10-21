# Nome do executável final
PROG = programa

# Compilador e flags
CC = gcc
CFLAGS = -Wall -g

# Arquivos fonte e objetos
SRC = list.c int_list.c
OBJ = $(SRC:.c=.o)

# Regras phony
.PHONY: all clean

# Regra padrão
all: $(PROG)

# Gerar executável
$(PROG): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(PROG)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(PROG)