#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



int main(int argc, char *argv[]) { 
    long int width, distance,
        on_side = 0, num_a, num_b, index_a = 0, index_b =  0, i;
    
    long int count = 0;
    if (scanf ("%ld %ld" , &width, &distance) != 2) {
      fprintf (stderr, "Error: Chybny vstup!\n");
      return 100;
    }
    width = width*width;
    if (scanf ("%ld" , &num_a) != 1) {
      fprintf (stderr, "Error: Chybny vstup!\n");
      return 100;
    }
    long int * side_a = (long int *)malloc( num_a * sizeof(long int) );
    for (i = 0; i < num_a; i++)
    {
       if( scanf("%ld", &side_a[i]) != 1) {
            free( side_a );
            return 1;
       }
    }
    //scanning side a

    if (scanf ("%ld" , &num_b) != 1) {
      //fprintf (stderr, "Error: Chybny vstup!\n");
      return 100;
    }

    long int * side_b = (long int *)malloc( num_b * sizeof(long int) );
    for (i = 0; i < num_b; i++)
    {
        if( scanf("%ld", &side_b[i]) != 1) {
            free( side_b );
            return 1;
       }
    }
    //scanning side a


    while (index_a != num_a || index_b != num_b)
    {
    
    if ( index_a == num_a) {
        on_side = 1;
    } else if (index_b == num_b)
    {
        on_side = 0;
    } else if (side_a[index_a] >= side_b[index_b])
    {
        on_side = 1;
    } else
    {
        on_side = 0;
    }
    
    
    
    switch (on_side)
    {
    case 0:
        for (i = index_a + 1; i < num_a; i++)
        {
            //printf("check count same a > %ld %ld\n", index_a, i);
            if ((side_a[index_a] + distance) >= side_a[i])
            {
                count += 1;
                //printf("check count same a > %ld\n", count);
            } else {
                break;
            }
        }
        for ( i = index_b; i < num_b; i++)
        {
            if ((long double)distance >= sqrt(pow((side_b[i]-side_a[index_a]), 2)+width))
            {
                count += 1;
                //printf("check count cross a > %ld\n", count);
            } else {
                break;
            }
        }
        index_a += 1;
        
        break;

    case 1:
        for (i = index_b + 1; i < num_b; i++)
        {
            if ((side_b[index_b] + distance) >= side_b[i])
            {
                count += 1;
                //printf("check count same b > %ld\n", count);
            } else {
                break;
            }
        }
        for ( i = index_a; i < num_a; i++)
        {
            if ((long double)distance >= sqrt(pow((side_a[i]-side_b[index_b]), 2)+width))
            {
                count += 1;
            } else {
                break;
            }
        }
        index_b += 1;
        break;

    default:
        break;
    }
    }
    printf("%ld\n", count);
    free(side_a);
    free(side_b);
    return 0;
}