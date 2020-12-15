#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Declare variables from weight capacity and number of items globally
int wcapacity;
int n;
//Declare structure for list of all items
struct list_of_items {
    char name[100];
    int profit_pi;
    int weight_wi;
};

int selection[500][500]; //For entries2.txt
//Algorithm for knapsack problem funciton ( recursive )
int calcmatrix(int matrix[n+1][wcapacity+1],int i,int j,struct list_of_items items[]){
    
    if(i>0 && j>=0){
        //Get the weight for the current item
        int j_weight = items[i-1].weight_wi;
        //Claculate the diff in column and current items weight
        int calweight = j-j_weight;
        //Get the upper value 
        int cal2 = (calcmatrix(matrix,i-1,j,items));
        int cal1;
            //Check whether the calculated weight is > 0. If not , it will give seg fault. Hence, check before hand.
        if(calweight<=0){
            cal1 = 0;
        }
        else{
            //Get the other value for comparison as shown. 
            cal1 = (calcmatrix(matrix,i-1,calweight,items));
            }
            //Compare and get the max value between the two.
        if((calweight>=0) &&  ((cal1 + items[i-1].profit_pi) > cal2))
        {   //return the value for recursion
            matrix[i][j] = cal1 + items[i-1].profit_pi;
            selection[i][j] = 1;
            return matrix[i][j];
        }
        else{
            // if the previous condition does not set// return the value for recursion
            matrix[i][j] = cal2;
            selection[i][j] = 1;
            return matrix[i][j];
            }

   }
   //if i||j is going < 0 , return 0 // out of bounds for matrix
   else {
       
       return 0;
   }

}

int main(int argc, char *argv[])
{   //Get number of arguments for argument check. If not 3, return error
     if(argc!=3){
         printf("Invalid Arguments: Syntax is './dynpro -k knapsack01.txt' \n");
         return -1;
     }
    //Second argument will be the name of txt file to be read from
    char * filename = argv[2];
    FILE* file = fopen(filename, "r");//open in read mode
    char line[256];  //buffer
    fgets(line,sizeof(line),file); //read 1st line
    char* token = strtok(line, " ");
    n = atoi(line); //get the number of items
    token = strtok(NULL, " ");
    wcapacity = atoi(token); // get the weight capacity
    int i=0;
    struct list_of_items items[n]; // declare structure for items
    while(fgets(line, sizeof(line), file)) {  //fetch all items from text file
    char* token = strtok(line, " "); 
    strcpy(items[i].name, token);
    token = strtok(NULL, " "); 
    items[i].profit_pi = atoi(token);
    token = strtok(NULL, " "); 
    items[i].weight_wi = atoi(token);
    i++;
    }
    fclose(file); //close
    
    int matrix[n+1][wcapacity+1];       //Declare matrix
    memset(matrix,0,sizeof(matrix));    //initialise to 0
    memset(selection,0,sizeof(selection));
    calcmatrix(matrix,n,wcapacity,items);  //Run knapsack dynamic programming refinement algorithm
    filename = "entries2.txt";          //Matrix to be written in this file
    file = fopen(filename, "w"); 
    
    for(i=1;i<=n;i++){
        fprintf(file,"\nrow%d",i);
        for(int j=0;j<=wcapacity;j++){
            //if(matrix[i][j]!=0){
              if(selection[i][j]==1){  
                fprintf(file,"\t%d",matrix[i][j]);       //write to txt file
            }
        }
        //fprintf(file,"\n");
    }
     fclose(file);

//Get the number of items, items, total profits, weights, etc eligible for acceptance
int x = matrix[n][wcapacity];        //Initialise to last element
i= n;
int p = wcapacity;                  // For changing j
int q =0;                           // For storing final matrix using q
int final[n];
int total_weight=0; 
int total_profit = 0;
memset(final,0,sizeof(final));      // Initialise final to 0
    for(i=n;i>=0;i--){
        for(int j=p;j>=0;j--){
             if(x == matrix[i][j]){         //If the element is same as the upper element, no change, element not taken
                break;
            }
            else                            //Else store the element no. in final matrix, add weights and profits for totalling
            {   
                p=j - items[i].weight_wi;
                x = matrix[i][p];
                total_profit += items[i].profit_pi;
                total_weight += items[i].weight_wi;
                final[q] = i;
                q++;
                break;
                
            }
        }
        }

    filename = "output2.txt";               //Items, profits and weights to be written into
    file = fopen(filename, "w");
    fprintf(file,"%d %d %d\n",q,total_profit,total_weight);
    for(i=q-1;i>=0;i--){
        fprintf(file,"%s %d %d\n",items[final[i]].name,items[final[i]].profit_pi,items[final[i]].weight_wi);
    }
    fclose(file);




}
