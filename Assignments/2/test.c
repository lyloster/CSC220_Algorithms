#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort( int *A, int n);

main()
{  int i, offset, j;
   int B[10000000];
   time_t t;
   srand( (unsigned) time( &t ));
   offset = rand()%10000000;
   for( i = 0; i< 10000000; i++ )
   {  B[i] = ((91*i)%10000000) + offset;
   }
   printf("Prepared array of 10 million integers; calling sort\n");
   sort( B, 10000000 );
   printf("finished sort, now check result\n");
   for( i=0, j=0; i < 10000000; i++ )
     if( B[i] != i+ offset ) j++;
   if( j == 0 )
     printf("Passed Test\n");
   else
     printf("Failed Test. %d numbers wrong.\n", j );
}
