#pragma once

#include "OpenVCL/OpenVCL.h"

class TWindow;

class TControl {
protected:
	SDL_Rect boundingBox = { 0 };
	TWindow* owner;
	int x = -1;
	int y = -1;
	int sizeX = 0;
	int sizeY = 0;

	void UpdateBoundingBox() {
		boundingBox.x = x;
		boundingBox.w = x + sizeX;
		boundingBox.y = y;
		boundingBox.h = y + sizeY;
	}

public:
	TControl(TWindow* owner) { this->owner = owner; };
	bool InBounds(int x, int y) { return IN_BOUNDS(x, y, boundingBox); }
	void SetSize(int length, int height) { sizeX = length; sizeY = height; UpdateBoundingBox(); }
	void SetPos(int x, int y) { this->x = x; this->y = y; UpdateBoundingBox(); }

	virtual void Draw(SDL_Renderer* renderer, FC_Font* font) = 0;


	// Mouse Button Handling POC
	virtual void MD() {};
	virtual void MU() {};


	friend class TWindow;
};