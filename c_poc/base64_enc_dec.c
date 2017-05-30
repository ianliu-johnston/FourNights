#include "fournights.h"
/*
 * From Stack Overflow:
 * https://stackoverflow.com/questions/342409/how-do-i-base64-encode-decode-in-c
 * Comments removed, and code adapted slightly to adhere to style.
 */

/**
  * base64encode - Encode a string in base64
  * @b64_encode_str: bytes to encode
  * @encode_size: encode this many bytes
  * Return: encoded data
 **/
char *base64encode(const void *b64_encode_str, int encode_size)
{
	BIO *b64_bio, *mem_bio;
	BUF_MEM *mem_bio_mem_ptr;

    b64_bio = BIO_new(BIO_f_base64());
    mem_bio = BIO_new(BIO_s_mem());
    BIO_push(b64_bio, mem_bio);
    BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(b64_bio, b64_encode_str, encode_size);
    BIO_flush(b64_bio);
    BIO_get_mem_ptr(mem_bio, &mem_bio_mem_ptr);
    BIO_set_close(mem_bio, BIO_NOCLOSE);
    BIO_free_all(b64_bio);
    BUF_MEM_grow(mem_bio_mem_ptr, mem_bio_mem_ptr->length + 1);
    mem_bio_mem_ptr->data[mem_bio_mem_ptr->length] = '\0';
    return (mem_bio_mem_ptr->data);
}

/**
  * base64decode - Decode a string in base64
  * @b64_decode_str: bytes to encode
  * @decode_size: encode this many bytes
  * Return: decoded data
 **/
char *base64decode (const void *b64_decode_str, int decode_size)
{
    BIO *b64_bio, *mem_bio;
    char *base64_decoded;
    int decoded_byte_index = 0;

	base64_decoded = calloc( (decode_size*3)/4+1, sizeof(char) );
    b64_bio = BIO_new(BIO_f_base64());
    mem_bio = BIO_new(BIO_s_mem());
    BIO_write(mem_bio, b64_decode_str, decode_size);
    BIO_push(b64_bio, mem_bio);
    BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);
    while ( 0 < BIO_read(b64_bio, base64_decoded+decoded_byte_index, 1) ){
        decoded_byte_index++;
    }
    BIO_free_all(b64_bio);
    return (base64_decoded);
}

/*
int main(void)
{
    char *data_to_encode;
    char *base64_encoded;
    char *base64_decoded;

	data_to_encode = "Base64 encode this string!";
    base64_encoded = base64encode(data_to_encode, my_strlen(data_to_encode));
    base64_decoded = base64decode(base64_encoded, my_strlen(base64_encoded));
    printf("Original character string is: %s\n", data_to_encode);
    printf("Base-64 encoded string is: %s\n", base64_encoded);
    printf("Base-64 decoded string is: %s\n", base64_decoded);

    free(base64_encoded);
    free(base64_decoded);
	return (0);
}
*/
