#include "fournights.h"
/**
 * helper - recursive helper function for the binary search
 * @array: input array
 * @size: size of the array
 * @first: first value of the sub array
 * @last: last value of the sub array
 * @value: value to search for
 * Return: Index of value if found, -1 on if not found
 */
static int helper(int *array, size_t size, size_t first, size_t last, int value)
{
	if (value == array[first])
		return (first);
	if (value == array[last])
		return (last);
	if (first >= last)
		return (-1);
	if (value == array[(first + last) / 2])
		return ((first + last) / 2);

	if (value < array[(first + last) / 2])
		return (helper(array, size, first, ((first + last) / 2), value));
	if (value > array[(first + last) / 2])
		return (helper(array, size, (first + last) / 2 + 1, last, value));
	return (-1);
}

/**
  * binary_search - binary search algorithm
  * @array: input array - must sorted in ascending order
  * @size: size of the array
  * @value: value to search for
  * Return: Index of value if found, -1 on errors or not found
 **/
int binary_search(int *array, size_t size, int value)
{
	if (!array)
		return (-1);
	return (helper(array, size, 0, size - 1, value));
}
/**
  * binary_search_string - goes through indicies in array of strings to find first index
  * @str: String to search through
  * @len: Length of the string
  * @file_filter: Main struct with often used values
  * Return: index of substring, -1 if not found
 **/
/* Basic Brute force. TODO: Use a search algorithm in an array*/
int binary_search_string(const char *str, size_t len, file_filter_t *file_filter)
{
	int i;

#ifndef NO_DEBUG
	printf("%s\n", str);
#endif
	/*
	binary_search(file_filter->file_extensions, file_filter->num_of_file_ext, str[ );
	*/
	for (i = 0; file_filter->file_extensions[i]; i++)
	{
		if (find_substr_end((char *)str, file_filter->file_extensions[i]))
			return (1);
	}
	len++;
	return (0);
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
