#include<stdio.h>
#include<stdlib.h> 
#include<time.h> 
#include<string.h>
#include<stdbool.h>

//Function for selection of random number n 
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

//Functions for union find algorithm - initialise, root, find and union
//Initialise with number n . Create set for each i in N. Set size as 1. Size is needed for merge(union) function to determine which root to attach the node.
void initialize(int set[],int size[],int N)
{
    for(int i = 0;i<N;i++)
    {
        set[i] = i ;
        size[i] = 1;
    }
}

//Get root of the vertex.
int root (int set[],int i)
{   
    while(set[i]!=i)
    {
        set[i]=set[set[i]]; 
        i=set[i]; 
    }
    return i;
}

//Find whether the given vertices are connected. Find3 function
bool find(int set[],int A,int B)
{
    if(root(set,A)==root(set,B))       //A and B are connected if they have the same root.
    { 
       return true;
    }
    else
    {
        return false;
    }
}

//Merge(Union)3 function. If the roots are different, merge them. Check size of the two nodes' roots. Change the root accordingly. 
void merge(int set[],int size[],int A,int B)
{
    int Aroot = root(set,A);
    int Broot = root(set,B);
    if(size[Aroot]<size[Broot])
    {
        set[Aroot]=set[Broot];
        size[Broot]+=size[Aroot];
    }
    else
    {
        set[Broot]=set[Aroot];
        size[Aroot]+=size[Broot];
    }
}

//Create a structure for Kruskals Algorithm since we need to check for cycles separately
struct edges{
int edge1;
int edge2;
int weight;

};

//Swap function for Quick Sort. Quicksort used so as to get (nlogn) complexity for sorting.
void swap(struct edges * a, struct edges* b) 
{ 
    struct edges t = *a; 
    *a = *b; 
    *b = t; 
}

//Partition function
int partition (struct edges edge[], int low, int high) 
{ 
    int pivot = edge[high].weight;  
    int i,j;     // pivot 
    i = (low-1);                   // Index of smaller element 
    for (j=low;j<=high-1;j++) 
    {                                    // If current element is smaller than the pivot 
        if (edge[j].weight < pivot) 
        { 
            i++;                         // increment index of smaller element 
            swap(&edge[i], &edge[j]);
        } 
    } 
    swap(&edge[i + 1], &edge[high]); 
    return (i + 1); 
} 
//QuickSort main function
void quickSort(struct edges edge[], int low, int high) 
{ 
    if (low < high) 
    {   
        // p_i = partitioning index
        int p_i = partition(edge, low, high); 
        //Sort elements before and after the partition
        quickSort(edge, low, p_i - 1); 
        quickSort(edge, p_i + 1, high); 
    } 
} 


int main()
{

printf("\nEnter your choice for Algorithm: \nType '1' for Prim's \nType '2' for Kruskal's\nChoice:");
int selection;
//Get algorithm selection choice 
scanf("%d",&selection);
if(!(selection==1 || selection==2)){
    printf("Please input either 1 or 2!.\nError!.\nReturning with return value -1!\n");
    return -1;
}
//Create n vertices
int n = selectn();

printf(" Randomly Selected n : %d \n",n);
time_t t;
//Create an nXn adjacency matrix
int matrix[n][n];
//Create a display matrix nXn
int display[n][n];
//Set all values to 0
memset(display,0,sizeof(display));


//Random assign a weight to each edge in matrix
int i,j;

for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        //Check condition if i==j. For diagonal elements, the value should be 0.
        if(i==j){
            matrix[i][j] =0;
          matrix[i][i]= 0;
        }
        // For all other elements
        else{
            //Using srand to randomize to seed pseudo random generator
            srand(i+j*2-32+i*j*time(0));
            //Since we want values to be between 1 and 10.Add 1 and randomise between 0 and 9
            int random = (rand()%(9))+1;
            //Assign values.
            matrix[i][j] = random;
            matrix[j][i] = random;
        }
    }
}

//Display matrix: Assigned values to the matrix.

printf("\n Random Matrix :  \n");
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        printf(" %d ",matrix[i][j]);
    }
    printf("\n");
}

