# Basic Makefile for fournights

CC=gcc
SRC_DIR=src
SRC=$(SRC_DIR)/file_operations.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/memory_management.c \
	$(SRC_DIR)/openssl_aes.c \
	$(SRC_DIR)/traverse_dir.c \
	$(SRC_DIR)/search.c \
	$(SRC_DIR)/string_funcs.c \
	$(SRC_DIR)/string_funcs_strtok.c
INCL_DIR=includes
OBJ=$(SRC:.c=.o)
NAME=fournights.0.0.1
LIB_DIR=-Llib
LIBS=-lcrypto -ldl
CFLAGS=-Wall -Werror -Wextra -pedantic -g -I $(INCL_DIR) 

DEBUG=0
OBFUSC=1
ifeq ($(DEBUG),1)
	SRC += $(SRC_DIR)/debugging_fxns.c
	CFLAGS += -g
	OBFUSC=0
else
	CFLAGS += -DNO_DEBUG
endif

.PHONY: clean oclean fclean re all $(NAME)
all: $(SRC) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIB_DIR) $(LIBS)

# TODO: fix to have a simple command: make debug, instead of make DEBUG=1
#debug: SRC += $(SRC_DIR)/debugging_fxns.c
#debug: 
#debug: all

fclean: oclean clean

oclean:
	$(RM) $(SRC_DIR)/debugging_fxns.o $(OBJ)

clean:
	$(RM) .*.swp data.key $(NAME)

re: oclean all
