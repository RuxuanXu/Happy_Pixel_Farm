#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "map.h"

void drawMap(Screen *screen,Land *land,sf::Clock *clock,Player *player,Herd *herd,sf::Sprite cursor[0])
{
    sf::Color white(255,255,255,255);
    sf::Color dark(220,200,200,255);
    sf::FloatRect rect = land->sprite.getLocalBounds();
    int a = 1, size = 2;
    int index = 0; //index of data
    int position = -40;
    int tileNum = 8;
    float slowdown = 0.1;
    float cursorX,cursorY,animalSize;

    cursorX=cursor[player->holdingAnimal+1].getPosition().x;
    cursorY=cursor[player->holdingAnimal+1].getPosition().y;
    animalSize = cursor[player->holdingAnimal+1].getLocalBounds().height*2/3;


    for(index=0; index<11*11; index++)
    {
        if (land->data[index]>=5&&clock[1].getElapsedTime().asSeconds()>6)
        {
            land->data[index]--;
        }
    }
    if(clock[1].getElapsedTime().asSeconds()>6)
    {
        clock[1].restart();
    }

    index = 0;

    for(int i=0; i<11*size ; i++)
    {
        if(i%2!=0)
        {
            for(int q=0; q<a; q++)
            {
                if(i<=5*size)
                {
                    if(q==0)
                    {
                        land->sprite.setPosition(land->sprite.getPosition().x+rect.width*3/2,land->sprite.getPosition().y+rect.height/3+1);
                    }

                    land->sprite.setPosition(land->sprite.getPosition().x-rect.width,land->sprite.getPosition().y);

                }
                else
                {
                    if(q==0)
                    {
                        land->sprite.setPosition(land->sprite.getPosition().x+rect.width*1/2,land->sprite.getPosition().y+rect.height/3+1);
                    }
                    land->sprite.setPosition(land->sprite.getPosition().x-rect.width,land->sprite.getPosition().y);

                }
                if(click(&land->sprite,screen,0,1)==1)
                {
                    land->sprite.setColor(white);
                    if (land->data[index]<tileNum-1&&clock[0].getElapsedTime().asSeconds()>slowdown&&player->holding==Water)
                    {
                        clock[0].restart();
                        land->data[index]++;
                    }
                    if(player->holdingAnimal>0)
                    {
                        if(herd->animal[herd->hold-1].alive==false)
                        {
                            herd->animal[herd->hold-1].sprite.setPosition(cursorX,cursorY+animalSize);
                        }
                        else
                        {
                            herd->animal[herd->hold-1].state = 0;
                            herd->animal[herd->hold-1].destination = 0;
                            herd->animal[herd->hold-1].minRoute = 640;
                            herd->animal[herd->hold-1].position[0]=cursorX;
                            herd->animal[herd->hold-1].position[1]=cursorY+animalSize;
                        }

                        herd->hold = 0;
                        player->holdingAnimal = 0;
                    }
                }
                else if(click(&land->sprite,screen,0,1)==2&&player->holdingAnimal==0)
                {
                    land->sprite.setColor(dark);
                }
                else
                {
                    land->sprite.setColor(white);
                }

                land->sprite.setTexture(land->tile[land->data[index]]);
                if(!player->firstTime)
                {
                    land->position[index][0]=land->sprite.getPosition().x;
                    land->position[index][1]=land->sprite.getPosition().y;
                }

                index++;
                screen->window->draw(land->sprite);
            }
        }
        else
        {
            for(int q=0; q<a; q++)
            {
                if(i<=5*size)
                {
                    if(q==0&&i!=0)
                    {
                        land->sprite.setPosition(land->sprite.getPosition().x-rect.width*3/2,land->sprite.getPosition().y+rect.height/3+1);
                    }
                    if(i==0)
                    {
                        land->sprite.setPosition(land->sprite.getPosition().x,land->sprite.getPosition().y+position);
                    }
                    else
                    {
                        land->sprite.setPosition(land->sprite.getPosition().x+rect.width,land->sprite.getPosition().y);
                    }
                }
                else
                {
                    if(q==0)
                    {
                        land->sprite.setPosition(land->sprite.getPosition().x-rect.width*1/2,land->sprite.getPosition().y+rect.height/3+1);
                    }
                    land->sprite.setPosition(land->sprite.getPosition().x+rect.width,land->sprite.getPosition().y);

                }

                if(click(&land->sprite,screen,0,1)==1)
                {
                    land->sprite.setColor(white);
                    if (land->data[index]<tileNum-1&&clock[0].getElapsedTime().asSeconds()>slowdown&&player->holding==Water)
                    {
                        clock[0].restart();
                        land->data[index]++;
                    }
                    if(player->holdingAnimal>0)
                    {
                        if(herd->animal[herd->hold-1].alive==false)
                        {
                            herd->animal[herd->hold-1].sprite.setPosition(cursorX,cursorY+animalSize);
                        }
                        else
                        {
                            herd->animal[herd->hold-1].state = 0;
                            herd->animal[herd->hold-1].destination = 0;
                            herd->animal[herd->hold-1].minRoute = 640;
                            herd->animal[herd->hold-1].position[0]=cursorX;
                            herd->animal[herd->hold-1].position[1]=cursorY+animalSize;
                        }

                        herd->hold = 0;
                        player->holdingAnimal = 0;
                    }
                }
                else if(click(&land->sprite,screen,0,1)==2&&player->holdingAnimal==0)
                {
                    land->sprite.setColor(dark);
                }
                else
                {
                    land->sprite.setColor(white);
                }

                land->sprite.setTexture(land->tile[land->data[index]]);
                if(!player->firstTime)
                {
                    land->position[index][0]=land->sprite.getPosition().x;
                    land->position[index][1]=land->sprite.getPosition().y;
                }

                index++;

                screen->window->draw(land->sprite);
            }
        }

        if(i<5*size)
        {
            a++;
        }
        else
        {
            a--;
        }
    }
    player->firstTime=1;
}

