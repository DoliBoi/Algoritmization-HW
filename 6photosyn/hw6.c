#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define ERROR 1

typedef struct node Node;

struct node {
    int data;
    int myMin;
    int myMax;
    int score;
};

struct node* newNode(int data) 
{ 
    struct node* temp 
        = (struct node*)malloc(sizeof(struct node)); 
    temp->data = data; 
    temp->myMin = -1; 
    temp->myMax = -1;
    temp->score = 0;
    return temp; 
} 

int min(int num1, int num2)
{
    return (num1 < num2 ) ? num1 : num2;
}

int highestScore = 0;

int main(int argc, char const *argv[]) {
    int numOfData, temp;

    if(scanf("%d", &numOfData) != 1) {
        fprintf (stderr, "Error: Chybny vstup!\n");
        return ERROR;
    }

    Node* tempData[numOfData];

    for(int i = 0; i < numOfData; i++) {
        if(scanf("%d", &temp) != 1) {
            fprintf (stderr, "Error: Chybny vstup!\n");
            return ERROR;
        }
        tempData[i] = newNode(temp);
    }

    for (int i = 1; i < numOfData-1; i++)
    {
        if (tempData[i-1]->data >= tempData[i]->data && tempData[i-1]->myMin < 0)
        {
            continue;
        }

        if (tempData[i]->data <= tempData[i-1]->myMin)
        continue;

        if (tempData[i-1]->data < tempData[i]->data && (tempData[i-1]->data <= tempData[i-1]->myMin || tempData[i-1]->myMin < 0))
        {
            tempData[i]->myMin = tempData[i-1]->data; 
        } else if (tempData[i-1]->data >= tempData[i-1]->myMin)
        {
            tempData[i]->myMin = tempData[i-1]->myMin;
        }
        

    }

    for (int i = numOfData-2; i > 0; i--) 
    {           
        if (tempData[i+1]->data <= tempData[i]->data && tempData[i+1]->myMax < 0)
        {
            continue;
        }

        if (tempData[i]->data >= tempData[i+1]->myMax && tempData[i+1]->myMax > 0)
        continue;

        if (tempData[i+1]->data > tempData[i]->data && tempData[i+1]->data >= tempData[i+1]->myMax)
        {
            tempData[i]->myMax = tempData[i+1]->data; 
        } else if (tempData[i+1]->data <= tempData[i+1]->myMax)
        {
            tempData[i]->myMax = tempData[i+1]->myMax;
        }
    }

    for (int i = 1; i < numOfData - 1; i++)
    {   
        if(tempData[i]->myMax < 0 || tempData[i]->myMin < 0)
        continue;

        tempData[i]->score = min((tempData[i]->data - tempData[i]->myMin),(tempData[i]->myMax - tempData[i]->data));
        if (tempData[i]->score > highestScore)
        {
            highestScore = tempData[i]->score;
        }
        
    }
    
    printf("%d\n", highestScore);
    
    for (int i = 0; i < numOfData; i++)
    {
        free(tempData[i]);
    }
    
    return 0;

}
