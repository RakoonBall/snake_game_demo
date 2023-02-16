#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

#define N 20
#define M 40

int i,j, Field[N][M],x,y,Gy, Head, Tail, Frogs,Game, a,b,var,dir;

void snakeInitialization(){
   for(i=0;i<N;i++){
    for(j=0;j<M;j++){
        Field[i][j] = 0;
    }
   }

   x = N/2; y = M/2; Gy = y; Head = 5; Tail = 1, Game=0, Frogs =0; dir='d';
    for(i=0;i<Head; i++){
        Gy++;
        Field[x][Gy-Head] = i+1;
    }
}
void draw(){
        for(i=0;i<=M+1;i++){
            if(i==0){
                printf("%c", 201);
            }else if(i==M+1){
                printf("%c", 187);
            }else{
                printf("%c",205);
            }
    }
    printf("\n");

    for(i=0;i<N;i++){
        printf("%c", 186);
        for(j=0;j<M;j++){
                if(Field[i][j]==0){
                    printf(" ");
                } 
                if(j==M-1) printf("%c\n", 186); 
        }

    }
    for(i=0;i<=M+1;i++){
            if(i==0){
                printf("%c", 200);
            }else if(i==M+1){
                printf("%c", 188);
            }else{
                printf("%c",205);
            }
    }
}

void movement(){
    var = getch_noblock();
    var = tolower(var);
    if(((var == 'd' || var == 'a')|| (var == 'w' || var =='s')) && (abs(dir-var)> 5)){
        dir = var;
    }
    if(dir == 'd'){
        y++;
        Head++;
        Field[x][y] = Head;
    }
    if(dir == 'a'){
        y--;
        Head++;
        Field[x][y] = Head;
    }
    if(dir == 'w'){
        x--;
        Head++;
        Field[x][y] = Head;
    }
    if(dir == 's'){
        x++;
        Head++;
        Field[x][y] = Head;
    }
}
int main(){
    snakeInitialization();
    draw();
    return 0;
}
