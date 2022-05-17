#include <SDL2/SDL.h>
#include "sdlpart.h"

//opt: 0 delay 1s
//opt: 1 keystrokes
//Press the right mouse button: return 1
//Press keyboard: return 0
//Press esc: return -1
int judgeinput(int opt, int num, int time){
    if(opt == 0){
        SDL_Delay(time*1000);
    }else if(opt == 1){
        while(1){
            //KeyboardState
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            SDL_PumpEvents();
            //Handing keyboard events
            //DOWN;RIGHT: NEXT
            //ESC: esc
            if(num == 0){
                Uint32 buttons = SDL_GetMouseState(&mousex, &mousey);
                //buttons: MouseState
                if((buttons & SDL_BUTTON_LMASK) != 0){
                    //Press the right mouse button
                    //Example Delete the stacked event
                    while(1){
                        Uint32 button = SDL_GetMouseState(&mousex, &mousey);
                        SDL_PumpEvents();
                        if((button & SDL_BUTTON_LMASK) != 0) continue;
                        else break;
                    }
                    return 1;
                }
            }
            if(state[SDL_SCANCODE_DOWN]) {
                //Press the Down key on the keyboard
                //Example Delete the stacked event
                while(1){
                    const Uint8 *state2 = SDL_GetKeyboardState(NULL);
                    SDL_PumpEvents();
                    if(state2[SDL_SCANCODE_DOWN]) continue;
                    else break;
                }
                break;
            }else if(state[SDL_SCANCODE_RIGHT]){
                //Press the Right key on the keyboard
                //Example Delete the stacked event
                while(1){
                    const Uint8 *state2 = SDL_GetKeyboardState(NULL);
                    SDL_PumpEvents();
                    if(state2[SDL_SCANCODE_RIGHT]) continue;
                    else break;
                }
                break;
            }else if(state[SDL_SCANCODE_ESCAPE]){
                //Press the Esc key on the keyboard
                return -1;
            }
        }
    }
    return 0;
}

//Draw border lines
//x: the columns of cell map
//y: the rows of cell map
void drawline(SDL_Window *window, SDL_Surface *screen, int x, int y){
    int i;
    //Drew column
    for(i = 0; i <= x; i++){
        SDL_Rect line = {i*100,0,1,100*y};
        //Gray line
        SDL_FillRect(screen,&line, SDL_MapRGB(screen->format, 128, 128, 128));
        //update surface
        SDL_UpdateWindowSurface(window);
    }
    //Draw lines line
    for(i = 0; i <= y; i++){
        SDL_Rect line = {0,i*100,100*x,1};
        //Gray line
        SDL_FillRect(screen,&line, SDL_MapRGB(screen->format, 128, 128, 128));
        //update surface
        SDL_UpdateWindowSurface(window);
    }
}

//Draw a cell map
//num 1: living cell
//num 0: dead cell
void drawrectangle(SDL_Window *window, SDL_Surface *screen, int x, int y, int num){
    //rectangular
    SDL_Rect rect = {x,y,100,100};
    //black color
    if(num == 1) SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0));
    //white color
    if(num == 0) SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format,0xFF,0xFF,0xFF));
    //update surface
    SDL_UpdateWindowSurface(window);
}
