#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{   if(argc!=3){
    printf("\nerror\n");
    return -1;
}
    int lena = strlen(argv[1]);
    int lenb = strlen(argv[2]);
    //Check whether the length of strings is greater than 100
    if(lena > 100 || lenb > 100){
        printf("\nThe string length is too long.\n");
        return -2;
    }
    char a[100],b[100];
//Get the two strings as input
    strcpy(a,argv[1]);
    strcpy(b,argv[2]);
// Initialise matrices of the lengths as the lengths as the strings
    int matrix[lena+1][lenb+1];
    char store[lena+1][lenb+1];
    printf("\n");
    int i,j;
// Initialise the first row and first column to be zero
    for(i=0;i<(lena+1);i++){
        matrix[i][0] = 0;
    }
    for(j=0;j<(lenb+1);j++){
        matrix[0][j] =0 ;

    }
//Apply LCS for dynamic programming    
    for(i=1;i<(lena+1);i++){
        for(j=1;j<(lenb+1);j++){
            if(a[i-1]== b[j-1]){
                matrix[i][j] = (matrix[i-1][j-1]) + 1; 
                store[i][j] = 'D';
            }
            else{
                if(matrix[i-1][j] >= matrix[i][j-1]){
                matrix[i][j] = matrix[i-1][j];
                 store[i][j] = 'U';
                }
                else{
                    matrix[i][j] = matrix[i][j-1];
                     store[i][j] = 'L';
                }
            }
        }
    }
//Print LCS
    i = lena;
    j = lenb;
//Get the length of LCS    
    int count = matrix[i][j];
    printf("Length of LCS : %d",count);
// Create a array to store to LCS    
    char c[count];
//Print the LCS
    while(i>0 && j>0){
        if(store[i][j]== 'D'){
            c[count-1] = a[i-1];
            count--;
            i--;
            j--;
        }
        else if(store[i][j] == 'U'){
            i--;
        }
        else{
            j--;
        }
    }
printf("\nLCS : %s",c);

printf("\n");
    

//Print the adjacency matrix    
printf("Adjacency Matrix :\n");
  for(i=0;i<(lena+1);i++) {
        for(j=0;j<(lenb+1);j++){
         printf(" %d ",matrix[i][j]);   
        }
        printf("\n");
    }


}





