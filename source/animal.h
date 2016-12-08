#ifndef ANIMAL_H_INCLUDED
#define ANIMAL_H_INCLUDED
#include "UI.h"
#include "menu.h"
#include "map.h"
#include <stdlib.h>
enum Direction{R,L,U,D};
struct Land;
struct Player;
struct Animal
{
    int kind=0,state=0;
    float minRoute = 640;
    int destination = 0;
    sf::Texture texture;
    sf::Sprite sprite;
    int blood = 50;
    int full=20;
    float position[2]={0,0};
    bool faceTo = 0;
    sf::Clock clock[7];
    bool alive=true;
};

struct Herd
{
    int num=0;
    int hold = 0;
    Animal animal[100];
};
void Move(Animal *animal,sf::Clock *clock,Direction direction,int step);
void animalMove(Animal *animal,sf::Clock *clock,Land *land,int *movement,int *step);
bool Breed(Herd *herd,Animal *animal,sf::Sprite sprite[0],Player *player,sf::Texture texture[0]);
void drawAnimal(Herd *herd,Screen *screen,Land *land,Player *player,int *movement,int *step,sf::Sprite sprite[0],sf::Texture texture[0]);
bool addAnimal(Herd *herd,Animal *animal,sf::Sprite cursor[0],Player *player);
int touchAnimal(Animal *animal,Player *player,Screen *screen);
void Initialize(Animal *animal,int kind,sf::Sprite animalS[0],sf::Texture animalT[0]);
void delAnimal(Herd *herd,int num);
void feed(Herd *herd,Player *player,sf::Sprite *face,sf::Texture faceT[0],Screen *screen);

#endif // ANIMAL_H_INCLUDED
