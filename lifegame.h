#ifndef SHARE_LIFEGAME_H
#define SHARE_LIFEGAME_H

#include <stdio.h>

int delaytime;

//Determine if the cells are alive
int cell(int celllife, int neighbour);

//Get cell map's row, column and delay time
int init(int* row, int *column, char* filename);

//chose model: Automatic or manual
int opt(void);

void commandline(int ac, char *av[], int *step, char *filename);
#endif //SHARE_LIFEGAME_H
