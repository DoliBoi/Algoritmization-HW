#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ERROR 1

int min(int num1, int num2)
{
    return (num1 < num2 ) ? num1 : num2;
}

int maxProfit(int pathCost, int numOfTowns, int towns[][numOfTowns], int profit[][numOfTowns], int x, int y) {
    int sum = 0, a = 0, b = 0, possibleProfit = 0, max = 0;
    for (int j = 0; j < y; j++) {
        a = towns[x][y-j-1];
        b = towns[x+y-j][j];
        sum = a + b;
        if (abs(sum) < abs(a) || abs(sum) < abs(b)){
            //printf("a: %d b: %d\n", a, b);
            possibleProfit = min(abs(a),abs(b))-(y);
            if(possibleProfit < 0)
            possibleProfit = 0;
            possibleProfit += profit[x][y-j-1] + profit[x+y-j][j] - pathCost;
        } else {
            possibleProfit = profit[x][y-j-1] + profit[x+y-j][j] - pathCost;
        }

        if (possibleProfit > max || j == 0)
        max = possibleProfit;
    }
    //printf("max: %d\n", max);
    return max;
}



int main(int argc, char const *argv[]) {
    int numOfTowns, mainTown, pathCost, result = 0;
    int x;
    if(scanf("%d %d %d", &numOfTowns, &mainTown, &pathCost) != 3) {
        fprintf (stderr, "Error: Chybny vstup!\n");
        return ERROR;
    }
    mainTown --;
    x = numOfTowns;
    int towns[x][x];
    int profit[x][x];

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < x; j++)
        {
            profit[i][j] = towns[i][j] = 0;
        }
    }
    

    for (int i = 0; i < numOfTowns; i++) {
        if(scanf("%d", &towns[i][0])!= 1){
            fprintf (stderr, "Error: Chybny vstup!\n");
            return ERROR;
        }
    }

    for (int j = 1; j < numOfTowns; j++) {
        for(int i = 0; i < numOfTowns - j; i++){
            towns[i][j] = towns[i][j-1] + towns[i+j][0];
            profit[i][j] = maxProfit(pathCost, numOfTowns, towns, profit, i, j);

            if(i <= mainTown && i + j >= mainTown){
                if(profit[i][j] > result)
                result = profit[i][j];
            }
        }
    }

    printf("%d \n", result);
    /*for (int j = 0; j < numOfTowns; j++) {
        for(int i = 0; i < numOfTowns - j; i++){
            printf("%d ",profit[i][j]);
        }
        printf("\n");
    }*/



    return 0;
}