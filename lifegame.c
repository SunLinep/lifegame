#include<stdio.h>
#include <SDL2/SDL.h>
#include <string.h>

int nextchoice = 0;
int x;
int y;

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

//opt: 0 delay 1s
//opt: 1 keystrokes
int judgeinput(int opt, int num){
    int i = 100;
    if(opt == 0){
        SDL_Delay(1000);
    }else if(opt == 1){
        while(1){
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            SDL_PumpEvents();
            //Handing keyboard events
            //DOWN;RIGHT: NEXT
            //ESC: esc
            if(num == 0){
                Uint32 buttons = SDL_GetMouseState(&x, &y);
                if((buttons & SDL_BUTTON_LMASK) != 0){
                    printf("%d, %d\n",x,y);
                    nextchoice = 1;
                    while(1){
                        Uint32 button = SDL_GetMouseState(&x, &y);
	        	        SDL_PumpEvents();
	        	        if((button & SDL_BUTTON_LMASK) != 0) continue;
	        	        else break;
                    }
                    return 1;
                }
            }
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
        return 0;
    }
    
}

//Draw border lines
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

//Draw a cell map
void drawrectangle(SDL_Window *window, SDL_Surface *screen, int x, int y, int num){
    SDL_Rect rect = {x,y,100,100};
    if(num == 0) SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0));
    if(num == 1) SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format,0xFF,0xFF,0xFF));
    SDL_UpdateWindowSurface(window);
}

//Get cell map's row and column
//-2: no file
//0: initialization succeeded
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

//chose model
int opt(void){
    int i;
    char txt[10];
    printf("Which model do you want(A/M): ");
    while(1){
        fgets(txt, 5, stdin);
        for(i = strlen(txt)-1; txt[i]== '\n' || txt[i]== '\r' ; i--){
            txt[i] = '\0';
        }
        if(strcmp(txt,"A") == 0) return 0;
        else if(strcmp(txt,"M") == 0) return 1;
        else {
            while(fgets(txt, 8, stdin) != NULL) printf("1\n");
            
            printf("Invalid input, please re-enter(A/M): ");
        }
    }
}

//1: Perfect input
//0: Perfect wrong input
//2: wrong time
//3: wrong filename
void commandline(int ac, char *av[], int *step, char *filename){
    int i;
    int num;
    char temp[200];
    if(ac > 1){
        int len1 = strlen(av[1]); 
        if(len1 < 4||(av[1][len1-1] != 't' || av[1][len1-2] != 'x' || av[1][len1-3] != 't' || av[1][len1-4] != '.')){
            do{
                printf("Invalid file name!\nPlease re-enter: ");
                fgets(filename,250,stdin);
                for(i = strlen(filename); filename[i-1] == '\n' || filename[i-1] =='\r'; i--) filename[i-1] = '\0';
                while(fgets(temp,190,stdin));
            }while(filename[strlen(filename)-1] != 't' || filename[strlen(filename)-2] != 'x' || filename[strlen(filename)-3] != 't' || filename[strlen(filename)-4] != '.');
        }else{
            strcpy(filename, av[1]);
        }
        if(ac > 2){
            int len2 = strlen(av[2]);
            for(i = 0; i < len2; num++, i++){
                if(av[2][i] < '0' || av[2][i] > '9') break;
            }
            if(i == len2){
                *step = atoi(av[2]);
            }else{
                while(1){
                    printf("Invalid step!\nPlease re-enter: ");
                    fgets(temp,190,stdin);
                    for(i = strlen(temp); temp[i-1] == '\n' || temp[i-1] =='\r'; i--) temp[i-1] = '\0';
                    len2 = strlen(temp);
                    for(i = 0; i < len2; num++, i++){
                        if(temp[i] < '0' || temp[i] > '9') break;
                    }
                    if(i == len2){
                        *step = atoi(temp);
                        while(fgets(temp,190,stdin));
                        break;
                    }
                    while(fgets(temp,190,stdin));
                }
            }
        }else{
            printf("Invalid output has been ignored!\n");
        }
    }else{
        do{
            printf("Invalid file name!\nPlease re-enter: ");
            fgets(filename,250,stdin);
            for(i = strlen(filename); filename[i-1] == '\n' || filename[i-1] =='\r'; i--) filename[i-1] = '\0';
            while(fgets(temp,190,stdin));
        }while(filename[strlen(filename)-1] != 't' || filename[strlen(filename)-2] != 'x' || filename[strlen(filename)-3] != 't' || filename[strlen(filename)-4] != '.');
        while(1){
            printf("Invalid step!\nPlease re-enter: ");
            fgets(temp,190,stdin);
            for(i = strlen(temp); temp[i-1] == '\n' || temp[i-1] =='\r'; i--) temp[i-1] = '\0';
            int len2 = strlen(temp);
            for(i = 0; i < len2; num++, i++){
               if(temp[i] < '0' || temp[i] > '9') break;
            }
            if(i == len2){
                *step = atoi(temp);
                while(fgets(temp,190,stdin));
                break;
            }
            while(fgets(temp,190,stdin));
         }
    }
}

int main(int argc, char *argv[]){
    //step number
    int step = -100;
    char filename[300];
    commandline(argc, argv, &step, filename);
    //Automatic or manual selection
    int nextoption = opt();
    int i, j, sum;
    //file
    FILE *fp;
    fp = fopen(filename, "r");
    char a[300];
    SDL_Window *window = NULL;
    SDL_Surface *screen = NULL;
    //life rowsize
    int MAXrow;
    //life columnsize
    int MAXcolumn;
    init(&MAXrow, &MAXcolumn, filename);
    int **start = (int **)malloc(MAXrow* sizeof(int *));
    int **next = (int **)malloc(sizeof(int *) * MAXrow);
    int **temp = (int **)malloc(sizeof(int *) * MAXrow);
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n",SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow("LifeGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAXcolumn*100+1, MAXrow*100+1, SDL_WINDOW_SHOWN);
    if(!window){
        printf("Window could not initialize! SDL_Error: %s\n",SDL_GetError());
        return -1;
    }
    screen = SDL_GetWindowSurface(window);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0xFF,0xFF,0xFF));
    SDL_UpdateWindowSurface(window);
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
        if(start[y/100][x/100] == 0){
            drawrectangle(window, screen, x/100*100, y/100*100, 0);
            drawline(window, screen, MAXcolumn, MAXrow);
            start[y/100][x/100] = 1;
        }else if(start[y/100][x/100] == 1){
            drawrectangle(window, screen, x/100*100, y/100*100, 1);
            drawline(window, screen, MAXcolumn, MAXrow);
            start[y/100][x/100] = 0;
        }
    }
    for(i = 0; i < MAXrow; i++){
        next[i] = (int *)malloc(sizeof(int) * MAXcolumn);
        temp[i] = (int *)malloc(sizeof(int) * MAXcolumn);
        memset(next[i], 0, sizeof(next[i]));
        memset(temp[i], 0, sizeof(temp[i]));
    }
    while(1){
        if(step != -100 && step <= 0) break;
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
        if(sum == 0) break;
        for(i = 0, sum = 0; i < MAXrow; i++){
            for(j = 0; j < MAXcolumn; j++){
                if(temp[i][j] == start[i][j]) sum++;
            }
        }
        if(sum == MAXrow*MAXcolumn) break;
        if(step != -100){
            step--;
        }
    }
    free(start);
    free(next);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
