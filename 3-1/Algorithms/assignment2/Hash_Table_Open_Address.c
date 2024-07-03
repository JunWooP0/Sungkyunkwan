#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int *table;
    int probes;
} HashTable;

HashTable *createHash()
{
    HashTable *hash = malloc(sizeof(HashTable));
    hash->table = malloc(sizeof(int) * 37);
    for (int i = 0; i < 37; i++)
    {
        hash->table[i] = -1;
    }
    hash->probes = 0;
    return hash;
}

void linear_insert(HashTable *hash, int key)
{
    int idx;
    int h1 = key % 37;
    for (int i = 0; i < 37; i++)
    {
        idx = (h1 + i) % 37;
        if (hash->table[idx] == -1)
        {
            hash->table[idx] = key;
            hash->probes += i;
            hash->probes++;
            return;
        }
    }
}

void double_insert(HashTable *hash, int key)
{
    int idx;
    int h1 = key % 37;
    int h2 = 7 + (key % 30);
    for (int i = 0; i < 37; i++)
    {
        idx = (h1 + i * h2) % 37;
        if (hash->table[idx] == -1)
        {
            hash->table[idx] = key;
            hash->probes += i;
            hash->probes++;
            return;
        }
    }
}

void print_h(HashTable *hash)
{
    for (int i = 0; i < 37; i++)
    {
        if (hash->table[i] != -1)
        {
            printf("%d:'%d' ", i, hash->table[i]);
        }
        else
        {
            printf("%d:__ ", i);
        }
    }
    printf("\n");
}

void print_s(HashTable *hash)
{
    int longest = 0;
    int current = 0;
    float average = 0;
    for (int i = 0; i < 37; i++)
    {
        int value = hash->table[i];
        if (value != -1)
        {
            current++;
            if (current > longest)
            {
                longest = current;
            }
        }
        else
        {
            current = 0;
        }
    }
    average = (float)hash->probes / 30;
    printf("Average number of probes per insertion: %.1f\n", average);
    printf("Primary cluster length: %d\n", longest);
}

int main()
{
    srand(time(NULL));
    int keys[30];
    int unique = 1;
    int temp = 0;
    int data = 0;
    HashTable *linearprobing = createHash();
    HashTable *doublehashing = createHash();

    for (int i = 0; i < 30; i++)
    {
        unique = 1;
        temp = rand() % 500;
        for (int j = 0; j < i; j++)
        {
            if (keys[j] == temp)
            {
                unique = 0;
                break;
            }
        }
        if (unique)
        {
            keys[i] = temp;
        }
        else
        {
            i--;
        }
    }
    for (int i = 0; i < 30; i++)
    {
        data = keys[i];
        linear_insert(linearprobing, data);
        double_insert(doublehashing, data);
    }

    printf("Linear Probing Hash Table\n");
    print_h(linearprobing);
    print_s(linearprobing);
    printf("\nDouble Hashing Hash Table\n");
    print_h(doublehashing);
    print_s(doublehashing);

    return 0;
}