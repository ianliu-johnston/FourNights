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

	buf = malloc(BIGBUF * sizeof(char));
	if (!buf)
		return(NULL);
	if(!getcwd(cwd_key, PATH_MAX))
		return (NULL);
	if (cipher_flag == 'e')
		my_strncat(cwd_key, "/public.pem\0", my_strlen(cwd_key), 12);
	else if (cipher_flag == 'd')
		my_strncat(cwd_key, "/private.pem\0", my_strlen(cwd_key), 13);
	lstat(cwd_key, &file_info);
	fd = fopen(cwd_key, "r");
	if (!fd)
		return (NULL);
	fread(buf, file_info.st_size, sizeof(char), fd);
	fclose(fd);
   	return (buf);
}

/**
  * createRSA - Create an RSA key
 (* http://hayageek.com/rsa-encryption-decryption-openssl-c/
  * @key: RSA key
  * @cipher_flag: 'e' for encrypt 'd' for decrypt
  * Return: pointer to RSA object
  */
static RSA *createRSA(char cipher_flag)
{
	unsigned char *key;
    RSA *rsa = NULL;
    BIO *keybio;

	key = get_key(cipher_flag);
    keybio = BIO_new_mem_buf(key, -1);
    if (keybio == NULL)
    {
        fprintf(stderr, "Failed to create key BIO\n");
		return (NULL);
    }
    if(cipher_flag == 'e')
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
    else if (cipher_flag == 'd')
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
    if(rsa == NULL)
        fprintf(stderr,"Failed to create RSA\n");
	free(key);
    return (rsa);
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
	RSA *rsa = NULL;
	int result;

	rsa = createRSA('e');
	if (!rsa)
		return (0);
	result = RSA_public_encrypt(data_len, dec, enc, rsa, RSA_PKCS1_PADDING);
	return(result);
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
	RSA *rsa = NULL;
	int result;

	rsa = createRSA('d');
	if (!rsa)
		return (0);
	result = RSA_private_decrypt(data_len, enc, dec, rsa, RSA_PKCS1_PADDING);
	CRYPTO_cleanup_all_ex_data();
	return (result);
}
