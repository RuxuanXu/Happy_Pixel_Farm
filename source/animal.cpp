#include "animal.h"

void Move(Animal *animal,sf::Clock *clock,Direction direction,int step)
{
    if(clock->getElapsedTime().asSeconds()>0.1)
    {
        switch (direction)
        {
        case L:
            animal->position[0]-=step;
            if(animal->faceTo==1)
            {
                animal->sprite.scale(-1.0f,1.0f);
                animal->faceTo=0;
            }
            break;
        case R:
            animal->position[0]+=step;
            if(animal->faceTo==0)
            {
                animal->sprite.scale(-1.0f,1.0f);
                animal->faceTo=1;
            }
            break;
        case U:
            animal->position[1]-=step;
            break;
        case D:
            animal->position[1]+=step;
            break;
        }
        clock->restart();
    }
}
void animalMove(Animal *animal,Land *land,int *movement,int *step)
{
    float animalX = animal->sprite.getPosition().x;
    float animalY = animal->sprite.getPosition().y;
    Direction movement0 = (Direction)*movement;
    *step=((rand()%5) +1);
    bool canMove = false;
    float routeX,routeY;

    for(int i=0; i<11*11; i++)
    {
        if (animalX>land->position[i][0]-30&&
                animalX<land->position[i][0]+90&&
                animalY>land->position[i][1]-20&&
                animalY<land->position[i][1]+60)
        {
            if(animal->state==0)
            {
                *movement=rand()%4;

                if(animalX>320&&*movement==0)
                {
                    *movement=rand()%2;
                    if(*movement==0)*movement=rand()%2;
                    movement0 = (Direction)*movement;
                }
                if(animalX<320&&*movement==1)
                {
                    *movement=rand()%2;
                    if(*movement==1)*movement=rand()%2;
                    movement0 = (Direction)*movement;
                }
                if(animalX>240&&*movement==3)
                {
                    *movement=rand()%2+2;
                    if(*movement==3)*movement=rand()%2+2;
                    movement0 = (Direction)*movement;
                }
                if(animalX<240&&*movement==2)
                {
                    *movement=rand()%2+2;
                    if(*movement==2)*movement=rand()%2+2;
                    movement0 = (Direction)*movement;
                }
            }
            canMove = true;
            if(land->data[i]>0&&animal->clock[0].getElapsedTime().asSeconds()>2)
            {
                animal->state = 1;
                animal->destination = 0;
                animal->minRoute = 1120;
                animal->minRoute = 640;
                if(animal->full<20)
                {
                    animal->full+=1;
                }
                if(animal->full>=20)
                {
                    animal->state = 0;
                }
                if(land->position[i][0]<animalX&&animal->faceTo==1)
                {
                    animal->sprite.scale(-1.0f,1.0f);
                    animal->faceTo = 0;
                }
                if(land->position[i][0]>animalX-animal->sprite.getLocalBounds().width/2&&
                        animal->faceTo==0&&animal->full<20)
                {
                    animal->sprite.scale(-1.0f,1.0f);
                    animal->faceTo = 1;
                }
                land->data[i]--;
                animal->clock[0].restart();
            }
            if(land->data[i]==0&&animal->state!=3)
            {
                animal->state = 0;
            }

            if(!land->data[i]&&animal->state!=1)
            {
                for(int q=0; q<11*11; q++)
                {
                    routeX = abs(land->position[i][0]-land->position[q][0]);
                    routeY = abs(land->position[i][1]-land->position[q][1]);
                    if(routeX+routeY<animal->minRoute&&land->data[q]>land->data[i])
                    {
                        animal->destination = q;
                        animal->minRoute = routeX + routeY;
                        animal->state = 3;
                    }
                }
                if(animal->state!=3&&animal->state!=4&&animal->state!=5)
                {
                    animal->state = 0;
                    Move(animal,&animal->clock[1],movement0,*step);
                }
                else
                {
                    if(animal->state==3)
                    {
                        if(animalX>land->position[animal->destination][0])
                        {
                            Move(animal,&animal->clock[2],L,*step);
                        }
                        else if(animalX<land->position[animal->destination][0])
                        {
                            Move(animal,&animal->clock[2],R,*step);
                        }
                        if(animalY>land->position[animal->destination][1])
                        {
                            Move(animal,&animal->clock[2],U,*step);
                        }
                        else if(animalY<land->position[animal->destination][1])
                        {
                            Move(animal,&animal->clock[2],D,*step);
                        }
                    }
                }
            }
        }
    }
    if(!canMove)
    {
        if(animalX>320)
        {
            Move(animal,&animal->clock[0],L,*step);
        }
        else
        {
            Move(animal,&animal->clock[0],R,*step);
        }
        if(animalY>240)
        {
            Move(animal,&animal->clock[1],U,*step);
        }
        else
        {
            Move(animal,&animal->clock[1],D,*step);
        }
    }
    animal->sprite.setPosition(animal->position[0],animal->position[1]);
}
bool Breed(Herd *herd,Animal *animal,sf::Sprite sprite[0],Player *player,sf::Texture texture[0])
{
    Animal newAnimal;
    sf::Color white(255,255,255,255);
    sf::Color vanish(0,0,0,0);
    sf::Color red(255,0,0,255);
    for(int q=0; q<herd->num; q++)
    {
        if(herd->animal[q].kind-3<=0&&animal->kind-3>0&& &herd->animal[q] != animal &&
                herd->hold!=q+1&&(&herd->animal[herd->hold-1]!=animal)&&animal->alive==true)
        {
            herd->animal[q].sprite.setColor(white);
            if(animal->sprite.getPosition().y>herd->animal[q].sprite.getPosition().y-30&&
                    animal->sprite.getPosition().y<herd->animal[q].sprite.getPosition().y+30&&
                    animal->sprite.getPosition().x>herd->animal[q].sprite.getPosition().x-40&&
                    animal->sprite.getPosition().x<herd->animal[q].sprite.getPosition().x+40)
            {
                if(herd->animal[q].alive==true)
                {
                    herd->animal[q].blood--;
                    herd->animal[q].sprite.setColor(red);
                }
                else
                {
                    delAnimal(herd,q);
                }
                animal->full++;
            }
        }
    }
    switch(animal->kind)
    {
    case 1:
    case 4:
        for(int q=0; q<herd->num; q++)
        {
            if(herd->animal[q].kind==animal->kind+1&&
                    herd->hold!=q+1&&(&herd->animal[herd->hold-1]!=animal)&&herd->animal[q].alive==true)
            {
                if(animal->sprite.getPosition().y>herd->animal[q].sprite.getPosition().y-30&&
                        animal->sprite.getPosition().y<herd->animal[q].sprite.getPosition().y+30&&
                        animal->sprite.getPosition().x>herd->animal[q].sprite.getPosition().x-40&&
                        animal->sprite.getPosition().x<herd->animal[q].sprite.getPosition().x+40&&
                        animal->clock[3].getElapsedTime().asSeconds()<10&&animal->clock[4].getElapsedTime().asSeconds()>10)
                {
                    if(animal->state!=5)
                    {
                        animal->clock[3].restart();
                    }
                    animal->state=5;
                    herd->animal[q].state=5;
                    animal->sprite.setPosition(herd->animal[q].sprite.getPosition().x,herd->animal[q].sprite.getPosition().y);
                    animal->sprite.setColor(vanish);
                    herd->animal[q].sprite.setColor(vanish);

                    return true;
                }
                else
                {
                    animal->clock[3].restart();
                    if(animal->state==5&&animal->alive==true&&herd->animal[q].alive==true)
                    {
                        switch(animal->kind)
                        {
                        case 1:
                            Initialize(&newAnimal,3,&sprite[0],&texture[0]);
                            newAnimal.sprite=sprite[2];
                            break;
                        case 4:
                            Initialize(&newAnimal,6,&sprite[0],&texture[0]);
                            newAnimal.sprite=sprite[5];
                            break;
                        }
                        addAnimal(herd,&newAnimal,sprite,player);
                        herd->animal[herd->num-1].position[0]=herd->animal[q].sprite.getPosition().x;
                        herd->animal[herd->num-1].position[1]=herd->animal[q].sprite.getPosition().y;
                        animal->clock[4].restart();
                        animal->state=0;
                    }
                }
            }
            animal->sprite.setColor(white);
            herd->animal[q].sprite.setColor(white);
        }
    }

    return false;
}
void drawAnimal(Herd *herd,Screen *screen,Land *land,Player *player,int *movement,int *step,sf::Sprite sprite[0],sf::Texture texture[0])
{

    sf::Color white(255,255,255,255);
    sf::Color red(255,0,0,255);
    sf::Color yellow(255,255,102,255);
    sf::Color green(154,205,50,255);
    sf::Color brown(165,42,42,255);
    sf::Color vanish(0,0,0,0);
    sf::Color dark(0,0,0,200);
    sf::Color Hdark(128,128,128,255);
    sf::RectangleShape rectangle[50];
    sf::RectangleShape rectangle2[20];
    sf::Texture breedingT[2];
    if(!breedingT[0].loadFromFile("img/porcupine+shark family.png",sf::IntRect(135,5,65,30)))
    {
        perror(NULL);
    }
    if(!breedingT[1].loadFromFile("img/porcupine+shark family.png",sf::IntRect(145,45,60,35)))
    {
        perror(NULL);
    }
    sf::Sprite breeding[2];
    for(int i=0; i<2; i++)
    {
        breeding[i].setTexture(breedingT[i]);
        breeding[i].setOrigin(breeding[i].getLocalBounds().width/2,breeding[i].getLocalBounds().height/2);
    }
    int a=0;
    int two;
    for(int i=0; i<herd->num; i++)
    {
        if(herd->animal[i].blood<=0)
        {
            if(herd->animal[i].alive==true)
            {
                herd->animal[i].alive=false;
            }
            herd->animal[i].sprite.setColor(dark);
            if(touchAnimal(&herd->animal[i],player,screen)==2)
            {
                player->holdingAnimal = 7;
                herd->hold=i+1;
            }

            if(herd->hold != i+1)
            {
                screen->window->draw(herd->animal[i].sprite);
            }
            a=1;
        }
        else
        {
            a=0;
        }

        if(!a)
        {

            if(herd->animal[i].clock[6].getElapsedTime().asSeconds()>30)
            {
                if(herd->animal[i].kind == 3||herd->animal[i].kind == 6)
                {
                    two = rand()%2+1;
                    herd->animal[i].kind -= two;
                    herd->animal[i].texture = texture[herd->animal[i].kind-1];
                    herd->animal[i].sprite = sprite[herd->animal[i].kind-1];
                    herd->animal[i].clock[6].restart();
                }
                else
                {
                    if(herd->animal[i].clock[6].getElapsedTime().asSeconds()>100)
                    {
                        herd->animal[i].sprite.setColor(Hdark);
                    }
                    if(herd->animal[i].clock[6].getElapsedTime().asSeconds()>120)
                    {
                        herd->animal[i].blood --;
                    }
                }
            }

            if(herd->animal[i].full>0&&herd->animal[i].clock[5].getElapsedTime().asSeconds()>=2)
            {
                herd->animal[i].clock[5].restart();
                herd->animal[i].full--;
            }
            if(herd->animal[i].blood>0&&herd->animal[i].full<=0&&herd->animal[i].clock[5].getElapsedTime().asSeconds()>=1)
            {
                herd->animal[i].clock[5].restart();
                herd->animal[i].blood-=5;
            }

            if(herd->animal[i].alive==true)
            {
                if(!Breed(herd,&herd->animal[i],&sprite[0],player,&texture[0]))
                {
                    if(herd->hold!=0)
                    {
                        if(i+1 != herd->hold)
                        {
                            animalMove(&herd->animal[i],land,movement,step);
                            screen->window->draw(herd->animal[i].sprite);
                        }
                    }
                    else
                    {
                        if(touchAnimal(&herd->animal[i],player,screen)==2)
                        {
                            if(herd->animal[i].kind<=6&&herd->animal[i].kind>0)
                            {
                                player->holdingAnimal = herd->animal[i].kind;
                                herd->hold=i+1;
                                herd->animal[herd->hold-1].state = 0;
                            }
                            else
                            {
                                animalMove(&herd->animal[i],land,movement,step);
                                screen->window->draw(herd->animal[i].sprite);
                            }

                        }
                        else if(touchAnimal(&herd->animal[i],player,screen)==1)
                        {
                            for (int b=0; b<50; b++)
                            {
                                if(b<herd->animal[i].blood)
                                {
                                    rectangle[b].setFillColor(red);
                                }
                                else
                                {
                                    rectangle[b].setFillColor(brown);
                                }
                                rectangle[b].setSize(sf::Vector2f(1,3));
                                rectangle[b].setPosition(herd->animal[i].sprite.getPosition().x-25+b,herd->animal[i].sprite.getPosition().y-25);
                                screen->window->draw(rectangle[b]);
                            }

                            for(int b=0; b<20; b++)
                            {
                                if(b<herd->animal[i].full)
                                {
                                    rectangle2[b].setFillColor(yellow);
                                }
                                else
                                {
                                    rectangle2[b].setFillColor(green);
                                }
                                rectangle2[b].setSize(sf::Vector2f(2.5,3));
                                rectangle2[b].setPosition(herd->animal[i].sprite.getPosition().x-25+b*2.5,herd->animal[i].sprite.getPosition().y-20);
                                screen->window->draw(rectangle2[b]);
                            }
                            animalMove(&herd->animal[i],land,movement,step);
                            screen->window->draw(herd->animal[i].sprite);
                        }
                        else
                        {
                            animalMove(&herd->animal[i],land,movement,step);
                            screen->window->draw(herd->animal[i].sprite);
                        }
                    }
                }
            }
            if(herd->animal[i].state==5&&herd->animal[i].alive==true)
            {
                switch(herd->animal[i].kind)
                {
                case 1:
                case 2:
                    breeding[0].setPosition(herd->animal[i].sprite.getPosition().x,herd->animal[i].sprite.getPosition().y);
                    screen->window->draw(breeding[0]);
                    break;
                case 3:
                case 4:
                    breeding[1].setPosition(herd->animal[i].sprite.getPosition().x,herd->animal[i].sprite.getPosition().y);
                    screen->window->draw(breeding[1]);
                    break;
                }

            }
        }
    }
}
bool addAnimal(Herd *herd,Animal *animal,sf::Sprite cursor[0],Player *player)
{
    if(herd->num<100)
    {
        herd->animal[herd->num] = *animal;
        herd->num++;
        return 1;
    }
    else
    {
        return 0;
    }
}
int touchAnimal(Animal *animal,Player *player,Screen *screen)
{
    if(player->holding==Bare&&player->holdingAnimal==0)
    {
        if(click(&animal->sprite,screen,0,2)==2)
        {
            return 1;
        }
        else if(click(&animal->sprite,screen,0.3,2)==1)
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}
void Initialize(Animal *animal,int kind,sf::Sprite animalS[0],sf::Texture animalT[0])
{
    animal->kind=kind;
    animal->state=0;
    animal->minRoute=640;
    sf::Texture texture;
    sf::Sprite sprite;
    animal->texture=animalT[kind-1];
    animal->sprite.setTexture(animal->texture);
    animal->blood = 50;
    animal->full=20;
    animal->position[0]= 0;
    animal->position[1]=0;
    animal->destination = 0;
    animal->alive=true;
}
void delAnimal(Herd *herd,int num)
{
    for(int i=num+1; i<herd->num; i++)
    {
        herd->animal[i-1]=herd->animal[i];
    }
    herd->num--;
}
void feed(Herd *herd,Player *player,sf::Sprite *face,sf::Texture faceT[0],Screen *screen)
{
    if(player->holdingAnimal!=0&&click(face,screen,0,1)==2)
    {
        face->setTexture(faceT[2]);
    }
    else if(player->holdingAnimal!=0&&click(face,screen,0,1)==1)
    {
        face->setTexture(faceT[3]);
        switch(player->holdingAnimal)
        {
        case 1:
            player->money += 10;
            break;
        case 2:
            player->money += 10;
            break;
        case 3:
            player->money += 5;
            break;
        case 4:
            player->money += 50;
            break;
        case 5:
            player->money += 50;
            break;
        case 6:
            player->money += 20;
            break;
        default:
            player->money += 5;
        }
        player->holdingAnimal=0;
        delAnimal(herd,herd->hold-1);
        herd->hold = 0;
    }
    else if(player->holdingAnimal==0&&click(face,screen,0,1)==2)
    {
        face->setTexture(faceT[1]);
    }
    else
    {
        face->setTexture(faceT[0]);
    }

}
