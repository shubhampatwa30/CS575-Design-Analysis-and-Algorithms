#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
//Declare variables from weight capacity and number of items globally
int wcapacity;
int n;
int count=0;
int num;
int maxprofit=0;
double bound=0.0;
int bestset[600];
int include[600];
int seq=1;

//Declare structure for list of all items
struct list_of_items {
    char name[100];
    int profit_pi;
    int weight_wi;
    double piwi;
};
//For sorting the items in nonincreasing order
void Sort(struct list_of_items items[]) 
{ struct list_of_items temp;
    for (int i = n-1; i >=0; i--)  
        for (int j = n-1; j >= n - i; j--)  
            if (items[j].piwi > items[j - 1].piwi)  
            {    temp = items[j];
                items[j] = items[j-1];
                items[j-1] = temp;
                
            }
} 
//Algorithm for calculating the bound as given in slides
double KWF2(int i, int weight, int profit,struct list_of_items items[])
{
    bound = profit;
    double x[n+1];
    for (int j = i; j <= n; j++)
    {
        x[j] = 0.0;
    }
    while (weight < wcapacity && i <= n)
    {
        if ((weight + items[i].weight_wi) <= wcapacity)
        {
            x[i] = 1.0;
            weight = weight + items[i].weight_wi;
            bound = bound + (double)items[i].profit_pi;
        }
        else
        {
            x[i] = (double)(wcapacity - weight) / (double)items[i].weight_wi;
            weight = wcapacity;
            bound = bound + items[i].profit_pi * x[i];
        }
        i = i+1;
    }
    return bound;
}
//Promising Node function as given in slides
int promising(int i, int weight, int profit,struct list_of_items items[])
{
    if (weight >= wcapacity)
    {
    return 0;
    }
    bound = KWF2(i+1, weight, profit,items);
    //To write into entries3.txt file for output
    char * filename = "entries3.txt";
    FILE* file = fopen(filename, "a+");
    fprintf(file,"\n%d\t%d\t%d\t%.2f",seq,profit, weight, bound);
    fclose(file);
    seq++;
    return (bound > maxprofit);
}
//Knapsack function
void knapsack(int i, int profit, int weight,struct list_of_items items[])
{
    if (weight <= wcapacity && profit > maxprofit)
    {
        maxprofit = profit;
        num = i;
        for (int i = 1; i <= n; i++)
            bestset[i] = include[i];
    }
    if (promising(i, weight, profit,items))
    {
        include[i+1] = 1;
        knapsack(i+1, profit + items[i+1].profit_pi, weight + items[i+1].weight_wi,items);
        include[i+1] = 0;
        knapsack(i+1,profit, weight,items);
    }
}

int main(int argc, char *argv[])
{   //Get number of arguments for argument check. If not 3, return error
    if(argc!=3){
          printf("Invalid Arguments: Syntax is './dynpro -k knapsack01.txt' \n");
          return -1;
      }
     //Second argument will be the name of txt file to be read from
   // char * filename = "knapsack01.txt";
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
    struct list_of_items knapuse[n+1];//To store items from 1st index
    while(fgets(line, sizeof(line), file)) {  //fetch all items from text file
    char* token = strtok(line, " "); 
    strcpy(items[i].name, token);
    token = strtok(NULL, " "); 
    items[i].profit_pi = atoi(token);
    token = strtok(NULL, " "); 
    items[i].weight_wi = atoi(token);
    items[i].piwi = (double)items[i].profit_pi / items[i].weight_wi;
    i++;
    }
    fclose(file); //close
    strcpy(knapuse[0].name," "); //Nullify 0th index
    knapuse[0].profit_pi = 0;
    knapuse[0].weight_wi = 0;
    knapuse[0].piwi = 0.0;
    Sort(items);             //Sort the items in nonincreasing order
    for(i=0;i<n;i++){       //Copy all other items
        strcpy(knapuse[i+1].name,items[i].name);
        knapuse[i+1].profit_pi = items[i].profit_pi;
        knapuse[i+1].weight_wi = items[i].weight_wi;
        knapuse[i+1].piwi = items[i].piwi;
     }
   //Run knapsack backtracking algorithm
    knapsack(0, 0, 0,knapuse);
    int total_weight=0, q=0;                     // Get the total weight and number of items.
    for(int j = 1; j <=num; j++)                // Show an optimal set of items.
     { if(bestset[j])
     {
       total_weight += items[j-1].weight_wi;
       q +=1;
     }
     }
    //For output3.txt file
    filename = "output3.txt";               //Items, profits and weights to be written into
    file = fopen(filename, "w");
    fprintf(file,"%d %d %d\n",q,maxprofit,total_weight);
    for(int j=1;j<=num;j++){
        if(bestset[j]){
        fprintf(file,"%s %d %d\n",items[j-1].name,items[j-1].profit_pi,items[j-1].weight_wi);}
    }
    fclose(file);

}