//PRIMS ALGORITHM
if(selection==1){
    printf("\n Selected Choice : PRIMS ALGORITHM : \n");
//Initialise number of edge to 0
int edges=0;
//Initialise visited array all to false
int visited[n];
int x,y,min;
//Declare costs and prev
int cost[n];
int prev[n];
//Set values for costs and prev as follows
for(i=0;i<n;i++){
    cost[i] = 9999;
    prev[i] = 0;
    visited[i] = 0;
}
//To start with vertex 0.
visited[0] = 1;
int vertex;
cost[0] = 0;
min =0;
int mincost;
printf("\n Prim's MST :\n ");
//Apply Prims algorithm
while(edges<=n-2){ //the edges should be n-1 in MST
    //Get minimum
    vertex = min;  //Initialise first vertex to 0 // Then set vertex to minimum value
    mincost = 9999;                             //Set mincost to infinity for comparison
    for(j=0;j<n;j++){
                                                //Go through adjacent vertices
        if(!visited[j] && matrix[vertex][j])
        {                                       //Set values for cost/prev
            if(matrix[vertex][j] < cost[j]){
                cost[j] = matrix[vertex][j];
                prev[j] = vertex;
                                                //Used arrays as priority queue
            }                                   //Get minimum value from all costs//
            if(cost[j]<mincost){
                mincost = cost[j];
                min = j;
           }
        }
    }                                   
    visited[min]=1;                     //Set minimum node that we get as visited                    
    edges++;                            //Increment edge counter
    x= prev[min];                       //Set values for x and y for display matrix
    y = min;
    printf("\nV%d-V%d : %d",x+1,y+1,cost[y]);       //Print edges
    display[x][y] = cost[min]; 
    display[y][x] = cost[min];                    //Copy values for MST
}
}

if(selection==2){
printf("\n Selected Choice : KRUSKALS ALGORITHM : \n");
int count=0,sizen=(n*n)-n;
struct edges edge[sizen]; //Array of structure edges. Size will be n^2 - n because if (i==j) then the node is connected to itself.Hence, weight will be 0.
//Other weights as initialised from 1 to 10 randomly as asked in problem statement.

//Copy adjacent matrix values in structure for kruskals algorithm
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        if(matrix[i][j]!=0){
            edge[count].edge1 = i;
            edge[count].edge2 = j;
            edge[count].weight = matrix[i][j];
            count++;}

    }
    
}

//Sort the edges in non decreasing weight order
quickSort(edge, 0, sizen-1);
//Create a new T matrix to store the MST. Size will be n-1
struct edges T[n-1];
// Initialise edge count to 0
int tcount=0;
 
int set[sizen],size[sizen];
//Initialise sets and size arrays for disjoint sets purpose.
//For each vertex create a set.
initialize(set,size,sizen);
//Apply the kruskals algorithm.
for(i=0;i<sizen;i++){
    if(tcount<n){  // Run until number(vertices) = n-1 or no more vertices/
    if(!find(set,edge[i].edge1,edge[i].edge2)){  //find whether vertices/edges have same roots( check for cycle)
        merge(set,size,edge[i].edge1,edge[i].edge2); // if not merge them . 
        T[tcount] = edge[i]; //                     //Add the edge to MST
        tcount++;                                   //increase the tcount/edge count
    }
    }
    else{
        break; //Once we get all the edges for MST, break the loop
    }
}

printf("\n Kruskal's MST : \n");
for (int i=0; i<tcount; i++)                            
{      
        display[T[i].edge1][T[i].edge2] = T[i].weight;         // COPY values from MST to display matrix for displaying
        display[T[i].edge2][T[i].edge1] = T[i].weight;
        printf("\n V%d - V%d : %d",T[i].edge1+1,T[i].edge2+1,T[i].weight); //print the kruskals MST
} 
}

printf("\n\n Display Matrix for selected algorithm : \n");
for(i=0;i<n;i++){               
    for(j=0;j<n;j++){
        printf(" %d ",display[i][j]);                          //Print the display MATRIX

    }
    printf("\n");
}

}