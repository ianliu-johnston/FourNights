#include "fournights.h"
/**
 * AES encryption/decryption demo program using OpenSSL EVP apis
 * gcc -Wall openssl_aes.c -lcrypto
 *
 * this is public domain code.
 *
 * Saju Pillai (saju.pillai@gmail.com)
 * Adapted by Ian Liu-Johnston (iliujohnston@gmail.com)
 **/


/**
 * Create a 256 bit key and IV using the supplied key_data. salt can be added for taste.
 * Fills in the encryption and decryption ctx objects and returns 0 on success
 **/
int aes_init(unsigned char *key_data, int key_data_len, unsigned char *salt, EVP_CIPHER_CTX *e_ctx, EVP_CIPHER_CTX *d_ctx, ransom_t *ransom)
{
  int i = 0, nrounds = 5;
  unsigned char key[32], iv[32];

  /*
   * Gen key & IV for AES 256 CBC mode. A SHA1 digest is used to hash the supplied key material.
   * nrounds is the number of times the we hash the material. More rounds are more secure but
   * slower.
   */
  i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, key_data, key_data_len, nrounds, key, iv);
  if (i != 32) {
#ifndef NO_DEBUG
    printf("Key size is %d bits - should be 256 bits\n", i);
#endif
    return -1;
  }

  EVP_CIPHER_CTX_init(e_ctx);
  EVP_EncryptInit_ex(e_ctx, EVP_aes_256_cbc(), NULL, key, iv);

  EVP_CIPHER_CTX_init(d_ctx);
  EVP_DecryptInit_ex(d_ctx, EVP_aes_256_cbc(), NULL, key, iv);

/*
#ifndef NO_DEBUG
*/
  if(ransom->cipher_flag == 'e')
	  printf("Encrypting!!\n");
  if(ransom->cipher_flag == 'd')
	  printf("Decrypting!!\n");
  /*
#endif
*/

  return (0);
}

/*
 * Encrypt *len bytes of data
 * All data going in & out is considered binary (unsigned char[])
 */
unsigned char *aes_encrypt(EVP_CIPHER_CTX *e, unsigned char *plaintext, int *len)
{
  /* max ciphertext len for a n bytes of plaintext is n + AES_BLOCK_SIZE -1 bytes */
  int c_len = *len + AES_BLOCK_SIZE, f_len = 0;
  unsigned char *ciphertext = malloc(c_len);

  /* allows reusing of 'e' for multiple encryption cycles */
  EVP_EncryptInit_ex(e, NULL, NULL, NULL, NULL);

  /* update ciphertext, c_len is filled with the length of ciphertext generated,
    *len is the size of plaintext in bytes */
  EVP_EncryptUpdate(e, ciphertext, &c_len, plaintext, *len);

  /* update ciphertext with the final remaining bytes */
  EVP_EncryptFinal_ex(e, ciphertext+c_len, &f_len);

  *len = c_len + f_len;
  return ciphertext;
}

/*
 * Decrypt *len bytes of ciphertext
 */
unsigned char *aes_decrypt(EVP_CIPHER_CTX *e, unsigned char *ciphertext, int *len)
{
  /* plaintext will always be equal to or lesser than length of ciphertext*/
  int p_len = *len, f_len = 0;
  unsigned char *plaintext = malloc(p_len);

  EVP_DecryptInit_ex(e, NULL, NULL, NULL, NULL);
  EVP_DecryptUpdate(e, plaintext, &p_len, ciphertext, *len);
  EVP_DecryptFinal_ex(e, plaintext+p_len, &f_len);

  *len = p_len + f_len;
  return plaintext;
}

/* int crypt_buffer_aes(unsigned char *key_data, unsigned int salt[], char *buffer)
int main(int argc, char *argv[])
{
	 "opaque" encryption, decryption ctx structures that libcrypto uses to record
	 status of enc/dec operations
	EVP_CIPHER_CTX encrypt, decrypt;
	int key_data_len;
	char *plaintext;
	unsigned char *ciphertext;
	int olen, len;
	char *key_data = "password";
	char *buffer = "I am a super duper secret string that nobody can nab";
	8 bytes to salt the key_data during key generation. This is an example of compiled in salt. We just read the bit pattern created by these two 4 byte integers on the stack as 64 bits of contigous salt material - ofcourse this only works if sizeof(int) >= 4
	unsigned int salt[] = {12345, 54321};

	key_data_len = my_strlen(key_data);
	gen key and iv. init the cipher ctx object
	if (aes_init((unsigned char *)key_data, key_data_len, (unsigned char *)&salt, &encrypt, &decrypt)) {
		fprintf(stderr, "Couldn't initialize AES cipher\n");
		return -1;
	}
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <password>", argv[0]);
		return(1);
	}
	Encrypt buffer
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
	{
		printf("WRONG\n");
	}
	free(ciphertext);
	EVP_CIPHER_CTX_cleanup(&encrypt);

	return 0;
}
*/
