/** See tests/openssl_aes_main.c for attribution. **/
#include "fournights.h"
/**
  * aes_init - Create a 256 bit key and IV using the supplied key_data
 (* Fills in the encryption and decryption ctx objects and returns 0 on success
 (* Gen key & IV for AES 256 CBC mode. A SHA1 digest is used to hash the supplied key material.
 (* nrounds is the number of times the material is hashed
 (*
  * @key_data: the plaintext key
  * @key_data_len: length of the key
  * @salt: salt for randomization and more secure keys
  * @e_ctx: encryption structure
  * @d_ctx: decryption structure
  * Return: 0 on success, -1 on failure
 **/

int aes_encrypt_init(unsigned char *key_data, int key_data_len, unsigned char *salt, EVP_CIPHER_CTX *e_ctx)
{
	int nrounds = 6;
	unsigned char key[32];
	unsigned char iv[32];
	FILE *fd; /* TODO: write to socket instead of a file */

	if (EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, key_data, key_data_len, nrounds, key, iv) != 32)
   	{
		printf("Key size is not 256 bits\n");
		return (-1);
	}
	EVP_CIPHER_CTX_init(e_ctx);
	EVP_EncryptInit_ex(e_ctx, EVP_aes_256_cbc(), NULL, key, iv);
	/* TODO: write to socket instead of file */
	fd = fopen("/home/vagrant/FourNights/data.key", "w+");
		fwrite(key, sizeof(char), 32, fd);
		fseek(fd, 32, SEEK_SET);
		fwrite(iv, sizeof(char), 32, fd);
	fclose(fd);
	return (0);
}

/**
  * aes_decrypt_init - Fills in the decryption ctx object from a hash and an iv
 (* reads raw hashed keydata from a file.
  * @d_ctx: decryption structure
  * Return: 0 on success, -1 on failure
 **/
int aes_decrypt_init(EVP_CIPHER_CTX *d_ctx)
{
	unsigned char key[32];
	unsigned char iv[32];
	FILE *fd;

	/* TODO: read from socket instead of file */
	fd = fopen("/home/vagrant/FourNights/data.key", "r+");
		fread(key, sizeof(char), 32, fd);
		fseek(fd, 32, SEEK_SET);
		fread(iv, sizeof(char), 32, fd);
	fclose(fd);

	EVP_CIPHER_CTX_init(d_ctx); /* Basically a memset wrapper */
	EVP_DecryptInit_ex(d_ctx, EVP_aes_256_cbc(), NULL, key, iv);
	return (0);
}

/*
 * aes_encrypt - encrypt *len bytes of plaintext
 * @encrypt: pointer to EVP cipher struct from openssl wrappers
 * @plaintext: pointer to source plaintext buffer
 * @len: size of plaintext buffer in bytes
 * Return: pointer to ciphertext buffer
 */
unsigned char *aes_encrypt(EVP_CIPHER_CTX *encrypt, unsigned char *plaintext, int *len)
{
	int c_len = 0; /* working length of cyphertext buffer */
	int f_len = 0; /* final length of cyphertext buffer */
	unsigned char *ciphertext = NULL;

	c_len = *len + AES_BLOCK_SIZE;
	ciphertext = malloc(c_len);
	EVP_EncryptInit_ex(encrypt, NULL, NULL, NULL, NULL);
	EVP_EncryptUpdate(encrypt, ciphertext, &c_len, plaintext, *len);
	EVP_EncryptFinal_ex(encrypt, ciphertext+c_len, &f_len);
	*len = c_len + f_len;
	return (ciphertext);
}

/**
  * aes_decrypt - decrypt *len bytes of ciphertext
  * @decrypt: pointer to EVP cipher struct from openssl wrappers
  * @ciphertext: pointer to source encrypted buffer
  * @len: size of ciphertext buffer in bytes
  * Return: pointer to plaintext buffer
 (* note - len plaintext will always be equal to or lesser than length of ciphertext
 **/
unsigned char *aes_decrypt(EVP_CIPHER_CTX *decrypt, unsigned char *ciphertext, int *len)
{
	int p_len = *len; /* working length of plaintext buffer */
	int f_len = 0; /* final length of plaintext buffer */
	unsigned char *plaintext = NULL;

	plaintext = malloc(p_len);
	EVP_DecryptInit_ex(decrypt, NULL, NULL, NULL, NULL);
	EVP_DecryptUpdate(decrypt, plaintext, &p_len, ciphertext, *len);
	EVP_DecryptFinal_ex(decrypt, plaintext + p_len, &f_len);
	*len = p_len + f_len;
	return (plaintext);
}
