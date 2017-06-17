# FourNights: C implementation
A program to encrypt all files with certain file extensions in a target directory. Creates a custom key, and sends that key over a socket to a remote server, which sends the key back when properly authenticated. Can be used for good OR evil. Please don't use it for evil. I am not responsible for how this software is used.

Additionally, some anti-debugging and obfuscation features have been added for extra authenticity.

## Specifications
<h5>Development Environment</h5>

* ``lsb_release -dirc && uname -pro`` output:

```
Distributor ID:	Ubuntu
Description:	Ubuntu 14.04.5 LTS
Release:	14.04
Codename:	trusty
3.13.0-101-generic x86_64 GNU/Linux
```

* gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04.3)
* OpenSSL version 1.0.2l (May 2017)
* Python 3 version 3.4.3

<h5>Tested On</h5>
- Ubuntu trusty 14.04.5 LTS

<h5>Dependencies</h5>
Uses OpenSSL crypto library for bulk file encryption with AES, encryption of a session key with RSA, and transfer over a network with SSL/TLS.

``libcrypto`` and ``libssl`` libraries are included here. Several standard library functions have been recreated and customized.

## Build
``make``

To disable obfuscation functions and macros:
``make OBFUSC=0``

To enable verbose debugging options and disable obfuscation:
``make DEBUG=1``

### Use
``./fournights.0.0.1 <target directory>``

## Program Design Flowchart
Coming soon

## To Do:
### Resolve Known Bugs:
- [ ] {!} En/Decrypts incorrectly when files are > 4KiB
- [ ] {!} If run twice in a row, overwrite the old key.
- [ ] {~} What if the program hits a file or directory that it has insufficient permissions to do anything with?
- [ ] {~} Depends on the file ``file_exts.txt``, which has to be formatted in one line, to determine which file extensions to target. OK for an MVP, but this design has some serious limitations.
- [ ] {-} Searches through over 300 file extensions, this could lead to slow searches + inefficient memory management.
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
- [ ] {!} Delivery to clients
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
| Day| Date| Task                       |  | Day| Date| Task                      |
| ---| ---| ----------------------------| -| ---| ---| ---------------------------|
| Mo | 19 | Reorganize + refactor       |  | Mo | 26 | (if necessary) Refactoring + fix glaring bugs (else) Unit Testing|
| Tu | 20 | Open a socket to send a key |  | Tu | 27 | Unit Testing               |
| We | 21 | Server Design: Receive + Store keys |  | We | 28 | Setup virtual environment for demo|
| Th | 22 | Server Design: Send keys    |  | Th | 29 | Prepare Final Presentation |
| Fr | 23 | Prompt user for auth        |  | Fr | 30 | Final Presentation / Demo  |
| Sa | 24 | Server Design: Send keys on authentication|  | Sa | 01 | Take a break!              |
| Su | 25 | Optimizations + Desired Features|  | Su | 02 |                            |

## Links
See ../LINKS.md

## Author:
**Ian Liu-Johnston** [Twitter](https://twitter.com/@Concativerse) || [Personal Website](http://www.ianxaunliu-johnston.com/) || [Linkedin](https://www.linkedin.com/in/ian-liu-johnston-32a40a115)
