#include"menu.h"
#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED
#include"player.h"

enum textStyle{Right,Middle};
struct Calendar;

sf::View calcView(const sf::Vector2u &windowsize, const sf::Vector2u &designedsize);
void windowEvent(sf::RenderWindow* window,const sf::Vector2u&designedsiz,int *state);
void showText(const char *words,sf::RenderWindow* window,int x,int y,sf::Color color,int size,textStyle style);
int click(sf::Sprite* sprite, Screen *screen,const float wait,const int style);
void myCursor(sf::Sprite* sprite,Screen *screen);
void showCalendar(Screen *screen,Calendar *calendar,const int x,const int y);

#endif // UI_H_INCLUDED
