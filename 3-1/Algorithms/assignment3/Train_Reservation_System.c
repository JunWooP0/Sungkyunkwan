#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define MAX_CITIES 26
#define RED 1
#define BLACK 0
#define TRAIN_SPEED 200.0

//RBT
typedef struct Node
{
    int id;
    char name[30];
    char source;
    char destination;
    char departureTime[15];
    int color;

    struct Node *left, *right, *parent;
} Node;

typedef struct RBT
{
    Node *root;
    Node *nil;
    int leftcount;
    int rightcount;
} RBT;

//Stack for print
typedef struct Stack
{
    Node *node;
    int space;
} Stack;

Node *createNode(RBT *T, int id, const char *name, char source, char destination, const char *departureTime)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->id = id;
    strcpy(node->name, name);
    node->source = source;
    node->destination = destination;
    strcpy(node->departureTime, departureTime);
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
    y->right = x;
    x->parent = y;
    T->rightcount++;
}

void Insert_Fixup(RBT *T, Node *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            Node *y = z->parent->parent->right;
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
            Node *y = z->parent->parent->left;
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

void Insert(RBT *T, int id, const char *name, char source, char destination, const char *departureTime)
{
    Node *z = createNode(T, id, name, source, destination, departureTime);
    Node *y = T->nil;
    Node *x = T->root;
    while (x != T->nil)
    {
        y = x;
        if (z->id < x->id)
        {
            x = x->left;
        }
        else if (z->id > x->id)
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
    else if (z->id < y->id)
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

Node *searchReservation(RBT *T, int id)
{
    Node *current = T->root;
    while (current != T->nil && current->id != id)
    {
        if (id < current->id)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return current;
}

void rbTransplant(RBT *T, Node *u, Node *v)
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
}

void Delete_Fixup(RBT *T, Node *x)
{
    while (x != T->root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            Node *w = x->parent->right;
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
                if (w->right != T->nil)
                {
                    w->right->color = BLACK;
                }
                Left_Rotate(T, x->parent);
                x = T->root;
            }
        }
        else
        {
            Node *w = x->parent->left;
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
                if (w->left != T->nil)
                {
                    w->left->color = BLACK;
                }
                Right_Rotate(T, x->parent);
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}

Node *treeMinimum(RBT *T, Node *x)
{
    while (x->left != T->nil)
    {
        x = x->left;
    }
    return x;
}

void rbDelete(RBT *T, Node *z)
{
    Node *y = z;
    Node *x;
    int y_original_color = y->color;
    if (z->left == T->nil)
    {
        x = z->right;
        rbTransplant(T, z, z->right);
    }
    else if (z->right == T->nil)
    {
        x = z->left;
        rbTransplant(T, z, z->left);
    }
    else
    {
        y = treeMinimum(T, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            rbTransplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(T, z, y);
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
        char color = (current->color == RED) ? 'R' : 'B';
        printf("\n");
        for (int i = 0; i < space; i++)
            printf(" ");
        printf("%d(%c)", current->id, color);

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

int compareTimes(const void *a, const void *b);

void generateRandomTime(char *time);

// Graph
typedef struct GraphNode
{
    int dest;
    struct GraphNode *next;
    char departureTimes[31][5][10];
    double distance;                
    double travelTime;             
} GraphNode;

typedef struct Graph
{
    GraphNode *head[MAX_CITIES];
} Graph;

GraphNode *createGraphNode(int dest, double distance, double travelTime)
{
    GraphNode *newNode = (GraphNode *)malloc(sizeof(GraphNode));
    newNode->dest = dest;
    newNode->next = NULL;
    newNode->distance = distance;
    newNode->travelTime = travelTime;
    return newNode;
}

Graph *createGraph()
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    for (int i = 0; i < MAX_CITIES; i++)
        graph->head[i] = NULL;
    return graph;
}

void addEdge(Graph *graph, int source, int dest, double distance)
{
    double travelTime = distance / TRAIN_SPEED;
    GraphNode *newNode = createGraphNode(dest, distance, travelTime);
    newNode->next = graph->head[source];
    graph->head[source] = newNode;

    for (int day = 0; day < 31; day++)
    {
        for (int i = 0; i < 5; i++)
        {
            generateRandomTime(newNode->departureTimes[day][i]);
        }
        // Sort the departure times
        qsort(newNode->departureTimes[day], 5, sizeof(newNode->departureTimes[day][0]), compareTimes);
    }
}

void printGraph(Graph *graph)
{
    for (int i = 0; i < MAX_CITIES; i++)
    {
        GraphNode *ptr = graph->head[i];
        if (ptr)
        {
            printf("City %c:\n", 'a' + i);
            while (ptr)
            {
                printf("City %c -> City %c\n", 'a' + i, 'a' + ptr->dest);
                printf("  Distance: %.2f km, Travel Time: %.2f hours\n", ptr->distance, ptr->travelTime);
                for (int day = 0; day < 31; day++)
                {
                    printf("  Day %d: ", day + 1);
                    for (int j = 0; j < 5; j++)
                    {
                        printf("%s ", ptr->departureTimes[day][j]);
                    }
                    printf("\n");
                }
                ptr = ptr->next;
            }
        }
    }
}

RBT reservationTree;
Graph *graph;

typedef struct City
{
    char name;
    int x, y;
} City;

City cities[MAX_CITIES];

typedef struct DepartureTime
{
    int day;
    char time[10];
} DepartureTime;

DepartureTime departureTimes[MAX_CITIES][10][31][5];

void generateRandomTime(char *time)
{
    int hour = rand() % 24;
    int minute = (rand() % 4) * 15;
    sprintf(time, "%02d:%02d", hour, minute);
}

void generateCityLocations()
{
    for (int i = 0; i < MAX_CITIES; i++)
    {
        cities[i].name = 'a' + i;
        cities[i].x = rand() % 1001;
        cities[i].y = rand() % 1001;
    }
}

double calculateDistance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int existPath(int source, int dest, Graph *graph)
{
    GraphNode *ptr = graph->head[source];
    while (ptr)
    {
        if (ptr->dest == dest)
            return 1;
        ptr = ptr->next;
    }
    return 0;
}

void generatePaths(Graph *graph)
{
    for (int i = 0; i < MAX_CITIES; i++)
    {
        int pathCount = 0;
        while (pathCount < 10)
        {
            int dest = rand() % MAX_CITIES;
            if (dest != i && !existPath(i, dest, graph))
            {
                double distance = calculateDistance(cities[i].x, cities[i].y, cities[dest].x, cities[dest].y);
                addEdge(graph, i, dest, distance);
                pathCount++;
            }
        }
    }
}

void generateDepartureTimes()
{
    for (int city = 0; city < MAX_CITIES; city++)
    {
        for (int path = 0; path < 10; path++)
        {
            for (int day = 0; day < 31; day++)
            {
                for (int i = 0; i < 5; i++)
                {
                    departureTimes[city][path][day][i].day = day + 1;
                    generateRandomTime(departureTimes[city][path][day][i].time);
                }
                qsort(departureTimes[city][path][day], 5, sizeof(departureTimes[city][path][day][0]), compareTimes);
            }
        }
    }
}

void printDepartureTimes()
{
    for (int city = 0; city < MAX_CITIES; city++)
    {
        for (int path = 0; path < 10; path++)
        {
            for (int day = 0; day < 31; day++)
            {
                printf("City %c, Path %d, Day %d: ", 'a' + city, path, day + 1);
                for (int i = 0; i < 5; i++)
                {
                    printf("%s ", departureTimes[city][path][day][i].time);
                }
                printf("\n");
            }
        }
    }
}

int timeToMinutes(const char *time)
{
    int hours, minutes;
    sscanf(time, "%d:%d", &hours, &minutes);
    return hours * 60 + minutes;
}

int compareTimes(const void *a, const void *b)
{
    char *timeA = (char *)a;
    char *timeB = (char *)b;
    int minutesA = timeToMinutes(timeA);
    int minutesB = timeToMinutes(timeB);
    return minutesA - minutesB;
}

bool search(Graph *graph, int currentCity, int destination, int day, int currentTime, char *result, bool *visited)
{
    visited[currentCity] = true;

    if (currentCity == destination)
    {
        return true;
    }

    GraphNode *ptr = graph->head[currentCity];
    while (ptr)
    {
        if (!visited[ptr->dest])
        {
            char buffer[100];
            sprintf(buffer, " -> %c", 'a' + ptr->dest);
            strcat(result, buffer);

            if (search(graph, ptr->dest, destination, day, currentTime, result, visited))
            {
                return true;
            }

            result[strlen(result) - strlen(buffer)] = '\0';
        }
        ptr = ptr->next;
    }

    visited[currentCity] = false;
    return false;
}

void findPath(int source, int destination, int day, int currentTime, char *result)
{
    bool visited[MAX_CITIES] = {false};
    search(graph, source, destination, day, currentTime, result, visited);
}

void calculateArrivalTime(int day, int departureMinutes, double travelTime, int *arrivalDays, char *arrivalTime)
{
    int travelMinutes = (int)(travelTime * 60);
    int arrivalMinutes = departureMinutes + travelMinutes;
    int arrivalHours = arrivalMinutes / 60;
    *arrivalDays = day + (arrivalHours / 24);
    arrivalMinutes %= 60;
    arrivalHours %= 24;

    if (*arrivalDays > 29)
        *arrivalDays -= 29;

    sprintf(arrivalTime, "%02d:%02d", arrivalHours, arrivalMinutes);
}

void createReservation()
{
    int id;
    char name[30], source, destination, departureTime[10];
    int day;

    printf("Enter reservation ID: ");
    scanf("%d", &id);
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter source (a-z): ");
    scanf(" %c", &source);
    printf("Enter destination (a-z): ");
    scanf(" %c", &destination);

    printf("Enter departure day (1-29): ");
    scanf("%d", &day);
    if (day < 1 || day > 29)
    {
        printf("Invalid day. Please choose a day between 1 and 29.\n");
        return;
    }

    int sourceIndex = source - 'a';
    int destIndex = destination - 'a';

    if (sourceIndex < 0 || sourceIndex >= MAX_CITIES || destIndex < 0 || destIndex >= MAX_CITIES)
    {
        printf("Invalid source or destination.\n");
        return;
    }

    GraphNode *path = NULL;
    GraphNode *ptr = graph->head[sourceIndex];

    while (ptr)
    {
        if (ptr->dest == destIndex)
        {
            path = ptr;
            break;
        }
        ptr = ptr->next;
    }

    char travelPath[1000] = "";

    // Check if there is an indirect path
    if (!path)
    {
        char result[1000] = "";
        findPath(sourceIndex, destIndex, day - 1, timeToMinutes("00:00"), result);

        if (strlen(result) == 0)
        {
            printf("No path found between %c and %c.\n", source, destination);
            return;
        }

        printf("Indirect path found: %c%s\n", source, result);

        char *token = strtok(result, " -> ");
        int accumulatedDay = day;
        int accumulatedTime = timeToMinutes("00:00");
        char fullPath[1000] = "";
        bool first = true;

        while (token)
        {
            char city = token[0];
            int cityIndex = city - 'a';
            ptr = graph->head[sourceIndex];

            while (ptr)
            {
                if (ptr->dest == cityIndex)
                {
                    path = ptr;
                    break;
                }
                ptr = ptr->next;
            }

            if (path)
            {
                printf("Available departure times from %c to %c:\n", 'a' + sourceIndex, 'a' + cityIndex);
                for (int i = 0; i < 5; i++)
                {
                    printf("%d. %s\n", i + 1, path->departureTimes[accumulatedDay - 1][i]);
                }

                int timeChoice;
                printf("Choose a departure time (1-5): ");
                scanf("%d", &timeChoice);
                if (timeChoice < 1 || timeChoice > 5)
                {
                    printf("Invalid choice. Please choose a time between 1 and 5.\n");
                    return;
                }

                strcpy(departureTime, path->departureTimes[accumulatedDay - 1][timeChoice - 1]);

                int departureMinutes = timeToMinutes(departureTime);
                char arrivalTime[10];
                int arrivalDays;
                calculateArrivalTime(accumulatedDay, departureMinutes, path->travelTime, &arrivalDays, arrivalTime);

                if (departureMinutes < accumulatedTime)
                {
                    accumulatedDay++;
                    if (accumulatedDay > 29)
                        accumulatedDay -= 29;
                }

                if (first)
                {
                    sprintf(fullPath, "%c(%02d:%02d, %d)", source, departureMinutes / 60, departureMinutes % 60, accumulatedDay);
                    first = false;
                }
                else
                {
                    char segment[100];
                    sprintf(segment, " -> %c(%02d:%02d, %d)", 'a' + sourceIndex, departureMinutes / 60, departureMinutes % 60, accumulatedDay);
                    strcat(fullPath, segment);
                }

                printf("Selected departure time and date: %s, %d\n", departureTime, accumulatedDay);

                if (accumulatedDay > 29)
                    accumulatedDay -= 29;
                accumulatedTime = timeToMinutes(arrivalTime);
                sourceIndex = cityIndex;

                token = strtok(NULL, " -> ");
            }
        }

        char finalSegment[100];
        sprintf(finalSegment, " -> %c(%02d:%02d, %d)", destination, accumulatedTime / 60, accumulatedTime % 60, accumulatedDay);
        strcat(fullPath, finalSegment);

        printf("Reservation Tree (Before Insertion): \n");
        print(&reservationTree, reservationTree.root);
        Insert(&reservationTree, id, name, source, destination, departureTime);
        printf("Reservation Tree (After Insertion): \n");
        print(&reservationTree, reservationTree.root);

        printf("Reservation created successfully.\n");
        printf("Name: %s, Reservation ID: %d, Travel Path: %s\n", name, id, fullPath);

        strcpy(travelPath, fullPath);
    }
    // Direct path
    else if (path)
    {
        printf("Available departure times from %c to %c:\n", 'a' + sourceIndex, destination);
        for (int i = 0; i < 5; i++)
        {
            printf("%d. %s\n", i + 1, path->departureTimes[day - 1][i]);
        }

        int timeChoice;
        printf("Choose a departure time (1-5): ");
        scanf("%d", &timeChoice);
        if (timeChoice < 1 || timeChoice > 5)
        {
            printf("Invalid choice. Please choose a time between 1 and 5.\n");
            return;
        }

        strcpy(departureTime, path->departureTimes[day - 1][timeChoice - 1]);
        printf("\n");

        printf("Reservation Tree (Before Insertion): \n");
        print(&reservationTree, reservationTree.root);
        Insert(&reservationTree, id, name, source, destination, departureTime);
        printf("Reservation Tree (After Insertion): \n");
        print(&reservationTree, reservationTree.root);

        int departureMinutes = timeToMinutes(departureTime);
        int travelMinutes = (int)(path->travelTime * 60);
        int arrivalMinutes = departureMinutes + travelMinutes;
        int arrivalHours = arrivalMinutes / 60;
        int arrivalDays = day + (arrivalHours / 24);
        arrivalMinutes %= 60;
        arrivalHours %= 24;

        if (arrivalDays > 29)
            arrivalDays -= 29;

        char arrivalTime[10];
        sprintf(arrivalTime, "%02d:%02d", arrivalHours, arrivalMinutes);

        printf("Reservation created successfully.\n");
        printf("Name: %s, Reservation ID: %d, Travel Path: %c(%s, %d) -> %c(%s, %d)\n",
               name, id, source, departureTime, day, destination, arrivalTime, arrivalDays);
        
    }
    else
    {
        printf("No path found between %c and %c.\n", source, destination);
    }
}

void viewReservation()
{
    int id;
    printf("Enter reservation ID to view: ");
    scanf("%d", &id);
    Node *reservation = searchReservation(&reservationTree, id);
    if (reservation != reservationTree.nil)
    {
        printf("\n");
        printf("Reservation ID: %d\n", reservation->id);
        printf("Name: %s\n", reservation->name);
        printf("Source: %c\n", reservation->source);
        printf("Destination: %c\n", reservation->destination);
        printf("Departure Time: %s\n", reservation->departureTime);
    }
    else
    {
        printf("Reservation not found.\n");
    }
}
void deleteReservation()
{
    int id;
    printf("Enter reservation ID to delete: ");
    scanf("%d", &id);
    Node *reservation = searchReservation(&reservationTree, id);
    if (reservation != reservationTree.nil)
    {
        print(&reservationTree, reservationTree.root); // Print before deletion
        rbDelete(&reservationTree, reservation);
        print(&reservationTree, reservationTree.root); // Print after deletion
        printf("Reservation deleted successfully.\n");
    }
    else
    {
        printf("Reservation not found.\n");
    }
}

int main()
{
    srand(time(NULL));
    reservationTree.nil = (Node *)malloc(sizeof(Node));
    reservationTree.nil->color = BLACK;
    reservationTree.nil->left = NULL;
    reservationTree.nil->right = NULL;
    reservationTree.nil->parent = NULL;
    reservationTree.nil->id = 0;
    reservationTree.root = reservationTree.nil;
    reservationTree.leftcount = 0;
    reservationTree.rightcount = 0;

    generateCityLocations();
    graph = createGraph();
    generatePaths(graph);
    generateDepartureTimes();

    // Print the graph at the start
    printGraph(graph);

    int choice;

    while (1)
    {
        printf("\n*** Train Reservation System ***\n");
        printf("1. Make a Reservation\n");
        printf("2. View Reservations\n");
        printf("3. Cancel a Reservation\n");
        printf("4. View All Travel Paths\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createReservation();
            break;
        case 2:
            viewReservation();
            break;
        case 3:
            deleteReservation();
            break;
        case 4:
            printGraph(graph);
            break;
        case 5:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
