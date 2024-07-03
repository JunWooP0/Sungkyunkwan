#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

int selectionSort(int *arr, int size)
{
    int temp = 0;
    int max = 0;
    int count = 0;

    for (int i = 0; i < size - 1; i++)
    {
        max = i;
        for (int j = i + 1; j < size; j++)
        {
            count++;
            if (arr[max] < arr[j])
            {
                max = j;
            }
        }
        SWAP(arr[i], arr[max], temp);
    }
    return count;
}

void createRandom(int *arr)
{
    int i = 0;
    while (i < 100)
    {
        int unique = 1;
        int random = rand() % 1000;

        for (int j = 0; j < i; j++)
        {
            if (arr[j] == random)
            {
                unique = 0;
                break;
            }
        }
        if (unique)
        {
            arr[i] = random;
            i++;
        } // ignoring duplicated keys
    }
}

void ascended(int *arr)
{
    for (int i = 0; i < 100; i++)
    {
        arr[i] = i + 1;
    }
}

void descended(int *arr)
{
    for (int i = 0; i < 100; i++)
    {
        arr[i] = 100 - i;
    }
}

void print(int *arr)
{
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    int A[100];
    int count = 0;

    createRandom(A);
    printf("Case 1) Array filled with random number:\n");
    print(A);
    count = selectionSort(A, 100);
    printf("Sorted:\n");
    print(A);
    printf("Number of comparisons: %d\n", count);

    descended(A);
    printf("\nCase 2) Already sorted array:\n");
    print(A);
    count = selectionSort(A, 100);
    printf("Sorted:\n");
    print(A);
    printf("Number of comparisons: %d\n", count);

    ascended(A);
    printf("\nCase 3) Reversely sorted array:\n");
    print(A);
    count = selectionSort(A, 100);
    printf("Sorted:\n");
    print(A);
    printf("Number of comparisons: %d\n", count);

    return 0;
}