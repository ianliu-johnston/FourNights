#include "fournights.h"
#include <string.h>
/**
  * tokenizer - create an array of strings
  * @str: string to tokenize
  * @ransom: ransom struct to push stuff into
  * Return: Double pointer
 **/
char **tokenizer(char *str, ransom_t *ransom)
{
	unsigned int len, count_delims, i;
	char *saveptr, *token, **tokens;

	len = count_delims = 0;
	if (!ransom)
		return (NULL);
	if (!str)
	{
		ransom->file_extensions = NULL;
		return (NULL);
	}
	/* count chars in string while counting delims */
	for (len = 0; str[len]; len++)
		if (str[len] == ' ')
			count_delims++;
	tokens = malloc((count_delims + 2) * sizeof(char *));
	tokens[0] = token = strtok_r(str, "\n ", &saveptr);
	for (i = 1; token != NULL; i++)
	{
		token = strtok_r(NULL, "\n ", &saveptr);
		tokens[i] = token;
	}
	ransom->num_of_file_ext = i - 1;
	ransom->file_extensions = tokens;
	return (tokens);
}

/**
  * my_strncmp - compares two strings up to n bytes
  * @s1: String to compare
  * @s2: string to compare
  * @n: number of bytes to compare
  * Return: Difference between the first two different characters
 **/
int my_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	for (i = 0; i <= n && s1[i] && s2[i]; i++)
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (s1[i] - s2[i]);
}

/**
  * my_strlen - gets the length of a string
  * @s: string to measure
  * Return: length of the string
 **/
size_t my_strlen(const char *s)
{
	size_t i;

	if (!s)
		return (0);
	for (i = 0; s[i]; i++)
		;
	return (i);
}

/**
  * my_strncat - copies a string then adds a terminating null byte
  * @dest: destination of bytes
  * @src: source string
  * @offset: specify where to start copying from
  * @n: number of bytes to copy
  * Return: Pointer to dest if no errors
 **/
char *my_strncat(char *dest, const char *src, size_t offset, size_t n)
{
	size_t i;

	if (!dest || !src)
		return (NULL);
	for (i = 0; i < n && src[i]; i++)
		dest[offset + i] = src[i];
	dest[offset + i] = '\0';
	return (dest);
}
