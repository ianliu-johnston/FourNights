# Basic Makefile for fournights

CC=gcc

SRC_DIR=src
SRC=$(SRC_DIR)/debugging_fxns.c \
	$(SRC_DIR)/file_operations.c \
	$(SRC_DIR)/linked_list_functions.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/memory_management.c \
	$(SRC_DIR)/obfuscation.c \
	$(SRC_DIR)/search.c \
	$(SRC_DIR)/string_funcs.c

INCL_DIR=includes
# DEPS=$(INCL_DIR)/fournights.h $(INCL_DIR)/obfuscation.h

OBJ=$(SRC:.c=.o)
NAME=fournights.0.0.1
LIBS=-lcrypto
CFLAGS=-Wall -Werror -Wextra -pedantic -g -I $(INCL_DIR) $(LIBS)

.PHONY: clean oclean fclean re all $(NAME)
all: $(SRC) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

fclean: oclean clean

oclean:
	$(RM) $(OBJ)

clean:
	$(RM) .*.swp $(NAME)

re: oclean all


