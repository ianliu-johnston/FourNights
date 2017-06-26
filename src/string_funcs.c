#include "fournights.h"
/**
  * tokenizer - create an array of strings
  * @str: string to tokenize
  * @file_filter: file_filter struct to push stuff into
  * Return: pointer to first token.
 **/
char *tokenizer(char *str, file_filter_t *file_filter)
{
	unsigned int len = 0, count_delims = 0, i = 0;
	char *saveptr = NULL, *token = NULL, **tokens = NULL;
	char *str_copied = NULL;

	if (!file_filter)
		return (NULL);
	if (!str)
	{
		file_filter->file_extensions = NULL;
		return (NULL);
	}
	/* count chars in string while counting delims must have exactly 1 delim*/
	for (len = 0; str[len] != '\n'; len++)
		if (str[len] == ' ')
			count_delims++;
	str_copied = my_calloc((len + 1) * sizeof(char), sizeof(char));
	file_filter->file_exts_whole_str = my_strncat(str_copied, str, 0, len);
	tokens = malloc((count_delims + 2) * sizeof(char *));
	tokens[0] = token = my_strtok_r(str_copied, "\n ", &saveptr);
	for (i = 1; token != NULL; i++)
	{
		token = my_strtok_r(NULL, "\n ", &saveptr);
		tokens[i] = token;
	}
	file_filter->file_extensions = tokens;
	return (tokens[0]);
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
