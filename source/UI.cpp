#include<string.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "UI.h"


sf::View calcView(const sf::Vector2u&windowsize, const sf::Vector2u&designedsize)
{
    sf::FloatRect viewport(0.f, 0.f, 1.f, 1.f);

    float screenwidth = windowsize.x / static_cast<float>(designedsize.x);
    float screenheight = windowsize.y / static_cast<float>(designedsize.y);

    if(screenwidth > screenheight)
    {
        viewport.width = screenheight / screenwidth;
        viewport.left = (1.f - viewport.width) / 2.f;
    }
    else if(screenwidth < screenheight)
    {
        viewport.height = screenwidth / screenheight;
        viewport.top = (1.f - viewport.height) / 2.f;
    }

    sf::View view( sf::FloatRect( 0, 0, designedsize.x , designedsize.y ) );
    view.setViewport(viewport);

    return view;
}
//Window closed and resized. Should be in every loop.
void windowEvent(sf::RenderWindow* window,const sf::Vector2u&designedsize,int *state)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
            *state=3;

        }
        if (event.type == sf::Event::Resized)
        {
            if (event.size.width<640)
            {
                window->setSize(sf::Vector2u(640,event.size.height));
            }
            if (event.size.height<480)
            {
                window->setSize(sf::Vector2u(event.size.width,480));
            }
            window->setView(calcView(sf::Vector2u(event.size.width, event.size.height), designedsize));
        }

    }
}

void showText(const char *words,sf::RenderWindow* window,int x,int y,sf::Color color,int size,textStyle style)
{
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("RUBBBB.TTF"))
    {
        perror(NULL);
    }
    text.setFont(font);
    text.setString(words);
    text.setCharacterSize(size);
    text.setColor(color);
    text.setStyle(sf::Text::Bold);
    sf::FloatRect textRect = text.getLocalBounds();
    switch(style)
    {
    case Right:
        text.setOrigin(textRect.left+textRect.width,
                       textRect.top+textRect.height/2);
        text.setPosition(sf::Vector2f(x,y));
        break;
    case Middle:
        text.setOrigin(textRect.left+textRect.width/2,
                       textRect.top+textRect.height/2);
        text.setPosition(sf::Vector2f(x,y));
        break;
    }
    window->draw(text);
}

