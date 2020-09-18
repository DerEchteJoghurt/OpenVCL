#pragma once

#include "OpenVCL/OpenVCL.h"

class TButton : public TControl {
private:
	bool clicked = false;
public:
	TButton(TWindow* owner, int x, int y, const char* label);
	void Draw(SDL_Renderer* renderer, FC_Font* font) override;
	void MD() override;
	void MU() override;

	void (*OnClick)(TControl* Sender) = 0;

	const char* label = "Button";
	int radius = 0;
};