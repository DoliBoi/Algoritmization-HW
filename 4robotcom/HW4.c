#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NO_NEIGHBOR -1
#define ERROR 1

int volatile counter = 0;

struct Node{
    int row;
    int collumn;
    long int neighbors[4];
    int type;
    int visited;
    long int distance;
};

typedef struct { 
    int front, rear; 
    int size;
    int capacity;
    struct Node* next[10000];
}Queue; 

struct Node* make_node(int rows, int collumns, int index) {
    struct Node* node = malloc(sizeof(struct Node));
    node->type = 0;
    node->visited = 0;
    node->row = index/collumns;
    node->collumn = index%collumns;
    node->distance = 0;
    if(node->collumn != 0){
        node->neighbors[0] = index - 1;
    } else {
        node->neighbors[0] = NO_NEIGHBOR;
    }

    if(node->row != 0){
        node->neighbors[1] = index - collumns;
    } else {
        node->neighbors[1] = NO_NEIGHBOR;
    }

    if(node->collumn != collumns-1){
        node->neighbors[2] = index + 1;
    } else {
        node->neighbors[2] = NO_NEIGHBOR;
    }
    
    if(node->row != rows-1){
        node->neighbors[3] = index + collumns;
    } else {
        node->neighbors[3] = NO_NEIGHBOR;
    }


    //node->num_of_neighbors = 0;
    return node;
}


void print_node(struct Node* n) {
    printf("Neighbors:");
    for (int i = 0; i < 4; i++)
    {
        printf(" %ld", n->neighbors[i]);
    }
    printf("\n");
    printf("Type: %d \n", n->type);
    

    
}

Queue* createQueue() 
{ 
    Queue* q = (Queue*)malloc(sizeof( Queue)); 
    q->front = q->size = 0; 
    q->capacity = 10000;

    q->rear = 9999;
    return q; 
} 

int is_full(Queue* queue) 
{ 
    return (queue->size == queue->capacity); 
} 

int is_empty(Queue* q) {
    return (q->size == 0);
}

void enQueue(Queue* q,struct Node* n) 
{  
  
    if (is_full(q)) 
        return; 
    q->rear = (q->rear + 1) 
                  % q->capacity; 
    q->next[q->rear] = n; 
    q->size = q->size + 1;
} 

struct Node* deQueue(Queue* q) 
{ 
   if (is_empty(q)) 
        return NULL; 
    struct Node* item = q->next[q->front]; 
    q->front = (q->front + 1) 
                   % q->capacity; 
    q->size = q->size - 1; 
    return item; 
}

long int BFS (struct Node* n,struct Node* l[], int max_type) {
    n->visited = 1;
    int search_token;
    long int dist;
    Queue* q = createQueue();
    enQueue(q, n);
    //printf("OK\n");
    while(is_empty(q)!=1) {
        counter++;
        struct Node* temp = deQueue(q);
        search_token = temp->visited;
        dist = temp->distance + 1;
        //print_node(temp);
        for (int i = 0; i < 4; i++) {
            if (temp->neighbors[i] > -1) {
                if(l[temp->neighbors[i]]->visited < search_token) {
                    //printf("Type: %d Search type: %d Counter: %d \n", l[temp->neighbors[i]]->type, search_token, counter);
                    if(l[temp->neighbors[i]]->type  == search_token) {
                        l[temp->neighbors[i]]->visited = search_token + 1;
                        if (search_token == max_type)
                        {   
                            free(q);
                            return dist;
                        }
                        
                    } else
                    {   
                        l[temp->neighbors[i]]->visited = search_token;
                    }
                    
                    l[temp->neighbors[i]]->distance = dist; 
                    enQueue(q, l[temp->neighbors[i]]);
                }
            }
        }
    }
    free(q);
    return ERROR;
}

int main(int argc, char const *argv[])
{
    int r, c, p, type, x, y, start, count;
    if(scanf("%d %d %d %d", &r, &c, &p, &type) != 4) {
        fprintf (stderr, "Error: Chybny vstup!\n");
        return ERROR;
    }

    struct Node *list_of_nodes[r*c];

    for (int i = 0; i < (r*c); i++)
    {
        list_of_nodes[i] = make_node(r, c, i);
    }
    //naskenuju souradnice start
    if(scanf("%d %d", &x, &y) != 2) {
        fprintf (stderr, "Error: Chybny vstup!\n");
        return ERROR;
    }

    start = (r - x) * c + (y - 1);

    //naskenuju a upravim na index souradnice prekazek
    for(int i = 0; i < p; i++) {
        if(scanf("%d %d", &x, &y) != 2) {
            fprintf (stderr, "Error: Chybny vstup!\n");
            return ERROR;
        }

        list_of_nodes[(r - x) * c + (y - 1)]->visited = type + 2;
    }

    //naskenuju typy policek
    for(int i = 0; i < type; i++) {
        if(scanf("%d", &count) != 1) {
            fprintf (stderr, "Error: Chybny vstup!\n");
            return ERROR;
        }
        for (int j = 0; j < count; j++)
        {
            if(scanf("%d %d", &x, &y) != 2) {
                fprintf (stderr, "Error: Chybny vstup!\n");
                return ERROR;
            }   

            list_of_nodes[(r - x) * c + (y - 1)]->type = i+1;
        }
        
    }
//debug
    /*for (int i = 0; i < (r*c); i++)
    {
        print_node(list_of_nodes[i]);
    }*/
    
    printf("%ld\n", BFS(list_of_nodes[start], list_of_nodes, type));
    


    for (int i = 0; i < (r*c); i++)
    {
        free(list_of_nodes[i]);
    }


    return 0;
}