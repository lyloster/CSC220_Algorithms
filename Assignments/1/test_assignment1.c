#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Ilyovska_Assignment1.c"

int common(int A[], int B[], int m, int n);

main()
{   int P[500000];
    int Q[200000];
    int i, t1,t2, result ;
    time_t t;
    srand( (unsigned) time ( &t ) ); /*initialize random numbers */ 
    for( i=0; i< 500000; i++) /* fill P with even numbers */
      P[i] = 2*( (579*i + 234987) % 500000 );
    for( i=0; i< 200000; i++)/* fill Q with odd numbers */
      Q[i] = 2*( (997*i + 98771) % 200000 ) + 1;
    t1 = (rand()%10) + 1;
    t2 = (rand()%10) + 1;
    for(i=0; i< t1; i++) /* put some odd numbers in P */
      {  P[ rand()%500000 ] = 2*( 51*i + 237) + 1;
	 P[ rand()%500000 ] = 2*( 51*i + 237) + 1;
	 P[ rand()%500000 ] = 2*( 51*i + 237) + 1;
	 Q[ 2*i ] = 2*( 51*i + 237) + 1;
      }
    for(i=0; i< t2; i++) /* put some even numbers in Q */
      {  Q[ rand()%200000 ] = 2*( 53*i + 732);
	 Q[ rand()%200000 ] = 2*( 53*i + 732);
	 Q[ rand()%200000 ] = 2*( 53*i + 732);
	 P[ 5*i ] = 2*( 53*i + 732);
      }
    printf(" finished preparing two arrays. they have %d elements in common\n",
	   t1+t2);
    result = common( P, Q, 500000, 200000);
    printf(" found %d elements in common.\n", result);
    if( result == t1 + t2 )
      printf( " Passed test.\n");
    else
      printf( " Failed test.\n");

}

