# Heap of Links
Links that were helpful in creating this program and all proof of concepts.

## Encryption Libraries
* [Scrypt](http://www.tarsnap.com/scrypt.html)
* [Serpent](http://www.cl.cam.ac.uk/~rja14/serpent.html)
* [Twofish](https://www.schneier.com/academic/twofish/download.html)
* [Threefish](https://github.com/wernerd/Skein3Fish)

### Base64
* [StackOverflow: Base64 in C with OpenSSL](https://stackoverflow.com/questions/342409/how-do-i-base64-encode-decode-in-c)
* [Base64 OpenSSL docs](https://www.openssl.org/docs/man1.0.2/crypto/BIO_f_base64.html)

### Openssl
* [OpenSSL Crypto Docs](https://www.openssl.org/docs/man1.0.2/crypto/crypto.html)
* [Blowfish Openssl](https://www.openssl.org/docs/man1.0.2/crypto/blowfish.html) - Don't use blowfish. It's old and easily broken
* [OpenSSL AES Example](https://github.com/saju/misc/blob/master/misc/openssl_aes.c) - Use AES
* [OpenSSL DOCS: EVP authenticated encryption / decryption](https://wiki.openssl.org/index.php/EVP_Authenticated_Encryption_and_Decryption)
* [OpenSSL DOCS: EVP Symmetric Encryption and Decryption](https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption)
* [OpenSSL DOCS: EVP BytesToKey()](https://wiki.openssl.org/index.php/Manual:EVP_BytesToKey(3))
* [OpenSSL DOCS: RAND functions](https://www.openssl.org/docs/man1.0.2/crypto/RAND_bytes.html)
* [OpenSSL AES decryption tutorial](http://eclipsesource.com/blogs/2017/01/17/tutorial-aes-encryption-and-decryption-with-openssl/)
* Network Security with OpenSSL by Viega/Messier/Chandra

## Function Call examples
* [How to use Uname](https://stackoverflow.com/questions/3596310/c-how-to-use-the-function-uname)
* [Detect if a process is being disassembled](https://stackoverflow.com/questions/3596781/how-to-detect-if-the-current-process-is-being-run-by-gdb)
* [Handling Signals in C](https://www.gnu.org/software/libc/manual/html_node/Sigaction-Function-Example.html)

## Technical How-To's
* [Makefile tutorial](http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)

## Portability
* [Github: Tinydir for wrapping POSIX dirent and Windows FindFirstFile](https://github.com/cxong/tinydir)

## Networking
* [ICMP Packet structure](http://www.networksorcery.com/enp/protocol/icmp/msg8.htm)
* [Creating Raw TCP packets in Python](http://www.binarytides.com/raw-socket-programming-in-python-linux/)

## Malware
* [The Zoo](https://github.com/ytisf/theZoo.git)

### Source code
* [Hidden Tear](https://github.com/goliate/hidden-tear.git)

### About Ransomware
* [Article on cradlecore ransomware](http://www.securityweek.com/cradlecore-ransomware-sold-source-code)
* [Article on ded cryptor ransomware](https://blog.kaspersky.com/ded-cryptor-ransomware/12526/)

### Debugging + Anti-Debugging Tactics
* [How to write a debugger: how they work](http://system.joekain.com/debugger/)
* [Anti-Reverse Engineering guide](https://www.codeproject.com/Articles/30815/An-Anti-Reverse-Engineering-Guide)
* [Five anti Debugging tricks that sometimes work](https://blog.malwarebytes.com/threat-analysis/2014/09/five-anti-debugging-tricks-that-sometimes-fool-analysts/)
* [Anti Debugging cheatsheet](http://antukh.com/blog/2015/01/19/malware-techniques-cheat-sheet/)
* [Defeating Debuggers by Raising the Dead](https://spareclockcycles.org/2012/02/14/stack-necromancy-defeating-debuggers-by-raising-the-dead/)
* [Symantec Anti-Debuggin Reference](https://www.symantec.com/connect/articles/windows-anti-debug-reference)
* [The "Ultimate" Debugging Reference](http://pferrie.host22.com/papers/antidebug.pdf)
