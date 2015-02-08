#include "sdlgraphs.h"
#include <iostream>

#define DEG_TO_RAD(deg) (M_PI / 180) * deg
#define RAD_TO_DEG(rad) (180/ M_PI) * rad

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return 1;

	SDL_Window *wnd = SDL_CreateWindow("Graph Test", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (wnd == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	Graph graph(-180.f, 180.f, 60.f, -1.f, 1.f, 0.2f, 640, 480);
	graph.setTargetWindow(wnd);

	graph.clear();

	graph.drawGrid(1, 1);

	graph.update();

	graph.setColor(0, 0xFF, 0);

	float x, y;
	for (int i = -180; i < 180; ++i)
    {
        x = i;
        y = sin(DEG_TO_RAD(x));

        graph.printPixel(x, y);
        graph.update();
    }

    
    bool quit = false;
    while (!quit)
    {
    	SDL_Event event;
	    while (SDL_PollEvent(&event))
	    {
	    	if (event.type == SDL_QUIT)
	    		quit = true;
	    }
	}

    SDL_DestroyWindow(wnd);
    SDL_Quit();

	return 0;
}
