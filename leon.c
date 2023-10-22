#include<unistd.h>

char *my_strcpy(char *dest, char *src) 
{    
    int count;

    count = 0;
    while (src[count] != '\0')
    {
        dest[count] = src[count];
        count++;
    }
    dest[count] = '\0';
    return dest;
}

int    main(void)
{
    char *test = "Hello Leon";
    char *result;
    char array[2];
    result = &array[0];
    int    i;
    int a;

    i = 0;
    a = 0;
    result = my_strcpy(result, test);
    while (result[i] != '\0')
    {
        write(1, &result[i], 1);
        i++;
    }
    return (0);
}
