#include "fournights.h"
/**
  * tokenizer - create an array of strings
  * @str: string to tokenize
  * @ransom: ransom struct to push stuff into
  * Return: pointer to first token.
 **/
char *tokenizer(char *str, ransom_t *ransom)
{
	unsigned int len, count_delims, i;
	char *saveptr, *token, **tokens;
	char *str_copied;

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
	str_copied = my_calloc((len + 1) * sizeof(char), sizeof(char));
	ransom->file_ext_nontoken = my_strncat(str_copied, str, 0, len);
	tokens = malloc((count_delims + 2) * sizeof(char *));
	tokens[0] = token = my_strtok_r(str_copied, "\n ", &saveptr);
	for (i = 1; token != NULL; i++)
	{
		token = my_strtok_r(NULL, "\n ", &saveptr);
		tokens[i] = token;
	}
	ransom->num_of_file_ext = i - 1;
	ransom->file_extensions = tokens;
	return (tokens[i]);
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
/** ALL FOR STRTOK_R
  * TODO: Make this more efficient
 **/
/**
 * my_strchr - checks for a char in a string
 * @s: the string
 * @c: the char being searched for
 * Return: pointer to char on success, NULL on failure
 */
char *my_strchr(char *s, char c)
{
	int len, i;

	if (!s)
		return(NULL);
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
unsigned int my_strspn(char *s, char *accept)
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
char *my_strpbrk(char *s, char *delims)
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
  * @saveptr: pointer to index from last time called
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
