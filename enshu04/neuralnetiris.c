#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define NUMVEC 5
#define NUMCLA 3
#define NUMNOD 7

int main(int argc,char *argv[])
{
  FILE *fp;
  double unknown[NUMVEC];
  double w1[NUMVEC][NUMNOD];
  double w2[NUMNOD][NUMCLA];
  double h_hidden[NUMNOD];
  double h_out[NUMCLA];
  double g_hidden[NUMNOD];
  double g_out[NUMCLA];
  double x[NUMVEC];
  double y[NUMCLA];
  int i,j,k,l,m;
  int sampley,resulty,correctclass[NUMCLA],class[NUMCLA];
  double rho = 0.1;
  double e3[NUMCLA],e2[NUMNOD];
  double maxnum;
  unsigned ranseed = (unsigned)time(NULL);

  for(i=0;i<NUMVEC;i++){
    for(j=0;j<NUMNOD;j++){
      ranseed += 1;
      srand(ranseed);
      w1[i][j] = (double)(rand()%9 + 1) / 10.0;
      //printf("%f ",w1[i][j]);
    }
    //printf("\n");
  }

  for(i=0;i<NUMCLA;i++){
    correctclass[i] = 0;
    class[i] = 0;
  }

  for(i=0;i<NUMNOD;i++){
    for(j=0;j<NUMCLA;j++){
      ranseed += 1;
      srand(ranseed);
      w2[i][j] = (double)(rand()%9 + 1) / 10.0;
      //printf("%f ",w2[i][j]);
    }
    //printf("\n");
  }

  // printf("a\n");

  /* unknown[0] = 1.0; */

  /* for(i=1;i<NUMVEC;i++){ */
  /*   unknown[i] = strtod(argv[i+1],0); */
  /* } */





  for(i=0;i<1000;i++){
    //printf("a\n");
    fp = fopen(argv[1],"r");
    
    while(!feof(fp)){
      
      x[0] = 1.0;

      for(l=1;l<NUMVEC;l++){
	fscanf(fp,"%lf",&x[l]);
	//printf("%f ",x[l]);
      }
      //printf("\n");
      
      //	    printf("a\n");
      
      g_hidden[0] = 1.0;
      
      for(l=0;l<NUMNOD;l++){
	h_hidden[l] = 0.0;
      }
	
      for(l=1;l<NUMNOD;l++){
	for(m=0;m<NUMVEC;m++){
	  h_hidden[l] += x[m]*w1[m][l];
	}
	  
	g_hidden[l] = 1.0 / (1.0 + exp(-h_hidden[l]));
	//printf("%f ",g_hidden[l]);
      }
	
      //  printf("a\n");
	
      for(l=0;l<NUMCLA;l++){
	h_out[l] = 0.0;
      }
	
      for(l=0;l<NUMCLA;l++){
	for(m=0;m<NUMNOD;m++){
	  h_out[l] += g_hidden[m]*w2[m][l];
	}
	  
	g_out[l] = 1.0 / (1.0 + exp(-h_out[l]));
      }
	
      //  printf("a\n");
	
      fscanf(fp,"%d\n",&sampley);
	
      for(l=0;l<NUMCLA;l++){
	if(l==sampley) y[l] = 1.0;
	else y[l] = 0.0;
	//printf("%f %d\n",y[l],l);
      }

      //printf("\n");
      //printf("a\n");

      for(l=0;l<NUMCLA;l++){
	e3[l] = (g_out[l] - y[l]) * g_out[l] * (1.0 - g_out[l]);
	//printf("%f \n",g_out[l] - y[l]);
      }
      //  printf("a\n");

      for(l=0;l<NUMNOD;l++){
	e2[l] = 0.0;
      }
      //  printf("a\n");

      for(l=0;l<NUMNOD;l++){
	for(m=0;m<NUMCLA;m++){
	  e2[l] += e3[m] * w2[l][m] * g_hidden[l] * (1.0 - g_hidden[l]);
	}
      }

      //  printf("a\n");

      for(l=0;l<NUMVEC;l++){
	for(m=1;m<NUMNOD;m++){
	  w1[l][m] -= rho * e2[m] * x[l];
	}
      }

      for(l=0;l<NUMNOD;l++){
	for(m=0;m<NUMCLA;m++){
	  w2[l][m] -= rho * e3[m] * g_hidden[l];
	  //printf("%f \n",e3[m]*g_hidden[l]);
	}
      }

      //  printf("a\n");
    }

    fclose(fp);
  }

  /* for(i=0;i<NUMVEC;i++){ */
  /*   for(j=0;j<NUMNOD;j++){ */
  /*     printf("%f ",w1[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */

  /* for(i=0;i<NUMNOD;i++){ */
  /*   for(j=0;j<NUMCLA;j++){ */
  /*     printf("%f ",w2[i][j]); */
  /*   } */
  /*   printf("\n"); */
  /* } */
  fp = fopen(argv[2],"r");
  
  while(!feof(fp)){

    unknown[0] = 1.0;

    for(l=1;l<NUMVEC;l++){
      fscanf(fp,"%lf",&unknown[l]);
      //printf("%f ",x[l]);
    }
  
    g_hidden[0] = 1.0;

    for(l=0;l<NUMNOD;l++){
      h_hidden[l] = 0.0;
    }
  
    for(l=1;l<NUMNOD;l++){
      for(m=0;m<NUMVEC;m++){
	h_hidden[l] += unknown[m]*w1[m][l];
      }
    
      g_hidden[l] = 1.0 / (1.0 + exp(-h_hidden[l]));
    }

    for(l=0;l<NUMCLA;l++){
      h_out[l] = 0.0;
    }
  
    for(l=0;l<NUMCLA;l++){
      for(m=0;m<NUMNOD;m++){
	h_out[l] += g_hidden[m]*w2[m][l];
      }

      //printf("%f\n",h_out[l]);
    
      g_out[l] = 1.0 / (1.0 + exp(-h_out[l]));
    }

    maxnum = g_out[0];
    j=0;

    for(i=0;i<NUMCLA;i++){
      printf("%f ",g_out[i]);
    
      if(g_out[i] > maxnum){
	maxnum = g_out[i];
	j = i;
      }
    }
    printf("\n");

    fscanf(fp,"%d\n",&resulty);

    class[resulty]++;

    if(j==resulty) correctclass[j]++; 
  }

  for(i=0;i<NUMCLA;i++){
    printf("The accuracy of class %d is : %f\n",i,(float)correctclass[i] / (float)class[i]);
  }
  
  return 0;
}
