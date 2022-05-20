#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sdlpart.h"
#include "lifegame.h"

//Determine if the cell is alive or dead
//1:alive
//0:dead
int cell(int celllife, int neighbour){
    //Cell survival condition
    if(celllife == 0 && neighbour == 3) return 1;
    if(celllife == 1) if(neighbour == 2 || neighbour == 3) return 1;
    return 0;
}

//Get cell map's row and column
//-2: file is wrong
//-1: file is null
//0: no file
//1: initialization succeeded
int init(int* row, int *column, char* filename){
    //The file pointer
    FILE *fp;
    char a[300];
    //i: row
    //j: column
    //k: temp
    int i, j, k;
    fp = fopen(filename, "r");
	//No such file
    if(fp == NULL) return 0;
	//File is null
    if(fgets(a, 250, fp) == NULL) return -1;
	//Wrong file
    for(i = 0; i < strlen(a) ; i++){
    	if(a[i] == '\r' || a[i] == '\n') {
            a[i] = '\0';
            break;
    	}
        if(a[i] < '0' || a[i] > '9') return -2;
    }
	//Save time
    delay = atoi(a);
	//The delay threshold is 100
    if(delay > 100) rewind(fp);
	//Count the number of rows and columns
    for(i = 0; fgets(a, 250, fp) != NULL; i++){
        j = 0;
        while(j < strlen(a) && a[j] != '\r' && a[j] != '\n'){
			//Wrong file
            if(a[j] != '0' && a[j] != '1') return -2;
            j++;
        }
		//Wrong file
        if(i > 1 && j != k) return -2;
        k = j;
    }
    *column = j;
    *row = i;
	//Free
    fclose(fp);
    return 1;
}

