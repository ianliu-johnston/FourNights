#include "fournights.h"
/**
 * my_strchr - checks for a char in a string
 * @s: the string
 * @c: the char being searched for
 * Return: pointer to char on success, NULL on failure
 */
static char *my_strchr(char *s, char c)
{
	int len, i;

	if (!s)
		return (NULL);
	len = my_strlen(s);
	for (i = 0; i < len; i++)
		if (s[i] == c)
			return (s + i);
	s = '\0';
	return (s);
}
/**
 * my_strspn - gets length of a substring
 * @s: string to be searched
 * @accept: string to match
 * Return: number of matching bytes
 */
static unsigned int my_strspn(char *s, char *accept)
{
	int s_len, i, result;

	s_len = my_strlen(s);
	i = result = 0;
	while (i < s_len)
	{
		if (my_strchr(accept, s[i]))
			result++, i++;
		else
			return (result);
	}
	return (result);
}
/**
 * my_strpbrk - searches through a string for any set of bytes.
 * @s: string to search through
 * @delims: bytes to search for in the string.
 * Return: pointer to first occurence in s of anything in accept
 */
static char *my_strpbrk(char *s, char *delims)
{
	char *temp;

	temp = delims;
	for (; *s; s++)
	{
		for (; *delims; delims++)
			if (*s == *delims)
				return (s);
		delims = temp;
	}
	return (*s ? s : 0);
}
/**
  * my_strtok_r - turns a string into an array of strings
  * @s: string to tokenize
  * @delim: delimiters that determine where to split
  * @save_ptr: pointer to index from last time called
  * Return: pointer to beginning of next token
 **/
char *my_strtok_r(char *s, char *delim, char **save_ptr)
{
	char *token;

	if (s == NULL)
	{
		if (*save_ptr == NULL)
			return (NULL);
		s = *save_ptr;
	}
	s += my_strspn(s, delim);
	if (*s == '\0')
	{
		*save_ptr = NULL;
		return (NULL);
	}
	token = s;
	s = my_strpbrk(token, delim);
	if (s == NULL)
		*save_ptr = NULL;
	else
	{
		*s = '\0';
		*save_ptr = s + 1;
	}
	return (token);
}
