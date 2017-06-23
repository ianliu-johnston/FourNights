#include "fournights.h"
/**
  * AES encryption/decryption demo program using OpenSSL EVP apis
  * gcc -Wall -Werror -Wextra -pedantic -g openssl_aes.c openssl_aes_main.c -lcrypto
  *
  * this is public domain code.
  *
  * Saju Pillai (saju.pillai@gmail.com)
  * Resource:
  * Adapted by Ian Liu-Johnston (iliujohnston@gmail.com)
 (* see openssl_aes.c for the functions aes_init, aes_decrypt, and aes_encrypt
 **/

int main(int argc, char *argv[])
{
/*
     "opaque" encryption, decryption ctx structures that libcrypto uses to record
     status of enc/dec operations
*/
    EVP_CIPHER_CTX encrypt, decrypt;
    int key_data_len;
    char *plaintext;
    unsigned char *ciphertext;
    int olen, len;
    char *key_data = "password";
    char *buffer = "I am a super duper secret string that nobody can nab";
/*
    8 bytes to salt the key_data during key generation. This is an example of compiled in salt. We just read the bit pattern created by these two 4 byte integers on the stack as 64 bits of contigous salt material - ofcourse this only works if sizeof(int) >= 4
*/
    unsigned int salt[] = {12345, 54321};

    key_data_len = my_strlen(key_data);
/* gen key and iv. init the cipher ctx object */
    if (aes_init((unsigned char *)key_data, key_data_len, (unsigned char *)&salt, &encrypt, &decrypt)) {
        fprintf(stderr, "Couldn't initialize AES cipher\n");
        return -1;
    }
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <password>", argv[0]);
        return(1);
    }
/* Encrypt buffer */
    olen = len = my_strlen(buffer)+1;
    ciphertext = aes_encrypt(&encrypt, (unsigned char *)buffer, &len);
    printf("ciphertext: %s\n", ciphertext);
    if (!(my_strncmp(argv[1], key_data, key_data_len)))
    {
        plaintext = (char *)aes_decrypt(&decrypt, ciphertext, &len);
        if (my_strncmp(plaintext, buffer, olen))
          printf("FAIL: enc/dec failed for \"%s\"\n", buffer);
        else
          printf("OK: enc/dec ok for \"%s\"\n", plaintext);
        printf("plaintext: %s\n", plaintext);
        free(plaintext);
        EVP_CIPHER_CTX_cleanup(&decrypt);
    }
    else
        printf("WRONG\n");
    free(ciphertext);
    EVP_CIPHER_CTX_cleanup(&encrypt);

    return 0;
}
