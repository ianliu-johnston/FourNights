# Basic Makefile for fournights

CC=gcc
SRC_DIR=src
OSSL_DIR=$(SRC_DIR)/openssl
OSSL_DIR_AES=$(OSSL_DIR)/aes
OSSL_DIR_EVP=$(OSSL_DIR)/evp
OSSL_SRC=$(OSSL_DIR_AES)/ \
	$(OSSL_DIR_EVP)/

SRC=$(SRC_DIR)/encryption.c \
	$(SRC_DIR)/file_operations.c \
	$(SRC_DIR)/linked_list_functions.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/memory_management.c \
	$(SRC_DIR)/search.c \
	$(SRC_DIR)/string_funcs.c \
	$(OSSL_SRC)
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

# TODO: fix to have a simple command: make debug, instead of make DEBUG=1
#debug: SRC += $(SRC_DIR)/debugging_fxns.c
#debug: 
#debug: all

fclean: oclean clean

oclean:
	$(RM) $(SRC_DIR)/debugging_fxns.o $(OBJ)

clean:
	$(RM) .*.swp $(NAME)

re: oclean all
aes_cbc.c
aes_cfb.c
aes_core.c
aes_ctr.c
aes_ecb.c
aes.h
aes_ige.c
aes_locl.h
aes_misc.c
aes_ofb.c
aes_wrap.c
aes_x86core.c
asm
Makefile
README
