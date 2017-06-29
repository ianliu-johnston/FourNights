#include "fournights.h"
#ifndef AES_H
#define AES_H
  #include <openssl/aes.h>
  #include <openssl/rand.h>
#endif
/**
  * aes_encrypt_init - Create a 256 bit key and IV using the supplied key_data
 (* if one doesn't already exist, otherwise uses the supplied key + IV
 (* Fills in the encryption ctx objects using AES 256 CBC mode.
 (* A SHA1 digest is used to hash the supplied key material.
  * @e_ctx: decryption structure
  * Return: 0 on success, -1 on failure
 **/
EVP_CIPHER_CTX *aes_encrypt_init(EVP_CIPHER_CTX *e_ctx)
{
	int i;
	int rounds = 24;
	unsigned char key[32], iv[32];
	unsigned char key_iv[64];

	unsigned char key_enc[2048];
	unsigned char key_dec[2048];
	int res = 0;
	unsigned char key_data[512], salt[16];
	char key_path[PATH_MAX];
	/*
	FILE *fd = NULL;
	*/
	FILE *fw = NULL;

	/* if a key and IV is in the file system, use that to encrypt or decrypt. */
	if (!getcwd(key_path, PATH_MAX))
		return (NULL);
	my_strncat(key_path, "/data.key\0", my_strlen(key_path), 10);
	/*
	fd = fopen(key_path, "r");
	if (fd)
	{
		if (!fread(key, sizeof(char), 32, fd))
			return (NULL);
		if (!fread(iv, sizeof(char), 32, fd))
			return (NULL);
		fclose(fd);
		goto init_cipher;
	}
	*/
	/* otherwise create a new key */
	RAND_bytes(salt, 16);
	RAND_bytes(key_data, 512);
	if (EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(),
						salt, key_data, 512, rounds, key, iv) != 32)
	{
		fprintf(stderr, "Key size is not 256 bits\n");
		return (NULL);
	}
	/*
	fw = fopen(key_path, "wb+");
		fwrite(key, sizeof(char), 32, fw);
		fwrite(iv, sizeof(char), 32, fw);
	fclose(fw);
	*/

	/* TODO: write to socket instead of file */
	/*
init_cipher:
*/
	for (i = 0; i < 64; i++)
	{
		if (i < 32)
			key_iv[i] = key[i];
		if (i >= 32)
			key_iv[i] = iv[i - 32];
	}
	res = rsa_public_encrypt(key_iv, 64, key_enc);
	if (res < 0)
		return (NULL);

	fw = fopen(key_path, "wb+");
		fwrite(key_enc, sizeof(char), res, fw);
	fclose(fw);

	if (rsa_private_decrypt(key_enc, res, key_dec) < 0)
		return (NULL);

	printf("Plaintext\n");
	for (i = 0; i < 64; i++)
		printf("%s%x", i ? ", " : "", key_iv[i]);

	printf("\nDecrypted\n");
	for (i = 0; i < 64; i++)
		printf("%s%x", i ? ", " : "", key_dec[i]);
	printf("\nEncrypted\n");
	for (i = 0; i < res; i++)
		printf("%s%x", i ? ", " : "", key_enc[i]);
	putchar('\n');

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
	int res, i;
	unsigned char key[32];
	unsigned char iv[32];
	unsigned char *key_iv_enc;
	unsigned char *key_iv_dec;
	char key_path[PATH_MAX];
	FILE *fd;
	struct stat file_info;

	if (!getcwd(key_path, PATH_MAX))
		return (NULL);
	my_strncat(key_path, "/data.key\0", my_strlen(key_path), 10);
	/* TODO: read from socket instead of file */
	if (lstat(key_path, &file_info) == -1)
		return (NULL);
	key_iv_enc = malloc((int)file_info.st_size * sizeof(char));
	key_iv_dec = my_calloc(512 * sizeof(char), sizeof(char));
	if (!key_iv_enc || !key_iv_dec)
		return (NULL);
	fd = fopen(key_path, "r");
	if (!fread(key_iv_enc, sizeof(char), file_info.st_size, fd))
		return (NULL);
	fclose(fd);
	printf("Encoded\n");
	for (i = 0; i < (int)file_info.st_size; i++)
		printf("%02x ", key_iv_enc[i]);
	putchar('\n');
	res = rsa_private_decrypt(key_iv_enc, (int)file_info.st_size, key_iv_dec);
	if (res < 0)
		return (NULL);
	printf("Decoded\n");
	for (i = 0; i < 32; i++)
	{
		key[i] = key_iv_dec[i];
		printf("%02x ", key[i]);
	}
	for (i = 32; i < 64; i++)
	{
		iv[i - 32] = key_iv_dec[i];
		printf("%02x ", iv[i - 32]);
	}

	EVP_CIPHER_CTX_init(d_ctx);
	EVP_DecryptInit_ex(d_ctx, EVP_aes_256_cbc(), NULL, key, iv);
	/*
	free(key_iv_enc);
	key_iv_enc = NULL;
	free(key_iv_dec);
	key_iv_dec = NULL;
	*/
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
