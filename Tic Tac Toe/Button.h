#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Button
{
public:
    //Initializes internal variables
    Button();
    Button(int BUTTON_WIDTH, int BUTTON_HEIGHT);

    //Sets top left position
    void setPosition(int x, int y);
    void setButtonSize(int BUTTON_WIDTH, int BUTTON_HEIGHT);

    //Handles mouse event
    bool insideButton(int x, int y);
    void setStatus(int status);
    int getStatus();

    //Shows button sprite
    //void render();

private:
    //Top left position
    SDL_Point mPosition;
    int status = 2;
    int BUTTON_WIDTH;
    int BUTTON_HEIGHT;
    //Currently used global sprite
    //LButtonSprite mCurrentSprite;
};