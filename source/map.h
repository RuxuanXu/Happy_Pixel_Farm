#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include "UI.h"
#include "animal.h"

struct Herd;
struct Player;

struct Land
{
    sf::Sprite sprite;
    sf::Texture tile[8];
    int data[11*11] = {0};
    float position[11*11][2]={{0}};
};

void drawMap(Screen *screen,Land *land,sf::Clock *clock,Player *player,Herd *herd,sf::Sprite cursor[0]);

#endif // MAP_H_INCLUDED
