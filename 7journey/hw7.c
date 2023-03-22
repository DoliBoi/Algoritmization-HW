#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define ERROR 1

typedef struct Node Node;
struct Node{
    int isStart;
    int index;
    int level;
    int num_of_next_cities;
    int next_cities[1000];
    int next_cities_cost[1000];
    int num_of_prev_cities;
    int prev_cities[1000];
    int prev_cities_cost[1000];
    int distance;
    int previous;
    int start[10];
    int start_distance[10];
};




struct Node* make_node(int index) {
    struct Node* node = malloc(sizeof(struct Node));
    node->level = node->num_of_next_cities = node->num_of_prev_cities = node->previous  = node->distance = 0;
    node->isStart = -1;
    node->index = index;
    for(int i = 0; i < 10; i++) {
        node->start_distance[i] = -1;
    }

    return node;
}


typedef struct { 
    int front, rear; 
    int size;
    int capacity;
    struct Node* next[10000];
}Queue; 

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

void topologicalSorting(Node* graph[], Node* sortedGraph[], int numOfCities, int starts[], int numOfStarts){
    Queue* q = createQueue();
    for (int i = 0; i < numOfStarts; i++)
    {
        enQueue(q, graph[starts[i]]);
    }
    Node* temp;
    int index = 0;

    while(!is_empty(q)) {
        temp = deQueue(q);
        for(int i = 0; i < temp->num_of_next_cities; i++) {
            if(graph[temp->next_cities[i]]->isStart >= 0){
                graph[numOfCities+graph[temp->next_cities[i]]->isStart]->level --;
                if ( graph[numOfCities+graph[temp->next_cities[i]]->isStart]->level == 0)
            {
                enQueue(q, graph[numOfCities+graph[temp->next_cities[i]]->isStart]);
            }

            } else{
            graph[temp->next_cities[i]]->level--;
            if (graph[temp->next_cities[i]]->level == 0)
            {
                enQueue(q, graph[temp->next_cities[i]]);
            }
            }
        }
        sortedGraph[index] = temp;
        index ++;

    }
    free(q);
}

void distanceFromStarts(Node* graph[], Node* sortedGraph[], int numOfCities, int starts[], int numOfStarts) {
    Node* temp, *temp2;
    for (int i = numOfStarts-1; i < numOfCities+numOfStarts; i++)
    {
        temp = graph[sortedGraph[i]->index];
        for(int a = 0; a < temp->num_of_prev_cities; a++) {
            temp2 = graph[temp->prev_cities[a]];
            //printf("im here");
            for(int b = 0; b < numOfStarts; b++) {
                if(temp2->start_distance[b]<0)
                continue;
                if (a > 0)
                {
                    if(temp2->start_distance[b]+temp->prev_cities_cost[a] < temp->start_distance[b] || temp->start_distance[b] < 0)
                    graph[sortedGraph[i]->index]->start_distance[b] = temp2->start_distance[b]+temp->prev_cities_cost[a];
                    
                    
                } else {
                    graph[sortedGraph[i]->index]->start_distance[b] = temp2->start_distance[b]+temp->prev_cities_cost[a];
                    //printf("imb here");
                }
                
            }

        }
    }
    
}

/*
int distanceOfTravel(int **sheet, int reps, int numOfStarts){
    int list[reps*numOfStarts];
    for(int i = 0; i < numOfStarts; i++) {
        list[i] = -1;
        for (int j = 0; j < numOfStarts; j++)
        {   if(sheet[j][i%numOfStarts]<0)
                continue;

            if(list[i] == -1)
            list[i] = sheet[j][i%numOfStarts];
            else {
                if(list[i] > sheet[j][i%numOfStarts])
                list[i] = sheet[j][i%numOfStarts];
            }
        }
        
    }
    for(int i = numOfStarts-1; i < reps*numOfStarts; i++) {
        list[i] = -1;
        for (int j = 0; j < numOfStarts; j++)
        {
            if(sheet[j][i%numOfStarts]<0)
                continue;
            
            if(list[i] == -1)
            list[i] = sheet[j][i%numOfStarts] + list[i-numOfStarts-i%numOfStarts+j];
            if(list[i]> sheet[j][i%numOfStarts] + list[i-numOfStarts-i%numOfStarts+j])
            list[i] = sheet[j][i%numOfStarts] + list[i-numOfStarts-i%numOfStarts+j];

        }
        
    }

    int min = list[reps*numOfStarts-1];

    for(int i = reps*numOfStarts - 1; i > (reps-1)*numOfStarts-1; i++){
        if(min > list[i])
        min = list[i];
    }

    return min;


}
*/

