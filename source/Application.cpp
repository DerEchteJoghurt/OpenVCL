#include "OpenVCL/OpenVCL.h"

void Application::Initialize() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	TTF_Init();
}

void Application::Run(TWindow* w) {
	w->window = SDL_CreateWindow(w->WindowName, 
								w->x,
								w->y, 
								w->Width, 
								w->Height, 
								w->flags);

	w->InitGraphics();

	// main application loop
	bool exit = false;
	while (!exit) {
		w->Paint();
		SDL_Event e;
		while(SDL_PollEvent(&e) != 0) {
			exit = !w->ProcessEvents(&e);
		}
	}

	w->DestroyGraphics();
	SDL_DestroyWindow(w->window);
	TTF_Quit();
	SDL_Quit();
}
