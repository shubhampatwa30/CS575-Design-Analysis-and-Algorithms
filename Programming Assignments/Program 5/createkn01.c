#include<stdio.h>
#include<stdlib.h> 
#include<time.h> 
#include<string.h>
#include<math.h>

//Function for selection of random number n 
int selectn(){
int i; 
i= rand() % 9;
if(i<4){
    return (i+4);
}
return i;
}

int randomprofit(){ //Function to create randomised profits between 10-30
//Use current time as seed for random generator
int i;
//srand(56); 
i= rand() % 31;
if(i<10){
    return (i+11);
}
return i;
}

int randomweight(){//Function to create randomised weights between 5-20
//Use current time as seed for random generator
int i;
//srand(32); 
i= rand() % 21;
if(i<5){
    return (i+7);
}
return i;
}

//Create structure for list of items
struct list_of_items {
    char name[7];
    int profit_pi;
    int weight_wi;
};

int main(int argc, char *argv[]){
    if(argc!=3){
        printf("Invalid Arguments: Syntax is './createkn01 -k knapsack01.txt' \n");
        return -1;
    }
    //Set seed for random number generator
    srand(time(0)); 
    //Get randomised n
    int n= selectn();
    struct list_of_items items[n];
    int i=0;
    int wcapacity = 0;
    for(i=0;i<n;i++){
        char buf[7];
        //Give names to each element we create item0, item1, etc
        snprintf(buf, 7, "item%d", i);
        strcpy(items[i].name,buf);
        items[i].profit_pi = randomprofit();
        items[i].weight_wi = randomweight();
        wcapacity += items[i].weight_wi;
    }
    //Calculate capacity of the weight
    wcapacity = 0.6 * wcapacity;
    wcapacity = floor(wcapacity);
    char * filename = argv[2];
    FILE* file = fopen(filename, "w");
    //Write the data to file
    fprintf(file,"%d %d\n",n,wcapacity);
    for(i=0;i<n;i++){
        fprintf(file,"%s %d %d\n",items[i].name,items[i].profit_pi,items[i].weight_wi);
    }
    fclose(file);
    return 0;
}
