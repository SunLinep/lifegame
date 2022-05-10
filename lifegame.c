#include<stdio.h>
#include <SDL2/SDL.h>
#include <string.h>

int nextchoice = 0;

//Determine if the cell is alive or dead
//1:alive
//0:dead
int cell(int celllife, int neighbour){
    if(celllife == 0 && neighbour == 3) return 1;
    if(celllife == 1){
        if(neighbour <= 1 || neighbour > 3) return 0;
        else return 1;
    }
}

void judgeinput(int opt){
    int i = 100;
    if(opt == 0){
        SDL_Delay(1000);
    }else if(opt == 1){
        while(1){
		    const Uint8 *state = SDL_GetKeyboardState(NULL);
	    	SDL_PumpEvents();
            if(state[SDL_SCANCODE_DOWN]) {
                nextchoice = 1;
                while(1){
                    const Uint8 *state2 = SDL_GetKeyboardState(NULL);
	    	        SDL_PumpEvents();
	    	        if(state2[SDL_SCANCODE_DOWN]) continue;
	    	        else break;
                }
                break;
            }else if(state[SDL_SCANCODE_RIGHT]){
            	nextchoice = 1;
            	while(1){
                    const Uint8 *state2 = SDL_GetKeyboardState(NULL);
	    	        SDL_PumpEvents();
	    	        if(state2[SDL_SCANCODE_RIGHT]) continue;
	    	        else break;
                }
                break;
            }else if(state[SDL_SCANCODE_ESCAPE]){
                exit(0);
            }
            
        }
        nextchoice = 0;
    }
    
}

void drawline(SDL_Window *window, SDL_Surface *screen, int x, int y){
    int i;
    for(i = 0; i <= x; i++){
        SDL_Rect line = {i*100,0,1,100*y};
        SDL_FillRect(screen,&line, SDL_MapRGB(screen->format, 128, 128, 128));
        SDL_UpdateWindowSurface(window);
    }
    for(i = 0; i <= y; i++){
        SDL_Rect line = {0,i*100,100*x,1};
        SDL_FillRect(screen,&line, SDL_MapRGB(screen->format, 128, 128, 128));
        SDL_UpdateWindowSurface(window);
    }
}

void drawrectangle(SDL_Window *window, SDL_Surface *screen, int x, int y){
    SDL_Rect rect = {x,y,100,100};
    SDL_FillRect(screen,&rect, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_UpdateWindowSurface(window);
}

int init(int* row, int *column, char* filename){
    FILE *fp;
    char a[300];
    char temp;
    int i, j;
    fp = fopen(filename, "r");
    if(fp == NULL) return -1;
    if(fgets(a, 250, fp) == NULL) return -2;
    for(i = 0, j = 0; i < strlen(a) && a[i] != '\r' && a[i] != '\n'; i++){
        if(a[i] == '0' || a[i] == '1') j++;
    }
    *column = j;
    for(j = 1; fgets(a, 250, fp) != NULL; j++);
    *row = j;
    return 0;
    fclose(fp);
}

int main(void){
    int nextoption = 1;
    FILE *fp;
    char filename[300] = "life.txt";
    fp = fopen(filename, "r");
    char a[300];
    SDL_Window *window = NULL;
    SDL_Surface *screen = NULL;
    int i, j, sum;
    int step = -100;//step number
    int MAXrow;//life rowsize
    int MAXcolumn;//life columnsize
    init(&MAXrow, &MAXcolumn, filename);
    int **start = (int **)malloc(MAXrow* sizeof(int *));
    int **next = (int **)malloc(sizeof(int *) * MAXrow);
    int **temp = (int **)malloc(sizeof(int *) * MAXrow);
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n",SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow("LifeGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAXcolumn*100, MAXrow*100, SDL_WINDOW_SHOWN);
    if(!window){
        printf("Window could not initialize! SDL_Error: %s\n",SDL_GetError());
        return -1;
    }
    screen = SDL_GetWindowSurface(window);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0xFF,0xFF,0xFF));
    SDL_UpdateWindowSurface(window);
    for(j = 0; fgets(a, 250, fp) != NULL; j++){
        start[j] = (int *)malloc(sizeof(int) * MAXcolumn);
        for(i = 0; i < strlen(a) && a[i] != '\r' && a[i] != '\n'; i++){
            if(a[i] != '1' && a[i] != '0') return -3;
            start[j][i] = a[i] - '0';
            if(start[j][i]==1)drawrectangle(window, screen, 100 * i, j * 100);
        }
    }
    drawline(window, screen, MAXcolumn, MAXrow);
    judgeinput(nextoption);
    for(i = 0; i < MAXrow; i++){
        next[i] = (int *)malloc(sizeof(int) * MAXcolumn);
        temp[i] = (int *)malloc(sizeof(int) * MAXcolumn);
        memset(next[i], 0, sizeof(next[i]));
        memset(temp[i], 0, sizeof(temp[i]));
    }
    while(1){
        if(step != -100 && step < 0) break;
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0xFF,0xFF,0xFF));
        SDL_UpdateWindowSurface(window);
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
        fp = fopen("copy.txt", "w");
        for(i = 0, sum = 0; i < MAXrow; i++){
            for(j = 0; j < MAXcolumn; j++){
                temp[i][j] = start[i][j];
                if((start[i][j] = next[i][j])==1){
                    drawrectangle(window, screen, 100 * j, i * 100);
                    sum++;
                }
                fprintf(fp,"%d",start[i][j]);
            }
            fprintf(fp,"\n");
            memset(next[i], 0, sizeof(next[i]));
        }
        fclose(fp);
        drawline(window, screen, MAXcolumn, MAXrow);
        judgeinput(nextoption);
        if(sum == 0) break;
        for(i = 0, sum = 0; i < MAXrow; i++){
            for(j = 0; j < MAXcolumn; j++){
                if(temp[i][j] == start[i][j]) sum++;
            }
        }
        if(sum == MAXrow*MAXcolumn) break;
        if(step != -100)step--;
    }
    free(start);
    free(next);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
