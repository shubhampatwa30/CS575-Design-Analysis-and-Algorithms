#include<stdio.h>
#include<stdlib.h>
int iter=0;
int **array;
void tromino( int x_board,int y_board,int x_missing,int y_missing,int board_size)
{

if(board_size==2){
    if(x_missing%2==0){
        if(y_missing%2==0 ){
           array[x_board][y_board] = 0;
            array[x_board+1][y_board+1] = 2;
            array[x_board+1][y_board] = 2;
            array[x_board][y_board+1] = 2;

        }
        else if(y_missing%2==1){
            array[x_board][y_board] = 4;
            array[x_board+1][y_board+1] = 4;
            array[x_board+1][y_board] = 4;
            array[x_board][y_board+1] = 0;
        }
        else{
            printf("\nWrong input in 1\n");
            printf("\n%d %d\n",x_missing,y_missing);
            printf("\n%d %d\n",x_board,y_board);
        }
    }
    else{
        if(y_missing%2==0){
            array[x_board][y_board] = 1;
            array[x_board+1][y_board+1] = 1;
            array[x_board+1][y_board] = 0;
            array[x_board][y_board+1] = 1;
        }
        else if(y_missing%2==1){
           array[x_board][y_board] = 3;
            array[x_board+1][y_board+1] = 0;
            array[x_board+1][y_board] = 3;
            array[x_board][y_board+1] = 3;
        }
        else{
            printf("\nWrong input in 2\n");
            printf("\n%d %d\n",x_missing,y_missing);
            printf("\n%d %d\n",x_board,y_board);
            
        }

    }
}
else{
    if(x_missing>=(x_board+board_size/2)){
        if(y_missing>=(y_board+board_size/2)){
            tromino( x_board + board_size/2, y_board + board_size/2, x_missing,y_missing, board_size/2);
           tromino( x_board , y_board + board_size/2, (x_board +board_size/2)-1, (y_board+board_size/2),board_size/2);
            tromino( x_board, y_board,(board_size/2)-1 ,(board_size/2)-1, board_size/2);
            tromino( x_board + board_size/2, y_board,(board_size/2) , (board_size/2)-1, board_size/2);
        }  
        else{
            tromino( x_board + board_size/2, y_board,x_missing ,y_missing, board_size/2);
            tromino( x_board, y_board + board_size/2, (x_board +board_size/2)-1, (y_board+board_size/2),board_size/2 );
            tromino( x_board + board_size/2, y_board + board_size/2,x_board+board_size/2, y_board+board_size/2, board_size/2 );
            tromino( x_board, y_board,(board_size/2)-1 ,(board_size/2)-1, board_size/2 );    
        }
    }
    else{
        if(y_missing>=(y_board+board_size/2)){
            tromino( x_board, y_board + board_size/2, x_missing,y_missing,board_size/2);
            tromino( x_board + board_size/2, y_board + board_size/2,x_board+board_size/2, y_board+board_size/2, board_size/2);
            tromino( x_board, y_board,(board_size/2) - 1 ,(board_size/2) - 1, board_size/2 );
            tromino( x_board + board_size/2, y_board,(board_size/2) , (board_size/2)-1, board_size/2);
        }
        else{
            tromino( x_board, y_board,x_missing ,y_missing, board_size/2);
            tromino( x_board, y_board + board_size/2, board_size/2-1, board_size/2,board_size/2);
            tromino( x_board + board_size/2, y_board + board_size/2,board_size/2, board_size/2, board_size/2);
            tromino( x_board + board_size/2, y_board,board_size/2 , (board_size/2)-1, board_size/2 );
        }   
    }
}
}

int main(){
    printf("Please input the board size (need to be 2^n):");
    int size,x_missing,y_missing;
    scanf("%d",&size);
    array = malloc(sizeof(int) * size+1);
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            array[i]=malloc(100);
        }
    }
    printf("Please enter coordinates of missing square (separate by a space):");
    scanf("%d %d",&x_missing,&y_missing);
    tromino(0,0,x_missing,y_missing,size);
    array[x_missing][y_missing] = 5;
    for(int i=size-1;i>=0;i--){
        for(int j=0;j<size;j++){
            if(array[j][i]==5){
                printf("MS  ");
            }
           else if((array[j][i])==0){
                if(j>0){
                    if(array[j-1][i-1]==0){
                        array[j][i]=4;
                        array[j-1][i-1]=4;
                        array[j][i-1]=4;
                        printf("LR  ");
                        continue;
                    }
                }
                if(j<size-1){
                    if(array[j][i-1]==0){
                        if(array[j+1][i]==0){
                            array[j][i]=1;
                            array[j][i-1]=1;
                            array[j+1][i]=1;
                            printf("UL  ");
                            continue;
                        }}
                        if(array[j+1][i-1]==0){
                           if(array[j][i-1]==0){
                               array[j][i]=3;
                               array[j+1][i-1]=3;
                               array[j][i-1] = 3;
                               printf("LL  ");
                               continue;
                           }
                            if(array[j+1][i]==0){
                               array[j][i]=2;
                               array[j+1][i-1]=2;
                               array[j+1][i]=2;
                               printf("UR  ");
                               continue;
                           }
                        }           
                }
            }
          else if(array[j][i]==1){
                printf("UL  ");
            }
           else  if(array[j][i]==2){
                printf("UR  ");

            }
           else  if(array[j][i]==3){
                printf("LL  ");
            }
            else{
                printf("LR  ");
            }
            
        }
        printf("\n");
    }
    return 0;
}