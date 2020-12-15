#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct marketprice{
	char *name; 
	int price;	
}marketprice;

typedef struct grandmaprice{
	char *name;
	int price;
    int profit;
}grandmaprice;

typedef struct outputnames{
    char *name;

}outputnames;

int msize;
 marketprice *marketpricefile(char *argv){
 char * fileName = argv; 
    FILE* file = fopen(fileName, "r"); 
    char line[256];  
   int count=0;
   fgets(line,sizeof(line),file);
   msize = atoi(line);
   marketprice *listofmcards = malloc(sizeof(marketprice)*msize);
   int i;
   i=0;
   while(fgets(line, sizeof(line), file)) {  
    listofmcards[i].name = malloc(250);
    char* token = strtok(line, " "); 
    strcpy(listofmcards[i].name, token);
    token = strtok(NULL, " "); 
    listofmcards[i].price = atoi(token);
    i++;
    }
   fclose(file);
   return listofmcards; 
}


int powersets(grandmaprice * pricelist, int psize, int W,clock_t t){
int i;
int sum=0;
int j;
int q=0;
int mark=0;
int maxprofit = 0;
int totalprofit=0;
int maxnumofcards = 0;
int maxcards=0;
for(i=0;i<psize;i++){
sum  = sum + pricelist[i].price;
}
if(sum<=W){
for(i=0;i<psize;i++){
    totalprofit = totalprofit + pricelist[i].profit;
}
sum=0;
maxprofit = totalprofit;
totalprofit= 0;
maxcards = psize;
t = clock() - t; 
double time_taken = ((double)t)/CLOCKS_PER_SEC; 
char * fileName = "output.txt"; 
    FILE* file = fopen(fileName, "a+"); 
    char line[256]; 
    fprintf(file,"%d %d %d %f\n",psize,maxprofit,maxcards,time_taken);
    for(i=0;i<psize;i++){
        fprintf(file,"%s\n",pricelist[i]);
    }
    fclose(file);
return 0;
}
else{
    outputnames *namesofcards = malloc(sizeof(outputnames)*psize);
    outputnames *finalnames = malloc(sizeof(outputnames)*psize);
    sum=0;
    totalprofit = 0;
    long int u = 1<<psize;
for(i=1;i<u;i++){
    
    int x=0;
    int subsets[u];
    int n = i;
    int count=0;
     maxnumofcards = 0;
    while (n > 0) { 
                subsets[x] = n % 2; 
        if(subsets[x]==1){
            sum  = sum + pricelist[x].price;
            totalprofit = totalprofit + pricelist[x].profit;
            maxnumofcards = maxnumofcards+1;
          
            
            } 
        n = n / 2; 
        x++; 
    } 
   
    if(sum<=W)
    {
if(totalprofit > maxprofit ){
    maxprofit = totalprofit;
    totalprofit =0;
    maxcards = maxnumofcards;
   mark=i;

}

}
sum=0;
totalprofit =0 ;
maxnumofcards=0;
}
t = clock() - t; 
double time_taken = ((double)t)/CLOCKS_PER_SEC;
char * fileName = "output.txt"; 
    FILE* file = fopen(fileName, "a+"); 
    char line[256]; 
    fprintf(file,"%d %d %d %f\n",psize,maxprofit,maxcards,time_taken);
    q=0;
    while (mark > 0) { 
        if(mark%2==1){
           fprintf(file,"%s\n",pricelist[q]);
            
            } 
        mark = mark / 2; 
        q++; 
    } 
    fclose(file);
return 0;
}

}

grandmaprice *  pricelistfile(char *argv,marketprice * node){
    char * fileName = argv; 
    FILE* file = fopen(fileName, "r");
    char line[256];  

   int count=0;
   int cost;
   int pricelistsize;
   while(fgets(line,sizeof(line),file)){
   clock_t t; 
    t = clock();
   char* token = strtok(line, " "); 
   pricelistsize = atoi(token);
   token = strtok(NULL, " "); 
   cost = atoi(token);
   grandmaprice *pricelist = malloc(sizeof(grandmaprice)*pricelistsize);
    int i=0;
    while(i<pricelistsize)
    {
     fgets(line,sizeof(line),file);
    pricelist[i].name = malloc(2500);
    char* token = strtok(line, " "); 
    strcpy(pricelist[i].name, token);
    token = strtok(NULL, " "); 
    pricelist[i].price = atoi(token);    
    i++;
    } 
    for(i=0;i<pricelistsize;i++){
        for(int j=0;j<msize;j++){
            if(strcmp(pricelist[i].name,node[j].name)==0)
            {   pricelist[i].profit = node[j].price - pricelist[i].price;
            break;
            }
            else{
                pricelist[i].profit = '\0';
            }    
     }
    }
    powersets(pricelist,pricelistsize,cost,t);
    }
fclose(file);
}



int main(int argc, char *argv[])
{   
marketprice *node = marketpricefile(argv[2]);
grandmaprice * pricelist= pricelistfile(argv[4],node);
return 0;
}