#include "fournights.h"

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

/**
  * find_substr_end - finds filepath extensions
  * @string: string to search through
  * @substr: substring to search for
  * Return: return the index if found, or 0 if not found and on error
 **/
unsigned int find_substr_end(char *string, char *substr)
{
	int i, j;
	int len_str, len_substr;

	if (!string || !substr)
		return (0);
	len_str = my_strlen(string);
	len_substr = my_strlen(substr);
	if (len_str == 0 || len_substr == 0 || len_str < len_substr)
		return (0);
	for (i = len_str, j = len_substr; i >= 0; i--)
	{
		for (j = len_substr; string[i] == substr[j]; j--, i--)
			if (j == 0)
				return ((unsigned int)len_str - len_substr);
	}
	return (0);
}
