#include "OpenVCL/OpenVCL.h"

void TButton::Draw(SDL_Renderer* renderer, FC_Font* font) {

	if (InBounds(owner->GetLastMouseX(), owner->GetLastMouseY())) {
		if (clicked) {
			roundedRectangleRGBA(renderer, boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, radius, 255, 255, 255, 26);
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	} else 
		SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);

	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	roundedRectangleRGBA(renderer, boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, radius, r, g, b, a);
	FC_Draw(font, renderer, boundingBox.x, boundingBox.y, label);
}

void TButton::MD() {
	clicked = true;
}

void TButton::MU() {
	if (clicked && InBounds(owner->GetLastMouseX(), owner->GetLastMouseY()) && OnClick != nullptr)
		OnClick(this);
	clicked = false;
}

TButton::TButton(TWindow* owner, int x, int y, const char* label) : TControl(owner) {

	this->label = label;
	this->x = x;
	this->y = y;
	sizeX = 60;
	sizeY = 24;

	radius = sizeY / 2;

	UpdateBoundingBox();
}
