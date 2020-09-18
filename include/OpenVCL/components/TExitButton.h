#pragma once

class TExitButton : public TControl {
public:
	bool clicked = false;
	float sizeXClose = 45;
	float sizeYClose = 25;
	float offsetY = 8;
	float offsetX = 18;

	void Draw(SDL_Renderer* renderer, FC_Font* font) override;
	void MD() override;
	void MU() override;

	TExitButton(TWindow* owner);

};