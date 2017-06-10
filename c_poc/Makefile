# Basic Makefile for fournights

CC=gcc
SRC_DIR=src
SRC=$(SRC_DIR)/file_operations.c \
	$(SRC_DIR)/linked_list_functions.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/memory_management.c \
	$(SRC_DIR)/search.c \
	$(SRC_DIR)/string_funcs.c
INCL_DIR=includes
OBJ=$(SRC:.c=.o)
NAME=fournights.0.0.1
LIBS=-lcrypto
CFLAGS=-Wall -Werror -Wextra -pedantic -g -I $(INCL_DIR) $(LIBS)

DEBUG=0
OBFUSC=1
ifeq ($(DEBUG),1)
	SRC += $(SRC_DIR)/debugging_fxns.c
	OBFUSC=0
else
	CFLAGS += -DNO_DEBUG
endif

ifeq ($(OBFUSC),1)
	SRC += $(SRC_DIR)/obfuscation.c
else
	CFLAGS += -D NO_OBFUSCATION
endif

.PHONY: clean oclean fclean re all $(NAME)
all: $(SRC) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

#debug: SRC += $(SRC_DIR)/debugging_fxns.c
#debug: all

fclean: oclean clean

oclean:
	$(RM) $(OBJ)

clean:
	$(RM) .*.swp $(NAME)

re: oclean all
