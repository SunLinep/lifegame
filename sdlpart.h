#ifndef SHARE_SDLPART_H
#define SHARE_SDLPART_H

#include <SDL2/SDL.h>
#include <stdio.h>
//Mouse's x position
int mousex;
//Mouse's y position
int mousey;
//delaytime
int delay;
//range
int range;

int judgeinput(int opt, int num, int time);

//Draw border lines
void drawline(SDL_Window *window, SDL_Surface *screen, int x, int y);

//Draw a cell map
void drawrectangle(SDL_Window *window, SDL_Surface *screen, int x, int y, int num);
#endif //SHARE_SDLPART_H
