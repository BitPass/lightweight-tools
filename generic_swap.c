#include <stdio.h>
void generic_swap(void *a, void *b, int size);

int main()
{
    int a = 5;
    int b = 9;
    printf("a = %d b = %d \n", a, b);

    generic_swap(&a, &b, sizeof(int));

    printf("a = %d b = %d \n", a, b);
    return 0;
}

void generic_swap(void *a, void *b, int size)
{
    void *temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}
