#include <time.h>
#include "menu.h"

enum {Title,Start,Load,Exit};

int main()
{

    srand(time(NULL));
    Screen myScreen;
    myScreen.scrWidth = 640, myScreen.scrHeight = 480;
    sf::RenderWindow window0(sf::VideoMode(myScreen.scrWidth,myScreen.scrHeight), "Happy Pixel Farm");
    myScreen.window = &window0;
    //window can be resized and maintain same ratio in window event func

    myScreen.window->setFramerateLimit(30); //FPS limit, 24 is our limit to tell the difference
    int state = Title;

    while(myScreen.window->isOpen())
    {
        sf::Clock clock; //to control I/O speed

        if(!state)
        {
            mainMenu(myScreen,&state,clock);
        }
        if(state == Start || state == Load)
        {
            gamePlay(myScreen,&state,clock);
        }
        if(state == Exit)
        {
            myScreen.window->close();

        }
    }
    return 0;
}
