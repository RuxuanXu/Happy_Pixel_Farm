#include "player.h"

void ShopAndTool(Player *player,sf::Sprite cursor[0],Herd *herd,int prize[0],int cubeNum,int toolNum,int animalNum,sf::Sprite cube[0],sf::Sprite tool[0],sf::Sprite animalButton[0],Screen *screen,sf::Texture cubeT,sf::Texture cubeT2,sf::Texture animalT[0])
{
    sf::Color white(255,255,255,255);
    sf::Color Half(255,255,255,100);
    char prizeC[10];
    Animal newAnimal;

    if(player->state == Tool)
    {
        for(int i=0; i<toolNum; i++)
        {
            if(click(&cube[i], screen,0,1)==1)
            {
                cube[i].setTexture(cubeT);
                if(player->holdingAnimal==0)
                {
                    player->holding=i;
                }
            }
            else if(click(&cube[i], screen,0,1)==2&&player->holdingAnimal==0)
            {
                cube[i].setTexture(cubeT2);
            }
            else
            {
                cube[i].setTexture(cubeT);
            }
            screen->window->draw(cube[i]);
        }

        for(int i=0; i<toolNum; i++)
        {
            if(player->holding!=i)
            {
                tool[i].setColor(white);
                screen->window->draw(tool[i]);
            }
            else
            {
                tool[i].setColor(Half);
                screen->window->draw(tool[i]);
            }
        }
    }
    else if(player->state == Shop)
    {
        for(int i=0; i<animalNum; i++)
        {
            if(click(&cube[i], screen,0.3,1)==1&&player->holdingAnimal==0)
            {
                cube[i].setTexture(cubeT);
                if(player->money>=prize[i]&&herd->num<100)
                {
                    Initialize(&newAnimal,i+1,&animalButton[0],&animalT[0]);
                    newAnimal.sprite=animalButton[i];
                    addAnimal(herd,&newAnimal,&cursor[0],player);
                    player->money-=prize[i];
                    player->holdingAnimal = i+1;
                    herd->hold = herd->num;
                }
            }
            else if(click(&cube[i], screen,0,1)==2&&player->holdingAnimal==0)
            {
                itoa(prize[i],prizeC,10);
                strcat(prizeC,"$");
                cube[i].setTexture(cubeT2);
                showText(prizeC,screen->window,cube[i].getPosition().x+cube[i].getLocalBounds().width/2+6,cube[i].getPosition().y-10,white,20,Middle);
            }
            else
            {
                cube[i].setTexture(cubeT);
            }
            screen->window->draw(cube[i]);
        }
        for(int i=0; i<animalNum; i++)
        {
            if(player->money>=prize[i])
            {
                animalButton[i].setColor(white);
            }
            else
            {
                animalButton[i].setColor(Half);
            }
            screen->window->draw(animalButton[i]);
        }
    }
}
