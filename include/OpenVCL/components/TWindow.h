#pragma once

#include "OpenVCL/OpenVCL.h"

class TWindow {
public:

	//GETTER
	SDL_Window* Window();
	int GetWidth();
	int GetHeight();
	int GetWindowX();
	int GetWindowY();
	const char* GetWindowName();
	PointerList<TControl> controls;
	SDL_Color background = {0x1a, 0x1a, 0x1a, 0xff};

	int GetLastMouseX() { return lastMouseX; };
	int GetLastMouseY() { return lastMouseY; };

	//SETTER
	void SetSize(int Width, int Height);
	void SetPos(int X, int Y);
	void SetName(const char* WindowName);

	//Functions
	void Show();
	void Hide();
	void Update();

private:
	//Inner Workings
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    FC_Font* font = nullptr;

	const char* WindowName = "Window";
	int Width = 500;
	int Height = 500;
	int x = SDL_WINDOWPOS_UNDEFINED;
	int y = SDL_WINDOWPOS_UNDEFINED;
    int flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS;

	int lastMouseX = 0;
	int lastMouseY = 0;

	// DEBUG VARS
	bool mb_down = false;
	bool buttonPressed = false;
	bool executeEvent = false;
	// END DEBUG VARS

	TExitButton* exit = new TExitButton(this);

	bool titlebarMD = false;
	SDL_Rect titlebar;

    bool ProcessEvents(SDL_Event* e);
    void InitGraphics();
	void DestroyGraphics();
    void Paint();
	void Resize();

	friend class Application;
};