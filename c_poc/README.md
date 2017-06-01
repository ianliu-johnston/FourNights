# C implementation of python prototype

## Dependencies
No dependencies required. All precompiled libraries are included here. Few standard library headers are included, because they have been recreated and customized.

## Versions:
1. Proof of concept: All functions and variables are named logically
2. Anti-Disassemble: All functions and variables are obfuscated

## Build:
With debugging print modes:
``gcc -Wall -Werror -Wextra -pedantic *.c -lssl -lcrypto -o bulk_encrypt``

Without debugging print modes:
``gcc -Wall -Werror -Wextra -pedantic *.c -lssl -lcrypto -o bulk_encrypt -D DEBUG_H``

## Author:
**Ian Xaun Liu-Johnston**
