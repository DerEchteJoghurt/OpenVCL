#include "OpenVCL/OpenVCL.h"

#ifdef _DEBUG_OVCL
#include "Helper/console.h"
#endif

#pragma region Getter

SDL_Window* TWindow::Window() { return window; }
int TWindow::GetWidth() { return Width; }
int TWindow::GetHeight() { return Height; }
int TWindow::GetWindowX() { return x; }
int TWindow::GetWindowY() { return y; }
const char* TWindow::GetWindowName() { return WindowName; }

#pragma endregion

#pragma region Setter

void TWindow::SetSize(int Width, int Height) {
	this->Width = Width;
	this->Height = Height;
	if (window)
		SDL_SetWindowSize(window, Width, Height);
}

void TWindow::SetPos(int X, int Y) {
	this->x = X;
	this->y = Y;
	if (window)
		SDL_SetWindowPosition(window, x, y);
}

void TWindow::SetName(const char* WindowName) {
	this->WindowName = WindowName;
	if (window)
		SDL_SetWindowTitle(window, WindowName);
}

#pragma endregion

#pragma region WindowFunctions

void TWindow::Show() { 
	if (window)
		SDL_ShowWindow(window);
}
void TWindow::Hide() { 
	if (window)
		SDL_HideWindow(window);
}
void TWindow::Update() {

}

#pragma endregion

#pragma region InternalMagic

#ifdef _WIN32
#define FONT_PATH "C:/Windows/fonts/Arial.ttf"
#else
#define FONT_PATH "/usr/share/fonts/truetype/freefont/FreeSansOblique.ttf"
#endif

void TWindow::InitGraphics() {
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	font = FC_CreateFont();
	// TODO everything that uses a font should be able to load its own font
	FC_LoadFont(font, renderer, FONT_PATH, 18, {255, 255, 255, 255}, 0);
	SDL_CaptureMouse(SDL_TRUE);
}

void TWindow::DestroyGraphics() {
	FC_FreeFont(font);
	SDL_DestroyRenderer(renderer);
}

// VERY BAD DEBUG CODE
void TWindow::Paint() {
	titlebar = { 0, 0, Width - 45, 25 };

	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
	SDL_RenderClear(renderer);

	// Titlebar Text (buggy)
	//pBrush->SetColor(D2D1::ColorF(1, 1, 1, 0.5));
	//pRenderTarget->DrawText(WindowName, wcslen(WindowName), pTextFormat, titlebar, pBrush);

	// Accent Color
	SDL_Color accent = {255, 128, 0, 255};

	thickLineRGBA(renderer, 0, 0, Width, 0, 5, accent.r, accent.g, accent.b, accent.a);

	exit->Draw(renderer, font);

	// Draw all Controls. draw in reverse order
	for (size_t i = controls.length(); 0 < i; i--)
		controls.get(i - 1)->Draw(renderer, font);

#ifdef _DEBUG_OVCL
		// DEBUG DRAWINGS
		pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow, 0.5));
		pRenderTarget->FillRectangle({ (float)lastMouseX -5, (float)lastMouseY-5, (float)lastMouseX + 5, (float)lastMouseY + 5 }, pBrush);

		// Draw Controls Bounding Boxes
		for (size_t i = 0; i < controls.length(); i++)
			pRenderTarget->DrawRectangle(controls.get(i)->boundingBox, pBrush);

		// END DEBUG DRAWINGS
#endif

	SDL_RenderPresent(renderer);
}

void TWindow::Resize()
{
	Update();
}

bool TWindow::ProcessEvents(SDL_Event* e) {
	switch (e->type) {
	case SDL_QUIT:
		return false;

	case SDL_WINDOWEVENT_RESIZED:
		Width = e->window.data1;
		Height = e->window.data2;
		Resize();
		return true;

	case SDL_MOUSEMOTION:

		if(titlebarMD){
			SetPos(x + (e->motion.x - lastMouseX), y + (e->motion.y - lastMouseY));
			return true;
		}

		lastMouseX = e->motion.x;
		lastMouseY = e->motion.y;
		Update();
		return true;

	case SDL_MOUSEBUTTONDOWN:
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			if (IN_BOUNDS(e->button.x, e->button.y, titlebar)) {
				titlebarMD = true;
				return true;
			}

			if (exit->InBounds(e->button.x, e->button.y)) exit->MD();
			else {
				for (size_t i = 0; i < controls.length(); i++) {
					if (controls.get(i)->InBounds(e->button.x, e->button.y)) {
						controls.get(i)->MD();
						break;
					}
				}
			}

			Update();
		}
		return true;

	case SDL_MOUSEBUTTONUP:
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			titlebarMD = false;

			exit->MU();
			for (size_t i = 0; i < controls.length(); i++)
				controls.get(i)->MU();
			Update();
		}
		return true;
	}

	return true;
}

#pragma endregion

void TExitButton::Draw(SDL_Renderer* renderer, FC_Font* font) {

	boundingBox = { owner->GetWidth() - (int) sizeXClose, 0, owner->GetWidth(), (int) sizeYClose };

	if (InBounds(owner->GetLastMouseX(), owner->GetLastMouseY())) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &boundingBox);

		if (clicked) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 102);
			SDL_RenderFillRect(renderer, &boundingBox);
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	} else
		SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);

	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

	thickLineRGBA(renderer, owner->GetWidth() - sizeXClose + offsetX, offsetY, owner->GetWidth() - offsetX, sizeYClose - offsetY, 1.5f, r, g, b, a);
	thickLineRGBA(renderer, owner->GetWidth() - sizeXClose + offsetX, sizeYClose - offsetY, owner->GetWidth() - offsetX, offsetY, 1.5f, r, g, b, a);
}

void TExitButton::MD() {
	clicked = true;
}

void TExitButton::MU() {
	if (clicked && InBounds(owner->GetLastMouseX(), owner->GetLastMouseY()))
	{
		SDL_Event e;
		e.type = SDL_QUIT;
    	SDL_PushEvent(&e);
	}
		
	clicked = false;
}

TExitButton::TExitButton(TWindow* owner) : TControl(owner) {}
