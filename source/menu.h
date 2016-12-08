#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

struct Screen
{
    int scrWidth, scrHeight;
    sf::RenderWindow *window;
};

void mainMenu(Screen screen,int *state,sf::Clock&clock);
void gamePlay(Screen screen,int *state,sf::Clock&clock);

#endif // MENU_H_INCLUDED