int main(int argc, char const *argv[]) {
    int numOfCities, numOfPaths, numOfStarts, numOfReps;
    int from, to, cost;
    if(scanf("%d %d %d %d", &numOfCities, &numOfPaths, &numOfStarts, &numOfReps) != 4) {
        fprintf (stderr, "Error: Chybny vstup!\n");
        return ERROR;
    }
    int starts[numOfStarts];
    Node* graph[numOfCities+numOfStarts];
    Node* sortedGraph[numOfCities+numOfStarts];
    
    

    for(int i = 0; i < numOfStarts; i++) {
        if(scanf("%d", &starts[i])!= 1){
            fprintf (stderr, "Error: Chybny vstup!\n");
            return ERROR;
    }
    starts[i] --;
    }

    for (int i = 0; i < numOfCities+numOfStarts; i++)
    {
        graph[i] = make_node(i);
        for (int j = 0; j < numOfStarts; j++)
        {
            graph[i]->start[j] = starts[j];
        }
        
    }

    for (int i = 0; i < numOfPaths; i++)
    {
        if(scanf("%d %d %d", &from, &to, &cost) != 3){
            fprintf (stderr, "Error: Chybny vstup!\n");
            return ERROR;
    }
        from--;
        to--;
        graph[from]->next_cities[graph[from]->num_of_next_cities] = to;
        graph[from]->next_cities_cost[graph[from]->num_of_next_cities] = cost;
        graph[from]->num_of_next_cities++;
        graph[to]->prev_cities[graph[to]->num_of_prev_cities] = from;
        graph[to]->prev_cities_cost[graph[to]->num_of_prev_cities] = cost;
        graph[to]->num_of_prev_cities++;
        graph[to]->level++;
    }
    
    for(int i = 0; i < numOfStarts; i++) {
        graph[starts[i]]->isStart = i;
        graph[starts[i]]->start_distance[i] = 0;
        graph[numOfCities+i]->level = graph[starts[i]]->level;
        for (int j = 0; j < graph[starts[i]]->num_of_prev_cities; j++)
        {
        graph[numOfCities+i]->prev_cities[j] = graph[starts[i]]->prev_cities[j];
        graph[numOfCities+i]->prev_cities_cost[j] = graph[starts[i]]->prev_cities_cost[j];
        graph[numOfCities+i]->num_of_prev_cities++;
        }
        
    }
    topologicalSorting(graph, sortedGraph, numOfCities, starts, numOfStarts);
    distanceFromStarts(graph, sortedGraph, numOfCities, starts, numOfStarts);

    int sheet[numOfStarts][numOfStarts];

    for (int i = 0; i < numOfStarts; i++)
    {
        for (int j = 0; j < numOfStarts; j++)
        {
            sheet[j][i]=graph[numOfCities + i]->start_distance[j];
        }
        
    }

    for (int i = 0; i < numOfCities+numOfStarts; i++)
    {
        free(graph[i]);
        
    }
//---------------------------------------------------------------------------------------
    int list[numOfReps*numOfStarts];
    for(int i = 0; i < numOfStarts; i++) {
        list[i] = -1;
        for (int j = 0; j < numOfStarts; j++)
        {   if(sheet[j][i%numOfStarts]<0)
                continue;

            if(list[i] == -1)
            list[i] = sheet[j][i%numOfStarts];
            else {
                if(list[i] > sheet[j][i%numOfStarts])
                list[i] = sheet[j][i%numOfStarts];
            }
        }
       // printf("list: %d index: %d", list[i], i);
        
    }
    //printf("\n");
    for(int i = numOfStarts; i < numOfReps*numOfStarts; i++) {
        list[i] = -1;
        for (int j = 0; j < numOfStarts; j++)
        {
            if(sheet[j][i%numOfStarts]<0)
                continue;
            
            if(list[i] == -1)
            list[i] = sheet[j][i%numOfStarts] + list[i-numOfStarts-i%numOfStarts+j];
            if(list[i]> sheet[j][i%numOfStarts] + list[i-numOfStarts-i%numOfStarts+j])
            list[i] = sheet[j][i%numOfStarts] + list[i-numOfStarts-i%numOfStarts+j];

        }
        
    }

    int min = list[numOfReps*numOfStarts-1];

    for(int i = 0; i < numOfStarts; i++){
        if(min > list[numOfReps*numOfStarts-i-1])
        min = list[numOfReps*numOfStarts-i-1];
    }

    
    //--------------------------------------------------------------------------
   /* printf("list: ");
    for (int i = 0; i < numOfReps*numOfStarts; i++)
    {
        printf("%d ", list[i]);
    }
    printf("\n");*/
    
    printf("%d\n", min);
    
   /* for (int i = 0; i < numOfStarts; i++)
    {   
        for (int j = 0; j < numOfStarts; j++)
        {
            printf("%d ", sheet[i][j]);
        }
        printf("\n");
    }
*/

    return 0;

}
