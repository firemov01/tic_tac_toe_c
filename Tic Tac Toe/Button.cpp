#include "Button.h"

Button::Button()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

Button::Button(int BUTTON_WIDTH, int BUTTON_HEIGHT)
{
	this->BUTTON_HEIGHT = BUTTON_HEIGHT;
	this->BUTTON_WIDTH = BUTTON_WIDTH;
	mPosition.x = 0;
	mPosition.y = 0;
}

void Button::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void Button::setStatus(int status) {
	this->status = status;
}

int Button::getStatus() {
	return status;
}

bool Button::insideButton(int x, int y)
{
	//Get mouse position

	//Check if mouse is in button
	bool inside = true;

	//Mouse is left of the button
	if (x < mPosition.x)
	{
		inside = false;
	}
	//Mouse is right of the button
	else if (x > mPosition.x + BUTTON_WIDTH)
	{
		inside = false;
	}
	//Mouse above the button
	else if (y < mPosition.y)
	{
		inside = false;
	}
	//Mouse below the button
	else if (y > mPosition.y + BUTTON_HEIGHT)
	{
		inside = false;
	}
	
	return inside;
}