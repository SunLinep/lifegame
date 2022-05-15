#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

//Get cell map's row and column
//-2: no file
//0: initialization succeeded
int init(int* row, int *column, char* filename){
    FILE *fp;
    char a[300];
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
    fclose(fp);
    return 0;
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


