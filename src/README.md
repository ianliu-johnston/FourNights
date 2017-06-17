gcc -Wall -Werror -Wextra -pedantic -I../includes openssl_aes.c string_funcs.c memory_management.c -lcrypto -o test -DNO_OBFUSCATION -ldl
