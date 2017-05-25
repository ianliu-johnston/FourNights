#include "fournights.h"

/*
 * binary_search - search for a value with binary search algorithm
 * @array: array to search through
 * @size: size of the array
 * @search: value to search for
 * Return: index in array, -1 on error
 */
int binary_search(int array[], int size, int search)
{
	int i;

	if (!array)
		return(-1);

	for(i = 0; i <= size; i++)
	{
		printf("arr[%d] = %d, size = %d\n", i, array[i], size);
		if(array[i] <= array[size])
			i = size / 2;
		else
			size = size / 2;
		if (array[i] == search)
			return(i);
	}
	return(0);
}

int main(void)
{
	int array[10] = {1, 2, 4, 12, 22, 23, 39, 120, 245, 2324};
	printf("%d\n", binary_search(array, 10, 245));
	return(0);
}