int click(sf::Sprite* sprite, Screen *screen,const float wait,const int style)
{
    sf::Clock myClock;
    bool press = 0;
    sf::FloatRect rect = sprite->getLocalBounds();
    float mx = sf::Mouse::getPosition(*screen->window).x;
    float my = sf::Mouse::getPosition(*screen->window).y;
    float wSizeX = screen->window->getSize().x;
    float wSizeY = screen->window->getSize().y;
    float spriteX;
    float spriteY;
    float spriteScaleX=sprite->getScale().x;
    if(spriteScaleX<0)
    {
        spriteScaleX*=-1;
    }

    switch(style)
    {
    case 1:
        spriteX = sprite->getPosition().x;
        spriteY = sprite->getPosition().y;
        break;
    case 2:
        spriteX = sprite->getPosition().x-rect.width/2;
        spriteY = sprite->getPosition().y-rect.height/2;
        break;
    default:
        spriteX = sprite->getPosition().x;
        spriteY = sprite->getPosition().y;
    }


    if(wSizeY/wSizeX <= 0.75)
    {
        if( sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                mx >= spriteX * wSizeY/480 + (wSizeX-640* wSizeY/480)/2 &&
                mx <= (spriteX + rect.width* spriteScaleX) * wSizeY/480 + (wSizeX-640* wSizeY/480)/2 &&
                my >= spriteY * wSizeY/480 &&
                my <= (spriteY + rect.height * sprite->getScale().y) * wSizeY/480)
        {
            myClock.restart();
            press = 1;
        }
        else if( mx >= spriteX * wSizeY/480 + (wSizeX-640* wSizeY/480)/2 &&
                 mx <= (spriteX + rect.width* spriteScaleX) * wSizeY/480 + (wSizeX-640* wSizeY/480)/2 &&
                 my >= (spriteY * wSizeY/480) &&
                 my <= (spriteY + rect.height* sprite->getScale().y) * wSizeY/480 )
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if( sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                mx >= spriteX * wSizeX/640  &&
                mx <= (spriteX + rect.width* spriteScaleX) * wSizeX/640 &&
                my >=  spriteY * wSizeX/640 + (wSizeY-480* wSizeX/640)/2  &&
                my <= (spriteY + rect.height* sprite->getScale().y) * wSizeX/640 + (wSizeY-480* wSizeX/640)/2 )
        {
            myClock.restart();
            press = 1;
        }
        else if( mx >= spriteX * wSizeX/640  &&
                 mx <= (spriteX + rect.width* spriteScaleX) * wSizeX/640 &&
                 my >= spriteY * wSizeX/640 + (wSizeY-480* wSizeX/640)/2 &&
                 my <= (spriteY + rect.height* sprite->getScale().y) * wSizeX/640 + (wSizeY-480* wSizeX/640)/2 )
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
    while(press==1)
    {
        if (myClock.getElapsedTime().asSeconds()>wait)
        {
            return 1;
        }
    }
    return 4;
}

void myCursor(sf::Sprite* sprite,Screen *screen)
{
    float mx = sf::Mouse::getPosition(*screen->window).x;
    float my = sf::Mouse::getPosition(*screen->window).y;
    float wSizeX = screen->window->getSize().x;
    float wSizeY = screen->window->getSize().y;
    float scrW = screen->scrWidth, scrH = screen->scrHeight;

    if(wSizeY/wSizeX <= scrH/scrW)
    {
        sprite->setPosition((mx-(wSizeX-scrW*wSizeY/scrH)/2)*(scrH/wSizeY),my*(scrH/wSizeY));
    }
    else
    {
        sprite->setPosition(mx*(scrW/wSizeX),(my-(wSizeY-scrH*wSizeX/scrW)/2)*(scrW/wSizeX));
    }
    screen->window->draw(*sprite);
    screen->window->setMouseCursorVisible(false);
}

void showCalendar(Screen *screen,Calendar *calendar,const int x,const int y)
{
    sf::Color white(255,255,255,255);
    int textSize =20;

    if(calendar->clock.getElapsedTime().asSeconds()>1)
    {
        calendar->min += 15;
        calendar->clock.restart();
        if (calendar->min==60)
        {
            calendar->hour++;
            calendar->min = 0;
        }
        if (calendar->hour==24)
        {
            calendar->day++;
            calendar->hour = 0;
        }
        if (calendar->day==31)
        {
            calendar->month++;
            calendar->day = 1;
        }
        if (calendar->month==5)
        {
            calendar->year++;
            calendar->month = 1;
        }
    }

    char yrStr[6]= {0};
    itoa(calendar->year,yrStr,10);
    char season[10];
    char *spring = "SPRING",*summer = "SUMMER",*autumn="AUTUMN",*winter="WINTER";
    switch (calendar->month)
    {
    case 1:
        strcpy(season,spring);
        break;
    case 2:
        strcpy(season,summer);
        break;
    case 3:
        strcpy(season,autumn);
        break;
    case 4:
        strcpy(season,winter);
        break;
    }
    char dayStr[3];
    itoa(calendar->day,dayStr,10);
    char minStr[3];
    itoa(calendar->min,minStr,10);
    char zminStr[4]= "0";
    strcat (zminStr,minStr);
    char hrStr[3];
    itoa(calendar->hour,hrStr,10);
    char zhrStr[4]= "0";
    strcat (zhrStr,hrStr);

    showText(yrStr,screen->window,x-75,y-180,white,textSize,Right);
    showText(season,screen->window,x-12,y-180,white,textSize,Right);
    showText(dayStr,screen->window,x+6,y-180,white,textSize,Right);
    if(calendar->hour<10)
    {
        showText(zhrStr,screen->window,x-60,y-160,white,textSize,Right);
    }
    else
    {
        showText(hrStr,screen->window,x-60,y-160,white,textSize,Right);
    }
    showText(":",screen->window,x-50,y-160,white,textSize+20,Right);
    if(calendar->min<10)
    {
        showText(zminStr,screen->window,x-28,y-160,white,textSize,Right);
    }
    else
    {
        showText(minStr,screen->window,x-28,y-160,white,textSize,Right);
    }
}
