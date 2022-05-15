#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdlib.h>
#include "sdlpart.h"
#include "lifegame.h"

int main(int argc, char *argv[]){
    //step number
    int step = -100;
    //filename
    char filename[300];
    //Process command line arguments
    commandline(argc, argv, &step, filename);
    //Automatic or manual selection
    int nextoption = opt();
    //Act as an intermediate variable
    int i, j;
    //The number of cells used to judge
    int sum;
    //File type pointer
    FILE *fp;
    //Open the file in read-only mode
    fp = fopen(filename, "r");
    char a[300];
    //UI window
    SDL_Window *window = NULL;
    //UI
    SDL_Surface *screen = NULL;
    //life rowsize
    int MAXrow;
    //life columnsize
    int MAXcolumn;
    //get cell map's row, column and delay time
    init(&MAXrow, &MAXcolumn, filename);
    //The initial state
    int **start = (int **)malloc(MAXrow* sizeof(int *));
    //Next state
    int **next = (int **)malloc(sizeof(int *) * MAXrow);
    //Temp state
    int **temp = (int **)malloc(sizeof(int *) * MAXrow);
    //Check whether the SDL is successfully initialized
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n",SDL_GetError());
        return -1;
    }
    //Initialize window
    window = SDL_CreateWindow("LifeGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAXcolumn*100+1, MAXrow*100+1, SDL_WINDOW_SHOWN);
    //Check whether the window is successfully initialized
    if(!window){
        printf("Window could not initialize! SDL_Error: %s\n",SDL_GetError());
        return -1;
    }
    //Initialize white interface
    screen = SDL_GetWindowSurface(window);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0xFF,0xFF,0xFF));
    SDL_UpdateWindowSurface(window);
    //Initializing an array and UI
    for(j = 0; fgets(a, 250, fp) != NULL; j++){
        start[j] = (int *)malloc(sizeof(int) * MAXcolumn);
        memset(start[j], 0, sizeof(start[j]));
        for(i = 0; i < strlen(a) && a[i] != '\r' && a[i] != '\n'; i++){
            if(a[i] != '1' && a[i] != '0') return -3;
            start[j][i] = a[i] - '0';
            if(start[j][i]==1) drawrectangle(window, screen, 100 * i, j * 100, 0);
        }
    }
    drawline(window, screen, MAXcolumn, MAXrow);
    while(judgeinput(1, 0)){
        if(mousex%100 == 0 || mousey%100 == 0) continue;
        if(start[mousey/100][mousex/100] == 0){
            drawrectangle(window, screen, mousex/100*100, mousey/100*100, 0);
            drawline(window, screen, MAXcolumn, MAXrow);
            start[mousey/100][mousex/100] = 1;
        }else if(start[mousey/100][mousex/100] == 1){
            drawrectangle(window, screen, mousex/100*100, mousey/100*100, 1);
            drawline(window, screen, MAXcolumn, MAXrow);
            start[mousey/100][mousex/100] = 0;
        }
    }
    //Initialize Next and Temp state
    for(i = 0; i < MAXrow; i++){
        next[i] = (int *)malloc(sizeof(int) * MAXcolumn);
        temp[i] = (int *)malloc(sizeof(int) * MAXcolumn);
        memset(next[i], 0, sizeof(next[i]));
        memset(temp[i], 0, sizeof(temp[i]));
    }
    while(1){
        if(step != -100 && step <= 0) break;
        //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0xFF,0xFF,0xFF));
        //SDL_UpdateWindowSurface(window);
        //Deal with the four corners
        next[0][0] = cell(start[0][0], start[0][1]+start[1][0]+start[1][1]);
        next[MAXrow-1][0] = cell(start[MAXrow-1][0], start[MAXrow-1][1]+start[MAXrow-2][0]+start[MAXrow-2][1]);
        next[0][MAXcolumn-1] = cell(start[0][MAXcolumn-1], start[0][MAXcolumn-2]+start[1][MAXcolumn-1]+start[1][MAXcolumn-2]);
        next[MAXrow-1][MAXcolumn-1] = cell(start[MAXrow-1][MAXcolumn-1], start[MAXrow-1][MAXcolumn-2]+start[MAXrow-2][MAXcolumn-1]+start[MAXrow-2][MAXcolumn-2]);
        //Deal with four edges
        for(i = 1; i < MAXrow-1;i++){
            next[i][0] = cell(start[i][0], start[i-1][0]+start[i+1][0]+start[i][1]+start[i-1][1]+start[i+1][1]);
            next[i][MAXcolumn-1] = cell(start[i][MAXcolumn-1], start[i-1][MAXcolumn-1]+start[i+1][MAXcolumn-1]+start[i][MAXcolumn-2]+start[i-1][MAXcolumn-2]+start[i+1][MAXcolumn-2]);
        }
        for(i = 1; i < MAXcolumn-1; i++){
            next[MAXrow-1][i] = cell(start[MAXrow-1][i], start[MAXrow-1][i-1]+start[MAXrow-1][i+1]+start[MAXrow-2][i]+start[MAXrow-2][i+1]+start[MAXrow-2][i-1]);
            next[0][i] = cell(start[0][i], start[0][i-1]+start[0][i+1]+start[1][i]+start[1][i+1]+start[1][i-1]);
        }
        //Deal with the middle part
        for(i = 1; i < MAXrow-1; i++){
            for(j = 1, sum = 0; j < MAXcolumn-1; j++){
                next[i][j] = cell(start[i][j],start[i-1][j]+start[i+1][j]+start[i][j-1]+start[i][j+1]+start[i-1][j-1]+start[i+1][j-1]+start[i+1][j+1]+start[i-1][j+1]);
            }
        }
        //Write the result to a file
        fp = fopen("copy.txt", "w");
        for(i = 0, sum = 0; i < MAXrow; i++){
            for(j = 0; j < MAXcolumn; j++){
                temp[i][j] = start[i][j];
                if((start[i][j] = next[i][j])==1){
                    drawrectangle(window, screen, 100 * j, i * 100, 0);
                    sum++;
                }
                fprintf(fp,"%d",start[i][j]);
            }
            fprintf(fp,"\n");
            memset(next[i], 0, sizeof(next[i]));
        }
        fclose(fp);
        drawline(window, screen, MAXcolumn, MAXrow);
        judgeinput(nextoption, 1);
        //If all cells die, exit
        if(sum == 0) break;
        //If cell balance is not iterated, exit
        for(i = 0, sum = 0; i < MAXrow; i++){
            for(j = 0; j < MAXcolumn; j++){
                if(temp[i][j] == start[i][j]) sum++;
            }
        }
        if(sum == MAXrow*MAXcolumn) break;
        if(step != -100){
            //In each iteration, step - 1
            step--;
        }
    }
    //free malloc
    free(start);
    free(next);
    free(temp)
    //destroy window
    SDL_DestroyWindow(window);
    //quit sdl
    SDL_Quit();
    return 0;
}
