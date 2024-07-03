#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int insertionSort(int *arr, int size)
{
    int count = 0;

    for (int i = 1; i < size; i++)
    {
        int temp = arr[i];
        int j;
        for (j = i - 1; j >= 0 && arr[j] > temp; j--)
        {
            count++;
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
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
    count = insertionSort(A, 100);
    printf("Sorted:\n");
    print(A);
    printf("Number of comparisons: %d\n", count);

    descended(A);
    printf("\nCase 2) Already sorted array:\n");
    print(A);
    count = insertionSort(A, 100);
    printf("Sorted:\n");
    print(A);
    printf("Number of comparisons: %d\n", count);

    ascended(A);
    printf("\nCase 3) Reversely sorted array:\n");
    print(A);
    count = insertionSort(A, 100);
    printf("Sorted:\n");
    print(A);
    printf("Number of comparisons: %d\n", count);

    return 0;
}