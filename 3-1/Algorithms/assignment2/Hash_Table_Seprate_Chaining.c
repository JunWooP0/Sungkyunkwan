#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct HashTable
{
    Node **bucket;
    int num;
} HashTable;

Node *createNode(int key)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = key;
    newNode->next = NULL;
    return newNode;
}

HashTable *createHash(int size)
{
    HashTable *hash = (HashTable *)malloc(sizeof(HashTable));
    hash->bucket = (Node **)malloc(sizeof(Node *) * size);
    for (int i = 0; i < size; i++)
    {
        hash->bucket[i] = NULL;
    }
    hash->num = size;
    return hash;
}
void insert_a(HashTable *hash, int key)
{
    int idx = key % 5;
    Node *newNode = createNode(key);
    newNode->next = hash->bucket[idx];
    hash->bucket[idx] = newNode;
}

void insert_b(HashTable *hash, int key)
{
    int idx = key % 11;
    Node *newNode = createNode(key);
    newNode->next = hash->bucket[idx];
    hash->bucket[idx] = newNode;
}

void print(HashTable *hash)
{
    int longest = 0;
    int total = hash->num;
    int value = 0;
    float sum = 0;
    float average = 0;
    for (int i = 0; i < total; i++)
    {
        int length = 0;
        printf("%d: ", i);
        Node *current = hash->bucket[i];
        while (current != NULL)
        {
            value = current->data;
            // printf("%d -> ", value);
            current = current->next;
            if(current != NULL)
                printf("%d -> ", value);
            else
                printf("%d", value);
            length++;
        }
        if (length > longest)
            longest = length;
        sum += length;
        printf("\n");
    }
    average = sum / total;
    printf("Average Chain Length: %.1f\n", average);
    printf("Longest Chain Length: %d\n", longest);
}

int main()
{
    srand(time(NULL));
    int keys[50];
    int unique = 1;
    int temp = 0;
    for (int i = 0; i < 50; i++)
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
    HashTable *table_a = createHash(5);
    HashTable *table_b = createHash(11);
    for (int i = 0; i < 50; i++)
    {
        insert_a(table_a, keys[i]);
        insert_b(table_b, keys[i]);
    }

    printf("Hash Table a\n");
    print(table_a);
    printf("\nHash Table b\n");
    print(table_b);

    return 0;
}