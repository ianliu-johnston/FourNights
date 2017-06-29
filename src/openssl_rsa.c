#include "fournights.h"
#ifndef RSA_H
#define RSA_H
  #include <openssl/rsa.h>
  #include <openssl/pem.h>
#endif
static unsigned char *get_key(char cipher_flag)
{
	char cwd_key[PATH_MAX];
	unsigned char *buf;
	FILE *fd;
	struct stat file_info;

	if(!getcwd(cwd_key, PATH_MAX))
		return (NULL);
	if (cipher_flag == 'e')
		my_strncat(cwd_key, "/public.pem\0", my_strlen(cwd_key), 12);
	else if (cipher_flag == 'd')
		my_strncat(cwd_key, "/private.pem\0", my_strlen(cwd_key), 13);
	lstat(cwd_key, &file_info);
	fd = fopen(cwd_key, "r");
	if (!fd)
	{
		fprintf(stderr, "Could not open key file.\n");
		return (NULL);
	}
	buf = my_calloc((file_info.st_size + 1) * sizeof(char), sizeof(char));
	if (!buf)
		return(NULL);
	fread(buf, file_info.st_size + 1, sizeof(char), fd);
	fclose(fd);
   	return (buf);
}

/**
  * rsa_cipher - Create an RSA key
  * @key: RSA key
  * @cipher_flag: 'e' for encrypt 'd' for decrypt
  * Return: pointer to RSA object
  */
static int rsa_cipher(unsigned char *plaintext,
					int data_len,
				   	unsigned char *ciphertext,
					char cipher_flag)
{
	unsigned char *key;
	int result;
    RSA *rsa = NULL;
    BIO *keybio = NULL;

	if (!plaintext || !ciphertext)
		return (-1);
	key = get_key(cipher_flag);
	if (!key)
		return (-1);
    keybio = BIO_new_mem_buf(key, -1);
    if (keybio == NULL)
    {
        fprintf(stderr, "Failed to create key BIO\n");
		free(key);
		return (-2);
    }
    if(cipher_flag == 'e')
	{
        PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
		if(rsa == NULL)
		{
			fprintf(stderr,"Failed to create RSA\n");
			free(key);
			return (-2);
		}
		result = RSA_public_encrypt(data_len, plaintext, ciphertext, rsa, RSA_PKCS1_PADDING);
	}
    if (cipher_flag == 'd')
	{
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
		if(rsa == NULL)
		{
			fprintf(stderr,"Failed to create RSA\n");
			free(key);
			return (-2);
		}
		result = RSA_private_decrypt(data_len, ciphertext, plaintext, rsa, RSA_PKCS1_PADDING);
	}
	free(key);
	RSA_free(rsa);
	BIO_free_all(keybio);
    return (result);
}

/**
  * public_encrypt - tiny wrapper for RSA_public_encrypt function
  * @plaintext: pointer to plaintext buffer
  * @data_len: length of buffer
  * @decrypted: pointer to encrypted buffer
  * Return: Length of encrypted buffer
 **/
int rsa_public_encrypt(unsigned char *dec,
					int data_len,
				   	unsigned char *enc)
{
	return(rsa_cipher(dec, data_len, enc, 'e'));
}

/**
  * private_decrypt - tiny wrapper for RSA_private_decrypt function
  * @enc_data: pointer to encrypted buffer
  * @data_len: length of encrypted buffer
  * @decrypted: pointer to decrypted buffer
  * Return: Length of decrypted buffer
 **/
int rsa_private_decrypt(unsigned char *enc,
					int data_len,
					unsigned char *dec)
{
	return(rsa_cipher(dec, data_len, enc, 'd'));
}
