#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include "color.h"
#include "display.h"

#define TARGET_FRAME_RATE 60
#define MS_PER_FRAME (1000 / TARGET_FRAME_RATE)

long long int hits = 0;

bool isNumber(const char *string, size_t stringlen){

    uchar character;
    for(size_t k = 0; k < stringlen; k++){

        character = string[k];
        if(character < 48 || character > 57) return false;

    }

    return true;
}


void usage(const char *pg_name){

    printf("Usage: %s [number-of-squares] < 1000\n", pg_name);

    
}

int main(int argc, char **argv){

    if(argc < 2 || !isNumber(argv[1], strlen(argv[1]))){

        usage(argv[0]);
        return -1;
    }

    uint number_of_squares = atoi(argv[1]);

    if(number_of_squares > 1000){

        usage(argv[0]);
        return -1;

    }


    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        stdErrorInfo("SDL");
        return 1;
    }

    Window my_win;
    Color *squares_color = malloc(sizeof(Color) * number_of_squares);
    uint *x_axis_speed = malloc(sizeof(uint) * number_of_squares);
    uint *y_axis_speed = malloc(sizeof(uint) * number_of_squares);

    setWindowSize(&my_win, 640, 480);
    setRGBColor(&my_win.background_color, 255, 255, 255, 0);

    my_win.display = SDL_CreateWindow("My Rectagnles",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     my_win.width,
                                     my_win.height,
                                     SDL_WINDOW_SHOWN);
    if(!my_win.display){
        stdErrorInfo("Window");
        return 1;
    }
    else{

        my_win.initialized = true;
        my_win.renderer = SDL_CreateRenderer(my_win.display, -1, SDL_RENDERER_ACCELERATED);

        if(!my_win.renderer){
            stdErrorInfo("Renderer");
            return 1;
        }
        else{

            my_win.rect = malloc(sizeof(SDL_Rect) * number_of_squares);
            for(size_t k = 0; k < number_of_squares; k++){


                randomColor(&squares_color[k]);

                x_axis_speed[k] = 2; //bottom speed
                y_axis_speed[k] = 2; //bottom speed

                x_axis_speed[k] += rand() % 15;
                y_axis_speed[k] += rand() % 15;

                my_win.rect[k].x = rand() % my_win.width - 25;
                my_win.rect[k].y = rand() % my_win.height - 25;
                my_win.rect[k].w = 50;
                my_win.rect[k].h = 50;
                   
            }
        
            my_win.quit = false;
        
            while(!my_win.quit){


                my_win.frame_tick = SDL_GetTicks();


                if(SDL_PollEvent(&my_win.ev)){
                    if(my_win.ev.type == SDL_QUIT){
                        my_win.quit = true;

                    }

                    if(my_win.ev.type == SDL_MOUSEBUTTONDOWN){
                        printf("Number of hits: %lld\n", hits);
                    }
                }

                setBackgroundColor(my_win, my_win.background_color);


                for(size_t k = 0; k < number_of_squares; k++){
                    

                    my_win.rect[k].x += x_axis_speed[k]; //moves the rectangles left
                    my_win.rect[k].y += y_axis_speed[k];

                    if(my_win.rect[k].x >= my_win.width || my_win.rect[k].x <= 0){

                        randomColor(&squares_color[k]);
                        x_axis_speed[k] *= -1;
                        hits++;
                    }

                    if(my_win.rect[k].y >= my_win.height || my_win.rect[k].y <= 0){

                        randomColor(&squares_color[k]); 
                        y_axis_speed[k] *= -1;
                        hits++;
                    }

                    SDL_SetRenderDrawColor(my_win.renderer, squares_color[k].R, squares_color[k].G, squares_color[k].B, squares_color[k].A); //random color i guarantee
                    SDL_RenderFillRect(my_win.renderer, &my_win.rect[k]);


                }





                SDL_RenderPresent(my_win.renderer);
                

                my_win.frame_time = SDL_GetTicks() - my_win.frame_tick;
                
                if(my_win.frame_time < MS_PER_FRAME){
                    SDL_Delay(MS_PER_FRAME - my_win.frame_time);
                } //Set fps to 60

            }

            SDL_DestroyRenderer(my_win.renderer);

        }

        SDL_DestroyWindow(my_win.display);

    }

    free(my_win.rect);
    free(squares_color);
    free(y_axis_speed);
    free(x_axis_speed);

    SDL_Quit();



}