//chose model
int opt(void){
    int i;
    char txt[10];
    printf("Which model do you want(A/M): ");
    while(1){
		//Read input
        fgets(txt, 4, stdin);
		//Deal with stdin
        if(txt[strlen(txt)-1] != '\r' && txt[strlen(txt)-1] != '\n')  while(getchar()!='\n');
		//Dispose of excess
        for(i = strlen(txt)-1; txt[i]== '\n' || txt[i]== '\r' ; i--){
            txt[i] = '\0';
        }
		//Automatic
        if(strcmp(txt,"A") == 0) return 0;
		//Manual
        else if(strcmp(txt,"M") == 0) return 1;
		//Wrong
        else printf("Invalid input, please re-enter(A/M): ");
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
	//At least one command line argument(First: filename)
    if(ac > 1){
		//The length of filename
        int len1 = strlen(av[1]);
		//Judge whether it is valid
		//Invalid
        if(len1 < 4||(av[1][len1-1] != 't' || av[1][len1-2] != 'x' || av[1][len1-3] != 't' || av[1][len1-4] != '.')){
            do{
				//Enter again
                printf("Invalid file name!\nPlease re-enter: ");
                fgets(filename,250,stdin);
				//Deal with stdin
                if(filename[strlen(filename)-1] != '\r' && filename[strlen(filename)-1] != '\n')  while(getchar()!='\n');
				//Dispose of excess
                for(i = strlen(filename); filename[i-1] == '\n' || filename[i-1] =='\r'; i--) filename[i-1] = '\0';
            }while(filename[strlen(filename)-1] != 't' || filename[strlen(filename)-2] != 'x' || filename[strlen(filename)-3] != 't' || filename[strlen(filename)-4] != '.');
        }else{
			//Valid
            strcpy(filename, av[1]);
        }
		//At least one command line argument(Second: step)
        if(ac > 2){
			//Dispose of excess
            if(ac > 3){
                printf("Invalid output has been ignored!\n");
            }
			//The length of step
            int len2 = strlen(av[2]);
			//The length of the valid input
            for(i = 0; i < len2; num++, i++){
                if(av[2][i] < '0' || av[2][i] > '9') break;
            }
			//Valid
            if(i == len2){
                *step = atoi(av[2]);
            }else{
				//Invalid
                while(1){
					//Enter again
                    printf("Invalid step!\nPlease re-enter: ");
                    fgets(temp,190,stdin);
					//Deal with stdin
                    if(temp[strlen(temp)-1] != '\r' && temp[strlen(temp)-1] != '\n')  while(getchar()!='\n');
                    //Dispose of excess
					for(i = strlen(temp); temp[i-1] == '\n' || temp[i-1] =='\r'; i--) temp[i-1] = '\0';
                    //The length of temp
					len2 = strlen(temp);
					//The length of the valid input
                    for(i = 0; i < len2; num++, i++){
                        if(temp[i] < '0' || temp[i] > '9') break;
                    }
					//Valid
                    if(i == len2){
                        *step = atoi(temp);
                        break;
                    }
                }
            }
        }else{
            char a[5];
            while(1){
                printf("Do you want to set the number of iterations?(Y/N) :");
                fgets(a, 4, stdin);
				//Deal with stdin
                if(a[strlen(a)-1] != '\r' && a[strlen(a)-1] != '\n')  while(getchar()!='\n');
                //Dispose of excess
				for(i = strlen(a); a[i-1] == '\n' || a[i-1] =='\r'; i--) a[i-1] = '\0';
                //No
				if(strcmp(a,"N") == 0) break;
				//Yes
                else if(strcmp(a,"Y") == 0){
                    while(1){
						//Enter step
                        printf("Invalid step!\nPlease re-enter: ");
                        fgets(temp,190,stdin);
						//Deal with stdin
                        if(temp[strlen(temp)-1] != '\r' && temp[strlen(temp)-1] != '\n')  while(getchar()!='\n');
                        //Dispose of excess
						for(i = strlen(temp); temp[i-1] == '\n' || temp[i-1] =='\r'; i--) temp[i-1] = '\0';
                        //The length of temp
						int len2 = strlen(temp);
						//The length of the valid input
                        for(i = 0; i < len2; num++, i++){
                            if(temp[i] < '0' || temp[i] > '9')  break;
                        }
						//Valid
                        if(i == len2){
                            *step = atoi(temp);
                            break;
                        }
                    }
                    break;
                }else{
                    printf("Wrong input! Please re-enter!\n");
                }
            }    
        }
    }else{
        do{
            printf("Invalid file name!\nPlease re-enter: ");
            fgets(filename,250,stdin);
			//Deal with stdin
            if(temp[strlen(temp)-1] != '\r' && temp[strlen(temp)-1] != '\n')  while(getchar()!='\n');
            //Dispose of excess
			for(i = strlen(filename); filename[i-1] == '\n' || filename[i-1] =='\r'; i--) filename[i-1] = '\0';
        }while(filename[strlen(filename)-1] != 't' || filename[strlen(filename)-2] != 'x' || filename[strlen(filename)-3] != 't' || filename[strlen(filename)-4] != '.');
        char a[5];
        while(1){
            printf("Do you want to set the number of iterations?(Y/N) :");
            fgets(a, 4, stdin);
            //Deal with stdin
			if(a[strlen(a)-1] != '\r' && a[strlen(a)-1] != '\n')  while(getchar()!='\n');
            //Dispose of excess
			for(i = strlen(a); a[i-1] == '\n' || a[i-1] =='\r'; i--) a[i-1] = '\0';
            //No
			if(strcmp(a,"N") == 0) break;
			//Yes
            else if(strcmp(a,"Y") == 0){
                while(1){
                    printf("Invalid step!\nPlease re-enter: ");
                    fgets(temp,190,stdin);
                    //Deal with stdin
					if(temp[strlen(temp)-1] != '\r' && temp[strlen(temp)-1] != '\n')  while(getchar()!='\n');
                    //Dispose of excess
					for(i = strlen(temp); temp[i-1] == '\n' || temp[i-1] =='\r'; i--) temp[i-1] = '\0';
                    //The length of temp
					int len2 = strlen(temp);
					//The length of the valid input
                    for(i = 0; i < len2; num++, i++){
                        if(temp[i] < '0' || temp[i] > '9')  break;
                    }
					//Valid
                    if(i == len2){
                        *step = atoi(temp);
                        break;
                    }
                }
                break;
            }else{
                printf("Wrong input! Please re-enter!\n");
            }
        }
    }
}

//Write the result to a file
void writefile(char* filename, int row, int column,  int* start[]){
    int i, j;
    //Write files
    FILE* fp = fopen(filename, "w");
    fprintf(fp,"%d\n",delay);
    for(i = 0; i < row; i++){
        for(j = 0; j < column; j++){
            fprintf(fp,"%d",start[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}
