#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 1
#define BLACK 0

typedef struct Node
{
    int key;
    int color;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct RBT
{
    Node *root;
    Node *nil;
    int leftcount;
    int rightcount;
} RBT;

typedef struct Stack
{
    Node *node;
    int space;
} Stack;

Node *createNode(RBT *T, int k)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = k;
    node->color = RED;
    node->parent = T->nil;
    node->left = T->nil;
    node->right = T->nil;
    return node;
}


void Left_Rotate(RBT *T, Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != T->nil)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == T->nil)
    {
        T->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    T->leftcount++;
}

void Right_Rotate(RBT *T, Node *x)
{
    Node *y = x->left;
    x->left = y->right;
    if (y->right != T->nil)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == T->nil)
    {
        T->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    x->right = x;
    x->parent = y;
    T->rightcount++;
}

void Insert_Fixup(RBT *T, Node *z)
{
    Node *y = (Node *)malloc(sizeof(Node));
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    Left_Rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                Right_Rotate(T, z->parent->parent);
            }
        }
        else
        {
            y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    Right_Rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                Left_Rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

void Insert(RBT *T, int k)
{
    Node *z = createNode(T, k);
    Node *y = T->nil;
    Node *x = T->root;
    while (x != T->nil)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else if (z->key > x->key)
        {
            x = x->right;
        }
        else
        {
            return;
        }
    }
    z->parent = y;
    if (y == T->nil)
    {
        T->root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;
    Insert_Fixup(T, z);
}

void Transplant(RBT *T, Node *u, Node *v)
{
    if (u->parent == T->nil)
    {
        T->root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
    if (v != T->nil)
        v->parent = u->parent;
}

void Delete_Fixup(RBT *T, Node *x)
{
    Node *w = (Node *)malloc(sizeof(Node));
    while (x != T->root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                Left_Rotate(T, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    Right_Rotate(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                Left_Rotate(T, x->parent);
                x = T->root;
            }
        }
        else
        {
            w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                Right_Rotate(T, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    Left_Rotate(T, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                Right_Rotate(T, x->parent);
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}

void Delete(RBT *T, int k)
{
    Node *z = T->root;
    while (z != T->nil && z->key != k)
    {
        if (k < z->key)
        {
            z = z->left;
        }
        else
        {
            z = z->right;
        }
    }
    if (z == T->nil)
    {
        return;
    }
    Node *y = z;
    int y_original_color = y->color;
    Node *x;
    if (z->left == T->nil)
    {
        x = z->right;
        Transplant(T, z, z->right);
    }
    else if (z->right == T->nil)
    {
        x = z->left;
        Transplant(T, z, z->left);
    }
    else
    {
        x = z->right;
        while (x->left != T->nil)
        {
            x = x->left;
        }
        y = x; // tree minimum
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            Transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK)
    {
        Delete_Fixup(T, x);
    }
}

void print(RBT *T, Node *root)
{
    if (root == T->nil)
        return;

    Stack *stack = malloc(100 * sizeof(Stack));
    int top = -1;
    int initial = 60;
    int between = 10;

    stack[++top] = (Stack){root, initial};

    while (top != -1)
    {
        Stack temp = stack[top--];
        Node *current = temp.node;
        int space = temp.space;
        char color;
        if (current->color == RED)
            color = 'R';
        else
            color = 'B';
        printf("\n");
        for (int i = 0; i < space; i++)
            printf(" ");
        printf("%d(%c)", current->key, color);

        if (current->right != T->nil)
        {
            stack[++top] = (Stack){current->right, space + between};
        }
        if (current->left != T->nil)
        {
            stack[++top] = (Stack){current->left, space - between};
        }
    }
    free(stack);
    printf("\n");
}

int main()
{
    srand(time(NULL));
    RBT *T = (RBT *)malloc(sizeof(RBT));
    T->nil = (Node *)malloc(sizeof(Node));
    T->nil->color = BLACK;
    T->nil->left = NULL;
    T->nil->right = NULL;
    T->nil->parent = NULL;
    T->nil->key = 0;
    T->root = T->nil;
    T->leftcount = 0;
    T->rightcount = 0;

    int A[10] = {0};
    for (int i = 0; i < 10; i++)
    {
        A[i] = rand() % 20;
        Insert(T, A[i]);
    }
    printf("<Insert 10 random numbers>\n");
    print(T, T->root);
    printf("\n");
    printf("total number of left rotation: %d\n", T->leftcount);
    printf("total number of right rotation: %d\n", T->rightcount);
    Insert(T, 7);
    printf("\n<Insert 7>\n");
    print(T, T->root);
    printf("\n");
    printf("total number of left rotation: %d\n", T->leftcount);
    printf("total number of right rotation: %d\n", T->rightcount);
    Insert(T, 12);
    printf("\n<Insert 12>\n");
    print(T, T->root);
    printf("\n");
    printf("total number of left rotation: %d\n", T->leftcount);
    printf("total number of right rotation: %d\n", T->rightcount);
    Insert(T, 2);
    printf("\n<Insert 2>\n");
    print(T, T->root);
    printf("\n");
    printf("total number of left rotation: %d\n", T->leftcount);
    printf("total number of right rotation: %d\n", T->rightcount);
    Insert(T, 18);
    printf("\n<Insert 18>\n");
    print(T, T->root);
    printf("\n");
    printf("total number of left rotation: %d\n", T->leftcount);
    printf("total number of right rotation: %d\n", T->rightcount);
    Insert(T, 16);
    printf("\n<Insert 16>\n");
    print(T, T->root);
    printf("\n");
    printf("total number of left rotation: %d\n", T->leftcount);
    printf("total number of right rotation: %d\n", T->rightcount);
    Delete(T, 18);
    printf("\n<Delete 18>\n");
    print(T, T->root);
    printf("\n");
    printf("total number of left rotation: %d\n", T->leftcount);
    printf("total number of right rotation: %d\n", T->rightcount);
    Delete(T, T->root->key);
    printf("\n<Delete root>\n");
    print(T, T->root);
    printf("\n");
    printf("total number of left rotation: %d\n", T->leftcount);
    printf("total number of right rotation: %d\n", T->rightcount);
    Delete(T, 2);
    printf("\n<Delete 2>\n");
    print(T, T->root);
    printf("\n");
    printf("total number of left rotation: %d\n", T->leftcount);
    printf("total number of right rotation: %d\n", T->rightcount);
    Delete(T, T->root->key);
    printf("\n<Delete root>\n");
    print(T, T->root);
    printf("\n");
    printf("total number of left rotation: %d\n", T->leftcount);
    printf("total number of right rotation: %d\n", T->rightcount);
    Delete(T, T->root->key);
    printf("\n<Delete root>\n");
    print(T, T->root);
    printf("\n");
    printf("total number of left rotation: %d\n", T->leftcount);
    printf("total number of right rotation: %d\n", T->rightcount);

    return 0;
}
