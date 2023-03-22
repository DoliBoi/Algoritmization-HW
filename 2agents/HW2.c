#include <stdio.h>
#include <stdlib.h>
#define RED 1
#define BLUE 2
#define WHITE 0
#define MAX_NODES 30
#define ERROR 1
volatile int top_score = 0;

typedef struct {
    int num_of_neighbor;
    int* neighbor;
    int colour;
    int my_index;
} Node;

Node* make_node(int num_of_nodes) {
    Node* node = malloc(sizeof(Node));
    node->num_of_neighbor= 0;
    node->neighbor = calloc(num_of_nodes, sizeof(int));
    node->colour = WHITE;
    node->my_index = 0;
    return node;
}

void print_node(Node* n) {
    /*printf("Neighbors:");
    for (int i = 0; i < n->num_of_neighbor; i++)
    {
        printf(" %d", n->neighbor[i]);
    }
    printf("\n");
    printf("%d\n", n->num_of_neighbor); */
    printf("Colour: %d \n", n->colour);
    
}

void free_node(Node* n) {
    free(n->neighbor);
    free(n);
}

void sort(Node* n[], int num) {
    int j,i;

    for(i=1;i<num;i++)
    {
        for(j=0;j<num-i;j++)
        {
            if(n[j]->num_of_neighbor <n[j+1]->num_of_neighbor)
            {
                Node* temp = n[j];
                n[j] =n[j+1];
                n[j+1] = temp;
            }
        }
    }
}

int red_score(Node* red_node, Node* n[]) {
    int score = 0;
    for(int i = 0; i < red_node->num_of_neighbor; i++) {
        if (n[red_node->neighbor[i]]->colour == RED)
        score += 2;
    }
    return score;
}

int blue_score(Node* blue_node, Node* n[]) {
    int score = 0;
    for(int i = 0; i < blue_node->num_of_neighbor; i++) {
        if (n[blue_node->neighbor[i]]->colour == RED)
        score += 1;
        if (n[blue_node->neighbor[i]]->colour == BLUE)
        score -= 1;
        if (n[blue_node->neighbor[i]]->colour == WHITE)
        score += 1;
    }
    return score;
}

void rec(Node* sn[], Node* n[], int red, int blue, int white, int temp_score,int index, int num_of_nodes) {
    int possible_score = temp_score;
    int add_score;
    for(int i = 0; i<red; i++) {
        possible_score += (sn[index + i]->num_of_neighbor)*2;
    }
    for (int i = red; i < red + blue; i++)
    {
        possible_score += (sn[index + i]->num_of_neighbor);
    }
    
    //printf("possible score: %d \n", possible_score);
    if(possible_score <= top_score || index == num_of_nodes) {
        return;
    }
    //herudistika
    //podminky
    if (red != 0) {
    red -= 1;
    n[sn[index]->my_index]->colour = RED;
    //printf("Red placed, position: %d ", sn[index]->my_index);
    add_score = red_score(sn[index], n);
    temp_score += add_score;
    //printf("white agents: %d red agents: %d red temp score: %d \n",white, red,  temp_score);
    
    if(temp_score >= top_score){
               /*for (int i = 0; i < num_of_nodes; i++)
    {   
        printf("Node %d: \n",i);
        print_node(n[i]);
    }*/
    top_score = temp_score;}
    rec(sn, n, red, blue, white, temp_score, index+1, num_of_nodes);
    red += 1;
    temp_score -= add_score;
    n[sn[index]->my_index]->colour = WHITE;
    }

    //blue
    if (blue != 0) {
    blue -= 1;
    n[sn[index]->my_index]->colour = BLUE;
    add_score = blue_score(sn[index], n);
    temp_score += add_score;
    //printf("index: %d blue temp score: %d \n",index , temp_score);
    if(temp_score >= top_score){
       /* for (int i = 0; i < num_of_nodes; i++)
            {   
        printf("Node %d: \n",i);
        print_node(n[i]);
    }*/
    top_score = temp_score;}

    rec(sn, n, red, blue, white, temp_score, index+1, num_of_nodes);
    blue += 1;
    temp_score -= add_score;
    n[sn[index]->my_index]->colour = WHITE;
    }    
    if (white != 0 /*&& (red> 0 || blue> 0)*/) {
    white -= 1;
    n[sn[index]->my_index]->colour = WHITE;
    //printf("White placed, position: %d\n", sn[index]->my_index);
    rec(sn, n, red, blue, white, temp_score, index+1, num_of_nodes);
    white+= 1;
    }
}




int main(int argc, char const *argv[])
{
    int num_of_nodes, num_of_edges, agent_red, agent_blue, x, y;
    int agent_white;
    if(scanf("%d %d %d %d", &num_of_nodes, &num_of_edges, &agent_red, &agent_blue) != 4) {
        fprintf (stderr, "Error: Chybny vstup!\n");
        return ERROR;
    }
    agent_white = num_of_nodes - (agent_blue + agent_red);
    Node *list_of_nodes[num_of_nodes], *sorted_list_of_nodes[num_of_nodes];
    //int given_nodes[num_of_nodes];
    for (int i = 0; i < num_of_nodes; i++)
    {
        list_of_nodes[i] = make_node(num_of_nodes);
        sorted_list_of_nodes[i] = make_node(num_of_nodes);
        sorted_list_of_nodes[i] -> my_index = i;
        //given_nodes[i] = WHITE;
    }
    
    for (int i = 0; i < num_of_edges; i++)
    {
        if(scanf("%d %d", &x, &y)!=2){
            fprintf (stderr, "Error: Chybny vstup!\n");
            return ERROR;
        }
        x -=1; y -=1;
        list_of_nodes[x]->neighbor[list_of_nodes[x]->num_of_neighbor] = y;
        list_of_nodes[x]->num_of_neighbor += 1;
        list_of_nodes[y]->neighbor[list_of_nodes[y]->num_of_neighbor] = x;
        list_of_nodes[y]->num_of_neighbor += 1;
        sorted_list_of_nodes[x]->neighbor[sorted_list_of_nodes[x]->num_of_neighbor] = y;
        sorted_list_of_nodes[x]->num_of_neighbor += 1;
        sorted_list_of_nodes[y]->neighbor[sorted_list_of_nodes[y]->num_of_neighbor] = x;
        sorted_list_of_nodes[y]->num_of_neighbor += 1;
    }

    sort(sorted_list_of_nodes, num_of_nodes);

    rec(sorted_list_of_nodes, list_of_nodes,agent_red, agent_blue, agent_white, 0, 0, num_of_nodes);
    printf("%d\n", top_score);
    //debug
    /*for (int i = 0; i < num_of_nodes; i++)
    {   
        printf("Unsorted list:\n");
        print_node(list_of_nodes[i]);
    }
    for (int i = 0; i < num_of_nodes; i++)
    {   
        printf("Sorted list:\n");
        print_node(sorted_list_of_nodes[i]);
    }
    */
    for (int i = 0; i < num_of_nodes; i++)
    {
        free_node(list_of_nodes[i]);
        free_node(sorted_list_of_nodes[i]);
    }
    
    return 0;
}
