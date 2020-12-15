#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Declare structure for list of all items
struct list_of_items {
    char name[100];
    int profit_pi;
    int weight_wi;
};

int main(int argc, char *argv[])
{   //Get number of arguments for argument check. If not 3, return error
    if(argc!=3){
        printf("Invalid Arguments: Syntax is './bruteforce -k knapsack01.txt' \n");
        return -1;
    }
    //Second argument will be the name of txt file to be read from
    char * filename = argv[2];
    FILE* file = fopen(filename, "r");//open in read mode
    char line[256];  
    fgets(line,sizeof(line),file);//read 1st line
    char* token = strtok(line, " ");
    int n = atoi(line);//get the number of items
    token = strtok(NULL, " ");
    int wcapacity = atoi(token); // get the weight capacity
    int i=0;
    struct list_of_items items[n];// declare structure for items
    while(fgets(line, sizeof(line), file)) {  //fetch all items from text file
        
    char* token = strtok(line, " "); 
    strcpy(items[i].name, token);
    token = strtok(NULL, " "); 
    items[i].profit_pi = atoi(token);
    token = strtok(NULL, " "); 
    items[i].weight_wi = atoi(token);
    i++;
    }
    fclose(file);//close
    

   //Initialise all variables to zero
    int mark=0;
    int sum_of_weight=0;
    int weight_total =0;
    int totalprofit = 0;
    long int u = 1<<n; //Calculate 2^n subsets
    int maxprofit = 0;
    int itemmax = 0;
//Run bruteforce algorithm
for(i=1;i<u;i++){
    int x=0;
    int subsets[u];
    int sub = i;
    int count=0;
    int itemcount = 0;
    while (sub > 0) { 
        subsets[x] = sub % 2; 
        if(subsets[x]==1){      //If binary of the number has the digit "1"
            sum_of_weight  +=items[x].weight_wi;
            totalprofit += items[x].profit_pi;
            itemcount += 1;
            } 
        sub = sub / 2; 
        x++; 
    } 
    if(sum_of_weight<=wcapacity)
    {   
        if(totalprofit > maxprofit ){
            maxprofit = totalprofit;
            totalprofit =0;
            itemmax = itemcount;
            mark=i;
            weight_total = sum_of_weight;
        }
    }
    sum_of_weight=0;
    totalprofit =0 ;
    itemcount=0;
}

char * fileName = "output1.txt"; //Output to be displayed in this file
file = fopen(fileName, "w"); 
fprintf(file,"%d %d %d\n",itemmax,maxprofit,weight_total); //First print this on the first line
int q=0;
while (mark > 0) {  
    if(mark%2==1){  //Check the binary number of the final subset we got for digit containing "1"
        fprintf(file,"%s %d %d\n",items[q].name,items[q].profit_pi,items[q].weight_wi);
    } 
    mark = mark / 2; 
    q++; 
    } 
fclose(file);
return 0;
}



