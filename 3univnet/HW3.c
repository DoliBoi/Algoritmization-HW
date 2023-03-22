#include <stdio.h>
#include <stdlib.h>
#define RED 1
#define BLUE 2
#define NO_NEIGHBOR -1
#define MAX_NODES 30
#define ERROR 1
volatile int paths = 0;

typedef struct {
    int num_of_neighbors;
    int neighbors[3];
    int type;
    int visited;
} Node;

Node* make_node(int num_of_nodes) {
    Node* node = malloc(sizeof(Node));
    for (int i = 0; i < 3; i++)
    {
        node->neighbors[i] = NO_NEIGHBOR;
    }
    node->type = 0;
    node->visited = 0;
    node->num_of_neighbors = 0;
    return node;
}
void print_node(Node* n) {
    printf("Neighbors:");
    for (int i = 0; i < n->num_of_neighbors; i++)
    {
        printf(" %d", n->neighbors[i]);
    }
    printf("\n");
    printf("%d\n", n->num_of_neighbors); 
    printf("Colour: %d \n", n->type);
    
}

int rec(Node* n[], int node_index) {
    if(n[node_index]->visited == 1)
        return 0;
    //printf("node index: %d\n", node_index);
    n[node_index]->visited = 1;
    if (n[node_index]->num_of_neighbors==1)
    {
        return n[node_index]->type;
    }
    int child_1 = 0, child_2 = 0;
    if (n[node_index]->num_of_neighbors == 3) {
        if(n[n[node_index]->neighbors[0]]->visited == 1){
            child_1 = rec(n, n[node_index]->neighbors[1]);
            child_2 = rec(n, n[node_index]->neighbors[2]);
        } else if (n[n[node_index]->neighbors[1]]->visited == 1)
        {
            child_1 = rec(n, n[node_index]->neighbors[0]);
            child_2 = rec(n, n[node_index]->neighbors[2]);
        } else
        {
            child_1 = rec(n, n[node_index]->neighbors[0]);
            child_2 = rec(n, n[node_index]->neighbors[1]);
        }
        
        } else
    {
        child_1 = rec(n, n[node_index]->neighbors[0]);
        child_2 = rec(n, n[node_index]->neighbors[1]);
    }

        if(child_2 == child_1)
            return child_2;
        if(child_2+child_1 == 3)
        {
            paths++;
            return 0;
        }
        else//if (child_2 + child_1 == child_2 || child_2 + child_1 == child_1)
        {
            return (child_2+child_1);
        }
    
    }
    
    


int main(int argc, char const *argv[])
{
    int num_of_nodes, num_of_edges, num_of_extractors, num_of_validators, x, y, root_index = 0;
    if(scanf("%d %d %d %d", &num_of_nodes, &num_of_edges, &num_of_extractors, &num_of_validators) != 4) {
        fprintf (stderr, "Error: Chybny vstup!\n");
        return ERROR;
    }

    Node *list_of_nodes[num_of_nodes+1];

    for (int i = 0; i < num_of_nodes; i++)
    {
        list_of_nodes[i] = make_node(num_of_nodes);
    }
//zapisu si hrany a sousedy   
    for (int i = 0; i < num_of_edges; i++)
    {
        if(scanf("%d %d", &x, &y)!=2){
            fprintf (stderr, "Error: Chybny vstup!\n");
            return ERROR;
        }
        x -=1; y -=1;
        //printf("x: %d y:%d \n", x, y);
        list_of_nodes[x]->neighbors[list_of_nodes[x]->num_of_neighbors] = y;
        list_of_nodes[x]->num_of_neighbors += 1;
        list_of_nodes[y]->neighbors[list_of_nodes[y]->num_of_neighbors] = x;
        list_of_nodes[y]->num_of_neighbors += 1;
    }
//zapisu si extractory
    for (int i = 0; i < num_of_extractors; i++)
    {
        if(scanf("%d ", &x)!=1){
            fprintf (stderr, "Error: Chybny vstup!\n");
            return ERROR;
        }
        x -=1;
        list_of_nodes[x]->type = RED;
    }
//zapisu validatory
    for (int i = 0; i < num_of_validators; i++)
    {
        if(scanf("%d ", &x)!=1){
            fprintf (stderr, "Error: Chybny vstup!\n");
            return ERROR;
        }
        x -=1;
        list_of_nodes[x]->type = BLUE;
    }
//najdu koren
    for (int i = 0; i < num_of_nodes; i++)
    {   if (list_of_nodes[i]->num_of_neighbors == 2)
    {
        root_index = i;
        break;
    }
    }
    //printf("nodes: %d \n", num_of_nodes);
    /*for (int i = 0; i < num_of_nodes; i++)
    {
        print_node(list_of_nodes[i]);
    }*/
    
//pustim rekurzi
    rec(list_of_nodes, root_index);
    printf("%d\n", paths);


    for (int i = 0; i < num_of_nodes; i++)
    {
        free(list_of_nodes[i]);
    }
    
    return 0;
}