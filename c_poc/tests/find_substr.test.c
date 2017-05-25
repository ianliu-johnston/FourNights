#include "fournights.h"

/*
 * Test for find sub_str
 * All tests except sub1 should not pass.
 */
int main(void)
{
    char *string = "Hello";
    char *sub1 = "ello";
    char *sub2 = "ellor";
    char *sub3 = "ell1";
    char *sub4 = "Hel";
    char *sub5 = "Helmet";

    printf("-----STRING: %s-----\n", string);
    printf("is sub1 in str? %s: %d\n", sub1, find_substr(string, sub1));
    printf("is sub2 in str? %s: %d\n", sub2, find_substr(string, sub2));
    printf("is sub3 in str? %s: %d\n", sub3, find_substr(string, sub3));
    printf("is sub4 in str? %s: %d\n", sub4, find_substr(string, sub4));
    printf("is sub5 in str? %s: %d\n", sub5, find_substr(string, sub5));
    return(0);
}

