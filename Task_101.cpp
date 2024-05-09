#include <SDL2/SDL.h>

#include <stdio.h>

#include <math.h>

#define SCREEN_WIDTH 800

#define SCREEN_HEIGHT 800

int cen_x = SCREEN_WIDTH / 2;

int cen_y = SCREEN_WIDTH / 2;

int rad = 100;

bool init_SDL(SDL_Window** window, SDL_Renderer** renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Can not initialize SDL: %s\n", SDL_GetError());

        return false;
    }

    *window = SDL_CreateWindow("Circle Made by ASHRAFUL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (*window == NULL)
    {
        printf("Can not create window: %s\n", SDL_GetError());

        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (*renderer == NULL)
    {
        printf("Can not create renderer %s\n", SDL_GetError());

        return false;
    }

    return true;
}

void Circle(SDL_Renderer* renderer)
{
    for (int x = -rad; x <= rad; x++)
    {
        for (int y = -rad; y <= rad; y++)
        {
            if (x * x +  y * y <= rad * rad)
            {
                SDL_RenderDrawPoint(renderer, cen_x + x, cen_y + y);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!init_SDL(&window, &renderer)) {
        return 1;
    }

    SDL_Event event;
    bool running = true;

    
    while (running) 
    {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

            
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        Circle(renderer);

        SDL_RenderPresent(renderer);
    }
   
    return 0;
}