#include<stdio.h>
#include <stdlib.h> 
#include <time.h> 
int selectn(){
//Use current time as seed for random generator
int i;
srand(time(0)); 
i= rand() % 10;
if(i<5){
    return (i+5);
}
return i;
}




int main()
{
//Create n vertices
int n = selectn();
printf("Randomly Selected n : %d \n",n);
time_t t;
//Create an nXn adjacency matrix and path matrix
int matrix[n][n];
int p[n][n];
//Random assign a weight to each edge and initialize p to 0
int i,j;
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        //Check condition if i==j. For diagonal elements, the value should be 0.
        if(i==j){
            matrix[i][j] =0;
          matrix[i][i]= 0;
          p[i][j]=0;
        }
        // For all other elements
        else{
            //Using srand to randomize to seed pseudo random generator
            srand(i+j*2);
            //Since we want values to be between 1 and 10.Add 1 and randomise between 0 and 9
            int random = (rand()%(9))+1;
            //Assign values.
            matrix[i][j] = random;
            matrix[j][i] = random;
            p[i][j]=0;


        }
    }
}

//Display matrix: Assigned values to the matrix.

printf("Assigned values to the matrix are: \n");
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        printf(" %d ",matrix[i][j]);
    }
    printf("\n");
}


//Apply floyd's agorithm:
int k;
for(k=0;k<n;k++){
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(matrix[i][j]> ((matrix[i][k])+matrix[k][j])){
                matrix[i][j] = matrix[i][k]+matrix[k][j];
                matrix[j][i] = matrix[i][k]+matrix[k][j];
                p[i][j] = k+1;
                p[j][i] = k+1;
            }
           
        }
    }
}
//Print D matrix
printf("\n");
printf("A matrix :\n");

for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        {
        printf(" %d ",matrix[i][j]);
        }
        
    }
    printf("\n");
}
printf("\n");

//Print P matrix:
printf("P matrix :\n");
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        {
        printf(" %d ",p[i][j]);
        }
    }
    printf("\n");
}

//Print Shortest Path and Lengths:
printf("\n");
printf("Shortest Paths and Lengths: ");
for(i=0;i<n;i++){
    printf("\nShortest Paths and lengths: V%d - Vj",i+1);
    for(j=0;j<n;j++){
        //CHeck whether p is 0
        if(p[i][j]!=0){
        printf("\nV%d-V%d-V%d : %d",i+1,p[i][j],j+1,matrix[i][j]);    
        }
        else{
            printf("\nV%d-V%d : %d",i+1,j+1,matrix[i][j]);
        }
    }
    printf("\n");
}
printf("\n");
}
