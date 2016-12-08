#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "UI.h"
#include "animal.h"
#include <string.h>

enum thingOnHand{Bare,Water};
enum panelState{Shop,Tool};
struct Herd;
struct Calendar
{
    sf::Clock clock;
    int year = 2016, month = 1, day = 1, hour = 7, min = 0;
};
struct Player
{
    int money = 1000;
    int holding = Bare;
    int holdingAnimal = 0;
    bool firstTime = 0;
    int blood=10;
    panelState state=Tool;
};
void ShopAndTool(Player *player,sf::Sprite cursor[0],Herd *herd,int prize[0],int cubeNum,int toolNum,int animalNum,sf::Sprite cube[0],sf::Sprite tool[0],
                 sf::Sprite animalButton[0],Screen *screen,sf::Texture cubeT,sf::Texture cubeT2,sf::Texture animalT[0]);
#endif // PLAYER_H_INCLUDED
