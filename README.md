# FourNights: C implementation
A program to encrypt all files with certain file extensions in a target directory. Creates a custom key, and stores it in the directory the binary is. Requires a list of file extensions, a public key, and a private key. I am not responsible for how this software is used.

## Specifications
<h5>Development Environment</h5>

Program tested only in this environment:

* **Operating System Version**	*Ubuntu 14.04.5 LTS trusty* -- (command: ``lsb_release -dirc``)

* **Kernel version** *3.13.0-101-generic x86_64 GNU/Linux*  -- (command: ``uname -pro``)

* **Glibc version** *(Ubuntu EGLIBC 2.19-0ubuntu6.11) 2.19* -- (command: ``ldd --version``)

* **GCC version** *4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04.3)*

* **OpenSSL** *version 1.0.2l (May 2017)*

* **Python 3** *version 3.4.3*

<h5>Dependencies</h5>
Uses OpenSSL crypto library for bulk file encryption with AES, encryption of a session key with RSA, and (future dev)transfer over a network with SSL/TLS.

``libcrypto`` and ``libssl`` libraries are included here. Several standard library functions have been recreated and customized.

Encryption scheme itself is AES 256 CBC mode.

## Build
``make``

To disable obfuscation functions and macros:
``make OBFUSC=0``

To enable verbose debugging options and disable obfuscation:
``make DEBUG=1``

### Use
Required Files must be in the same directory:
1. ``fournights.0.0.1`` -- complied binary
2. ``file_exts.txt`` -- file with file extensions to encrypt
3. ``public.pem`` -- public key used to encrypt the AES symmetric key
4. ``private.pem`` -- private key used to decrypt the AES key
5. ``TESTS/`` -- Directory that contains all target files. Required if the program is run without any arguments.

``./fournights.0.0.1 <target directory>``
If the program is run without a command line argument, it will default to trying to encrypt everything in a directory called "TESTS" that is in the current working directory. It will segfault if that directory does not exist. This is a built in vulnerability.

Requires a file ``file_exts.txt`` with a list of sorted file extensions, with each file extension separated by a single space. This is a built in vulnerability. 
Example:

```
.c .gif .h .jpg .pdf .zip
```

Files are encrypted with a randomly generated AES symmetric key, which is then encrypted with a RSA public key. This key is contained in another required file, called public.pem. This is feature currently in development. What some encryption programs do is to send a petition to a server, which then sends a public key to do the encryption with. This is not implemented.

To generate a private RSA key with openssl:
``openssl genrsa -out private.pem 4096``

To create a public key from that private key:
``openssl rsa -in private.pem -outform PEM -pubout -out public.pem``

## Program Design
### Flowchart
Coming soon

### Repository Structure
| Entry             | Description |
| ------------------| ------------|
| ``file_exts.txt`` | Necessary component for operation of compiled program. NOT GOOD DESIGN
| ``Makefile``      | Compiles + configure program
| ``includes/``     | All headerfiles for this program, and a tar archive with openssl header files
| ``lib/``          | Only Openssl Dynamic Library compiled for Ubuntu
| ``src/``          | All source files
| ``tests/``        | Unit tests
| ``initial_POC/``  | Contains initial python sketches for simple directory traversal and base64 obfuscation with password authentication
| ``TESTS/``        | Not a directory in this repository. Create with ``mkdir TESTS`` and populate with copies of misc. files for a test environment

## Organization
### To Do
#### Resolve Known Bugs
- [ ] {~} Depends on the file ``file_exts.txt``, which has to be formatted in one line, to determine which file extensions to target. OK for an MVP, but this design has some serious limitations.
- [ ] {-} Searches through over 300 file extensions, this could lead to slow searches + inefficient memory management.
- [ ] {-} Uses a recursive function with a lot of variables to walk through all files in a directory. Done this way for MVP. If the target directory has a lot of nested directories, could use up so much memory, it runs out. Use a stack instead?
- [x] En/Decrypts incorrectly when files are > 4KiB
- [x] If run twice in a row, overwrite the old key.
- [x] What if the program hits a file or directory that it has insufficient permissions to do anything with?
- [x] What happens when it hits a very large file and runs out of hard drive space? --> skip file if over 5Gb?
- [x] Remove hard coded filepaths for relative filepaths

#### Base functionality / design considerations
- [ ] { } Encrypt Raw Key Data with RSA
- [ ] { } Reorganize code for legibility -- on going
- [ ] { } Unit Testing
- [ ] {M} Prepare presentation 
- [ ] {M} Prepare test environments for demonstrations
- [ ] {M} Figure out how to prompt user for decryption authentication
- [ ] {-} Open a socket to send a key (Replaces current functionality where raw key data is saved to a local file)
- [ ] {-} Figure out system design for server
  - [ ] How to listen for keys
  - [ ] How to store keys
  - [ ] How to send back keys
  - [ ] How to listen for proper authentication
- [ ] {-} Case insensitive file extension search

#### Desired Features
- [ ] {!} Implement binary search algorithm for looking through list of target file extensions. Currently, uses linear search for MVP
- [ ] {~} Open a socket to send a key via ping
- [ ] {~} Delivery to clients
- [ ] {-} Portability (Currently only tested on Ubuntu)
  - [ ] Server to send system appropriate binary
- [ ] {-} Figure out how to send key to multiple IP addresses 
- [ ] {-} Generate custom bitcoin addresses and private keys to access the coins
- [ ] {-} Anti-Disassembly
- [ ] {-} Obfuscation
- [ ] {-} Stealth
- [ ] {-} Sandbox detection

##### Legend for tasklist
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
See [LINKS.md](LINKS.md)

## Author:
**Ian Liu-Johnston** [Twitter](https://twitter.com/@Concativerse) || [Personal Website](http://www.ianxaunliu-johnston.com/) || [Linkedin](https://www.linkedin.com/in/ian-liu-johnston-32a40a115)
