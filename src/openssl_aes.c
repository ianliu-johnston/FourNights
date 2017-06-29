#include "fournights.h"
#ifndef AES_H
#define AES_H
  #include <openssl/aes.h>
  #include <openssl/rand.h>
#endif
/**
  * aes_encrypt_init - Create a 256 bit key and IV using the supplied key_data
 (* Fills in the encryption ctx objects using AES 256 CBC mode.
 (* A SHA1 digest is used to hash the supplied key material.
  * @e_ctx: decryption structure
  * Return: pointer to the EVP_CIPHER_CTX structure or NULL on errors
 **/
EVP_CIPHER_CTX *aes_encrypt_init(EVP_CIPHER_CTX *e_ctx)
{
	int rounds = 24;
	unsigned char key[32], iv[32];
	unsigned char key_data[512], salt[16];

	RAND_bytes(salt, 16);
	RAND_bytes(key_data, 512);
	if (EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(),
						salt, key_data, 512, rounds, key, iv) != 32)
	{
		fprintf(stderr, "Key size is not 256 bits\n");
		return (NULL);
	}
	if (encrypt_key_iv(key, iv) < 0)
	{
		fprintf(stderr, "Key was not written to disk.\n");
		return (NULL);
	}
	EVP_CIPHER_CTX_init(e_ctx);
	EVP_EncryptInit_ex(e_ctx, EVP_aes_256_cbc(), NULL, key, iv);
	return (e_ctx);
}

/**
  * aes_decrypt_init - Fills in the decryption ctx object from a hash and an iv
 (* reads raw hashed keydata from a file.
  * @d_ctx: decryption structure
  * Return: 0 on success, -1 on failure
 **/
EVP_CIPHER_CTX *aes_decrypt_init(EVP_CIPHER_CTX *d_ctx)
{
	unsigned char key[32];
	unsigned char iv[32];

	if (decrypt_key_iv(key, iv) < 0)
		return (NULL);
	EVP_CIPHER_CTX_init(d_ctx);
	EVP_DecryptInit_ex(d_ctx, EVP_aes_256_cbc(), NULL, key, iv);
	return (d_ctx);
}

/*
 * aes_encrypt - encrypt *len bytes of plaintext
 * @encrypt: pointer to EVP cipher struct from openssl wrappers
 * @plaintext: pointer to source plaintext buffer
 * @len: size of plaintext buffer in bytes
 * Return: pointer to ciphertext buffer
 */
unsigned char *aes_encrypt(EVP_CIPHER_CTX *encrypt,
							unsigned char *plaintext, int *len)
{
	int c_len = 0; /* working length of cyphertext buffer */
	int f_len = 0; /* final length of cyphertext buffer */
	unsigned char *ciphertext = NULL;

	c_len = *len + AES_BLOCK_SIZE;

	ciphertext = malloc(c_len);
	EVP_EncryptInit_ex(encrypt, NULL, NULL, NULL, NULL);
	EVP_EncryptUpdate(encrypt, ciphertext, &c_len, plaintext, *len);
	EVP_EncryptFinal_ex(encrypt, ciphertext + c_len, &f_len);
	*len = c_len + f_len;
	return (ciphertext);
}

/**
  * aes_decrypt - decrypt *len bytes of ciphertext
  * @decrypt: pointer to EVP cipher struct from openssl wrappers
  * @ciphertext: pointer to source encrypted buffer
  * @len: size of ciphertext buffer in bytes
  * Return: pointer to plaintext buffer
 **/
unsigned char *aes_decrypt(EVP_CIPHER_CTX *decrypt,
							unsigned char *ciphertext, int *len)
{
	int p_len = *len; /* working length of plaintext buffer */
	int f_len = 0; /* final length of plaintext buffer */
	unsigned char *plaintext = NULL;

	plaintext = malloc(p_len);
	my_memset(plaintext, 0, sizeof(char));
	EVP_DecryptInit_ex(decrypt, NULL, NULL, NULL, NULL);
	EVP_DecryptUpdate(decrypt, plaintext, &p_len, ciphertext, *len);
	EVP_DecryptFinal_ex(decrypt, plaintext + p_len, &f_len);
	return (plaintext);
}

/**
  * check_padding - checks number of padding bytes
  * @buf: buffer to check
  * @size: size of buffer
  * Return: num of padded bits
 **/
int check_padding(unsigned char *buf, size_t size)
{
	unsigned char pad_byte;
	unsigned int i, counter = 0;

	if (!buf || size == 0)
		return (0);
	if (buf[size - 1] > 16) /* all padding characters will be < 16 */
		return (0);
	pad_byte = buf[size - 1];
	for (i = size - (int)pad_byte; i > size || buf[i] == pad_byte; i++)
		counter++;
	return (counter == (int)pad_byte ? (int)pad_byte : 0);
}
