#include "fournights.h"
/**
  * encrypt_key_iv - encrypts the key and iv and writes it to a file
  * @key: filepath to the encrypted session key
  * @iv: size of the file
  * Return: NULL on error, or a buffer to the decrypted key and IV
 **/
int encrypt_key_iv(unsigned char *key, unsigned char *iv)
{
	int i = 0, res = 0;
	char key_path[PATH_MAX];
	unsigned char key_iv[64];
	unsigned char key_enc[2048];
	FILE *fw = NULL;

	if (!getcwd(key_path, PATH_MAX))
		return (-1);
	my_strncat(key_path, "/data.key\0", my_strlen(key_path), 10);
	/* if key already exists, do not overwrite the key and do not encrypt again */
	if (access(key_path, R_OK) == 0) /* This is a kill switch */
		return (-1);

	for (i = 0; i < 32; i++)
		key_iv[i] = key[i];
	for (i = 32; i < 64; i++)
		key_iv[i] = iv[i - 32];
	res = rsa_public_encrypt(key_iv, 64, key_enc);
	if (res < 0)
		return (-1);

	fw = fopen(key_path, "wb+");
		fwrite(key_enc, sizeof(char), res, fw);
	fclose(fw);
	return (res);
}
/**
  * decrypt_key_iv - reads an encrypted file and fills buffers with the appropriate fields
  * @key: 32 byte sized buffer decrypted key goes in
  * @iv: 32 byte sized buffer decrypted iv goes in
  * Return: -1 on error, 1 on success
 **/
int decrypt_key_iv(unsigned char *key, unsigned char *iv)
{
	int i = 0, res = 0;
	unsigned char *key_iv_dec = NULL;
	unsigned char *key_iv_enc = NULL;
	char key_path[PATH_MAX];
	FILE *fd = NULL;
	struct stat file_info;

	if (!getcwd(key_path, PATH_MAX))
		return (-1);
	my_strncat(key_path, "/data.key\0", my_strlen(key_path), 10);
	if (lstat(key_path, &file_info) == -1)
		return (-1);
	key_iv_enc = malloc(file_info.st_size * sizeof(char));
	key_iv_dec = my_calloc(512 * sizeof(char), sizeof(char));
	if (!key_iv_enc || !key_iv_dec)
		return (-1);
	fd = fopen(key_path, "r");
	if (!fd)
		return (-1);
	if (!fread(key_iv_enc, sizeof(char), file_info.st_size, fd))
		return (-1);
	fclose(fd);
	res = rsa_private_decrypt(key_iv_enc, file_info.st_size, key_iv_dec);
	if (res < 0)
		return (-1);
	for (i = 0; i < 32; i++)
		key[i] = key_iv_dec[i];
	for (i = 32; i < 64; i++)
		iv[i - 32] = key_iv_dec[i];
	free(key_iv_dec);
	key_iv_dec = NULL;
	free(key_iv_enc);
	key_iv_enc = NULL;
	return (res);
}
