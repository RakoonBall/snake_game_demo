#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

#define N 20
#define M 40

int i, j, Field[N][M], x, y, Gy, Head, Tail, Frogs, Game, a, b, var, dir, score, highscore, Speed=99;

FILE *f;

void snakeInitialization(){
    f = fopen("highscore.txt", "r");
    fscanf(f, "%d", &highscore);
    fclose(f);
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
    printf("Current Score: %d   Highscore: %d", score, highscore);
    printf("\n");
    for(i=0;i<N;i++){
        printf("%c", 186);
        for(j=0;j<M;j++){
                if(Field[i][j]==0){
                    printf(" ");
                } 
                if(Field[i][j] > 0 && Field[i][j]!=Head){
                    printf("%c", 176);
                } 
                if(Field[i][j]==Head){
                    printf("%c", 178);
                } 
                if(Field[i][j]==-1){
                    printf("%c", 42);
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
//stops the game from reloading again and again
void ResetScreenPosition(){
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

//generating frog 
void Random (){
    srand(time(0));
    a =1 + rand()%18;
    b = 1 + rand()%38;
    if(Frogs == 0 && Field[a][b] ==0){
        Field[a][b] = -1;
        Frogs = 1;
        if(Speed > 10 && score!=0) Speed = Speed -5;
    }
}
int getch_noblock(){
    if(_kbhit())
        return _getch();
    else
        return -1;
}
void movement(){
    var = getch_noblock();
    var = tolower(var);
    if(((var == 'd' || var == 'a')|| (var == 'w' || var =='s')) && (abs(dir-var)> 5)){
        dir = var;
    }
    if(dir == 'd'){
        y++;
        if(Field[x][y] !=0 && Field[x][y] !=-1) GameOver();
            if(y==M-1) y=0;
            if(Field[x][y]== -1){
                Frogs =0;
                score +=5;
                Tail-=2;
            }
        
        if(y==M-1) y = 0;
        if(Field[x][y] == -1){
            Frogs = 0;
            score +=5;
            Tail-=2;
        }
        Head++;
        Field[x][y] = Head;
    }
    if(dir == 'a'){
        y--;
        if(Field[x][y] !=0 && Field[x][y] !=-1) GameOver();
        if(y==0) y = M-1;
        if(Field[x][y] == -1){
            Frogs = 0;
            score +=5;
            Tail-=2;
        }
        Head++;
        Field[x][y] = Head;
    }
    if(dir == 'w'){
        x--;
        if(Field[x][y] !=0 && Field[x][y] !=-1) GameOver();
        if(x==-1) x = N-1;
        if(Field[x][y] == -1){
            //setting the Frog flag to zero to create another frog
            Frogs = 0;
            score +=5;
            //increase the size of snake when it eats the  frog
            Tail-=2;
        }
        Head++;
        Field[x][y] = Head;
    }
    if(dir == 's'){
        x++;
        if(Field[x][y] !=0 && Field[x][y] !=-1) GameOver();
        if(x==N-1) x = 0;
        if(Field[x][y] == -1){
            Frogs = 0;
            Tail-=2;
        }
        Head++;
        Field[x][y] = Head;
    }
}
void TailRemove(){
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            if(Field[i][j] == Tail){
                Field[i][j] = 0;
            }
        }
    }
    Tail++;
}

void GameOver(){
    printf("\a");// for a beep sound
    Sleep(1500); //1,5 seconds so that the player can see 
    system("Cls");//clear screen
    if(score> highscore){
        printf("   New highscore %d!!!!!!!!\n\n", score);
        system("pause");//let the user see the highscore befor he hits any keys
        f = fopen("highscore.txt", "w");
        fprintf(f,"%d", score);
        fclose(f);
    }
    printf("\n\n           GAME OVER !!!!!!!");
    printf("\n\n           SCORE : %d \n\n !!!!!!!", score);
    printf("               Press enter to play again or ESC to exit ...\n");

    while(1){
        var  = getch_noblock();
        if(var == 13){
            score = 0;
            Game =0;
            snakeInitialization();
            break;
        }else if(var ==27){
            Game = 1;
            break;
        }
    }
    system("Cls");
}
int main(){
    snakeInitialization();
    while(Game == 0){
        draw();
        ResetScreenPosition();
        Random();
        movement();
        TailRemove();
        Sleep(Speed);
    }
    return 0;
}


//create the box 
//declaring game loop so the game runs
//create the snake
//create the  frog and make sure that it is generated randomly so we use srand(time(0)) to create random position for the frog
//then we fix movement of the snake
//we need to fix tail as well
//increase the size when it eats the frog and generate a new frog
//gameover
//save score
//show highscroe using file
//increase the speed of the  snake every time the snake eats a frog
//play again option for the user
