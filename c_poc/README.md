# FourNights: C implementation
A program to encrypt all files with certain file extensions in a target directory. Creates a custom key, and sends that key over a socket to a remote server, which sends the key back when properly authenticated. Can be used for good OR evil. Please don't use it for evil. I am not responsible for how this software is used.

Additionally, some anti-debugging and obfuscation features have been added for extra authenticity.

## Dependencies
Uses the OpenSSL crypto library for bulk file encryption with AES, encryption of a session key with RSA, and transfer over a network with SSL/TLS.

``libcrypto`` and ``libssl`` libraries are included here. Several standard library functions have been recreated and customized.

## Build:
``make``

To disable obfuscation functions and macros:
``make OBFUSC=0``

To enable verbose debugging options and disable obfuscation:
``make DEBUG=1``

## Use
``./fournights.0.0.1 <target directory>``

## Program Design
Coming soon

## To Do:
### Resolve Known Bugs:
- [ ] {!} En/Decrypts incorrectly when files are > 4KiB
- [ ] {!} If run twice in a row, overwrite the old key.
- [ ] {-} What if the program hits a file or directory that it has insufficient permissions to do anything with?
- [ ] {-} Uses a recursive function with a lot of variables to walk through all files in a directory. Done this way for MVP. If the target directory has a lot of nested directories, could use up so much memory, it runs out. Use a stack instead?

### For MVP
- [ ] { } Reorganize code for legibility
- [ ] {>} Open a socket to send a key (Replaces current functionality where raw key data is saved to a local file)
- [ ] {!} Encrypt Raw Key Data with RSA
- [ ] {M} Figure out system design for server
  - [ ] How to listen for keys
  - [ ] How to store keys
  - [ ] How to send back keys
  - [ ] How to listen for proper authentication
- [ ] {M} Figure out how to prompt user for decryption authentication
- [ ] {-} Case insensitive file extension search
- [ ] {-} Unit Testing
- [ ] {M} Prepare presentation 
- [ ] {M} Prepare test environments for demonstrations

### Desired Features
- [ ] {!} Implement binary search algorithm for looking through list of target file extensions. Currently, uses linear search for MVP
- [ ] {!} Open a socket to send a key via ping
- [ ] {~} Anti-Disassembly
- [ ] {~} Obfuscation
- [ ] {-} Portability (Currently only tested on Ubuntu)
  - [ ] Server to send system appropriate binary
- [ ] {-} Stealth
- [ ] {-} Sandbox detection
- [ ] {-} Figure out how to send key to multiple IP addresses 
- [ ] {-} Generate custom bitcoin addresses and private keys to access the coins

### Legend for tasklist
| Symbol| Meaning                     |
| ------| ---------------------------:|
|  { }  | current item                |
|  {>}  | next item                   |
|  {M}  | Needed for MVP              |
|  {!}  | high priority               |
|  {~}  | medium priority             |
|  {-}  | low priority                |
|  {.}  | done                        |

### Schedule June 19 - June 30
| Day| Date| Task                        |
| ---| ---| ----------------------------|
| Sa | 17 |                             |
| Su | 18 |                             |
| M  | 19 |                             |
| Tu | 20 |                             |
| W  | 21 |                             |
| Th | 22 |                             |
| F  | 23 |                             |
| Sa | 24 |                             |
| Su | 25 |                             |
| M  | 26 |                             |
| Tu | 27 |                             |
| W  | 28 |                             |
| Th | 29 |                             |
| F  | 30 | Deadline + Presentation     |

## Links
See ../LINKS.md

## Author:
**Ian Xaun Liu-Johnston**
