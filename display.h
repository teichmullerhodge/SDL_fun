typedef struct {

    SDL_Window *display;
    SDL_Renderer *renderer;
    SDL_Rect *rect;
    SDL_Event ev;

    Color background_color;

    uint width;
    uint height;
    
    uint frame_tick;
    uint frame_time;

    bool initialized;
    bool quit;

} Window;



void stdErrorInfo(const char *SDL_ENTITY){

    printf("%s could not be created!\n", SDL_ENTITY);
    printf("SDL_Error: %s\n", SDL_GetError());

}


void setRenderColor(Window win, Color RGB){

        SDL_SetRenderDrawColor(win.renderer, RGB.R, RGB.G, RGB.B, RGB.A);

}

void setBackgroundColor(Window win, Color RGB){

    SDL_SetRenderDrawColor(win.renderer, RGB.R, RGB.G, RGB.B, RGB.A);
    SDL_RenderClear(win.renderer);

}


void setWindowSize(Window *win, uint width, uint height){

    win->width  =  width;
    win->height = height;

}