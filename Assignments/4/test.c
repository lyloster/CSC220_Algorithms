#include <stdio.h>
#include <stdlib.h>

#define k 10
int maxflow(int n, int *cap, int *flow, int *residual);

main()
{    int capacities[4*k+2][4*k+2];
     int flow[4*k+2][4*k+2];
     int residual[4*k+2][4*k+2];
     int i,j, improvement, stepcount, totalflow;
     int inflow, outflow;
     for(i=0; i<4*k+2; i++)
       for(j=0; j<4*k+2; j++)
	 {  capacities[i][j]=0; flow[i][j]=0; residual[i][j]=0;
	 }
     /* initialize capacities */
     for(i=1; i< k+1; i++)
       { capacities[0][i] = 20;
	 capacities[i][k+i] = 4;
	 capacities[i][k+(i%k)+1] = 4;
	 capacities[i][2*k+i] = 5;
	 capacities[k+i][3*k+i] = 5;
	 capacities[2*k+i][3*k+i] = 3;
	 capacities[2*k+i][3*k+(i%k)+1] = 3;
	 capacities[2*k+i][3*k+((i+1)%k)+1] = 3;
	 capacities[3*k+i][4*k+1] = 12;
       }
     printf("created capacity matrix. %d vertices, expected maximum flow %d.\n",
	    4*k+2, 10*k );
     improvement=1; stepcount = 0;
     while( improvement > 0)
     { improvement=maxflow( 4*k+2, &(capacities[0][0]), &(flow[0][0]),
				   &(residual[0][0]) );
       stepcount ++;
       /* check flow matrix: capacity constraint and nonnegativity */
       for(i=0; i<4*k+2; i++)
          for(j=0; j<4*k+2; j++)
	  {  if( flow[i][j] < 0 )
	     {	printf("step %d: negative flow value %d on edge %d -> %d\n",
		       stepcount, flow[i][j], i, j); fflush(stdout); exit(0);
	     }
	     if( flow[i][j] > capacities[i][j] )
	     {	printf("step %d: flow %d > capacity %d on edge %d -> %d\n",
		       stepcount, flow[i][j], capacities[i][j], i, j);
	               fflush(stdout); exit(0);
	     }
	  }
       /* check flow matrix: inflow = outflow */
       for( i=1; i< 4*k+1; i++ )
       {  inflow = 0; outflow = 0;
	  for( j=0; j<4*k+2; j++ )
	  {  inflow += flow[j][i];
	    outflow += flow[i][j];
	  }
	  if( inflow != outflow )
	    {  printf("step %d: flow conservation violated in vertex %d\n",
		      stepcount, i); fflush(stdout); exit(0);
	    }
       }
       printf("step %d completed; improvement %d\n", stepcount, improvement );
     }
     totalflow =0;
     for( i=1; i<k+1; i++)
        totalflow += flow[0][i];
     printf("finished after %d steps; total flow %d\n", stepcount, totalflow);
}
