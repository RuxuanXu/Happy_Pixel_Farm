#include "menu.h"
#include "UI.h"
#include "map.h"
#include "string.h"
#include "animal.h"

void mainMenu(Screen screen, int *state,sf::Clock&clock)
{
    int x=screen.scrWidth/2,y=screen.scrHeight/2;  //put origin at center
    const sf::Vector2u designedsize(screen.scrWidth,screen.scrHeight);//for windowEvent func in loop

    sf::Texture BG;
    if (!BG.loadFromFile("img/cloudy-sky.jpg",sf::IntRect(0, 0,640, 480)))
    {
        perror(NULL);
    }
    sf::Sprite Title;
    Title.setTexture(BG);
    Title.setPosition(x,y);
    sf::FloatRect rect = Title.getLocalBounds();
    Title.setOrigin(rect.width/2,rect.height/2);

    sf::Texture titleTextT;
    if (!titleTextT.loadFromFile("img/Happy-Pixel-Farm.png",sf::IntRect(0, 0,640, 480)))
    {
        perror(NULL);
    }
    sf::Sprite titleText;
    titleText.setTexture(titleTextT);
    sf::FloatRect TTrect = titleText.getLocalBounds();
    titleText.setOrigin(TTrect.width/2,TTrect.height/2);
    titleText.setPosition(x,y-130);


    sf::Texture scrollT;
    if(!scrollT.loadFromFile("img/scroll.PNG",sf::IntRect(0,0,300,352)))
    {
        perror(NULL);
    }
    sf::Sprite scroll;
    scroll.setTexture(scrollT);
    scroll.setPosition(x,y);
    sf::FloatRect srect = scroll.getLocalBounds();
    scroll.setOrigin(srect.width/2,srect.height/2);

    sf::Texture CursorPic;
    if (!CursorPic.loadFromFile("img/cursor.png",sf::IntRect(0, 0,22, 30)))
    {
        perror(NULL);
    }
    sf::Sprite cursor;
    cursor.setTexture(CursorPic);

    sf::Texture button1;
    if (!button1.loadFromFile("img/button.png",sf::IntRect(0, 0,123, 29)))
    {
        perror(NULL);
    }
    sf::Texture button2;
    if (!button2.loadFromFile("img/button.png",sf::IntRect(0, 30,123, 29)))
    {
        perror(NULL);
    }
    sf::Texture button3;
    if (!button3.loadFromFile("img/button.png",sf::IntRect(0, 60,123, 29)))
    {
        perror(NULL);
    }
    sf::Sprite newGame, option, exit;
    sf::Sprite buttons[3]= {newGame,option,exit};
    for (int i=0; i<3; i++)
    {
        buttons[i].setTexture(button1);
        buttons[i].setScale(1.5f,1.5f);
        if(i==0)
        {
            buttons[i].setPosition(x-buttons[i].getGlobalBounds().width/2,180);
        }
        else
        {
            buttons[i].setPosition(buttons[i-1].getPosition().x,buttons[i-1].getPosition().y+60);
        }
    }

    /////Text Attribute/////
    int fontSize=24;
    sf::Color red(105,53,30,255);
    sf::Color white(255,255,255,255);

    while(*state==0)
    {
        windowEvent(screen.window,designedsize,state);
        screen.window->clear(sf::Color::Black);

        screen.window->draw(Title);
        screen.window->draw(scroll);
        for(int i=0; i<3; i++)
        {
            screen.window->draw(buttons[i]);
            if(click(&buttons[i], &screen,0.2,1)==1)
            {
                buttons[i].setTexture(button3);
                switch(i+1)
                {
                case 1:
                    showText("Play!",screen.window,x,buttons[i].getPosition().y+20,red,fontSize,Middle);
                    *state = 1;
                    break;
                case 2:
                    showText("Special Thanks",screen.window,x,buttons[i].getPosition().y+20,red,fontSize,Middle);
                    break;
                case 3:
                    showText("Goodbye!",screen.window,x,buttons[i].getPosition().y+20,red,fontSize,Middle);
                    *state = 3;
                    break;
                }
            }
            else if(click(&buttons[i], &screen,0.2,1)==2)
            {
                buttons[i].setTexture(button2);
                switch(i+1)
                {
                case 1:
                    showText("Play!",screen.window,x,buttons[i].getPosition().y+20,white,fontSize,Middle);
                    break;
                case 2:
                    showText("Special Thanks",screen.window,x,buttons[i].getPosition().y+20,white,fontSize,Middle);
                    break;
                case 3:
                    showText("Goodbye!",screen.window,x,buttons[i].getPosition().y+20,white,fontSize,Middle);
                    break;
                }
            }
            else
            {
                buttons[i].setTexture(button1);
                switch(i+1)
                {
                case 1:
                    showText("New Game",screen.window,x,buttons[i].getPosition().y+18,white,fontSize,Middle);
                    break;
                case 2:
                    showText("Credits",screen.window,x,buttons[i].getPosition().y+18,white,fontSize,Middle);
                    break;
                case 3:
                    showText("Exit",screen.window,x,buttons[i].getPosition().y+18,white,fontSize,Middle);
                    break;
                }
            }
        }

        screen.window->draw(titleText);

        myCursor(&cursor,&screen);
        screen.window->display();
    }
}

void gamePlay(Screen screen,int *state,sf::Clock&clock)
{
    sf::Texture instruct;
    if (!instruct.loadFromFile("img/instruct.png",sf::IntRect(0, 0,640, 480)))
    {
        perror(NULL);
    }
    sf::Sprite instructS;
    instructS.setTexture(instruct);
    bool instuctionON=false;

    sf::Color dark(25,25,56,70);
    sf::RectangleShape night;
    night.setSize(sf::Vector2f(640,480));
    night.setFillColor(dark);
    Player player;
    player.blood = 10;
    player.holdingAnimal=0;
    Herd herd;
    herd.num=0;
    char money[10];
    player.state = Tool;

    Calendar calendar;
    sf::Clock mapClock[2];

    sf::Color white(255,255,255,255);
    sf::Color sky(122,200,255,255);
    sf::Color Half(255,255,255,100);

    int data[11*11] = {0}; //*size/2

    int x=screen.scrWidth/2,y=screen.scrHeight/2;  //put origin at center
    const sf::Vector2u designedsize(screen.scrWidth,screen.scrHeight);//for windowEvent func in loop

    ////texture attribute////

    sf::Texture button1;
    if (!button1.loadFromFile("img/button.png",sf::IntRect(0, 0,123, 29)))
    {
        perror(NULL);
    }
    sf::Texture button2;
    if (!button2.loadFromFile("img/button.png",sf::IntRect(0, 30,123, 29)))
    {
        perror(NULL);
    }
    sf::Texture button3;
    if (!button3.loadFromFile("img/button.png",sf::IntRect(0, 60,123, 29)))
    {
        perror(NULL);
    }
    sf::Sprite shopButton;
    shopButton.setTexture(button1);
    sf::FloatRect sbg = shopButton.getLocalBounds();
    shopButton.setOrigin(sbg.width/2,sbg.height/2);
    shopButton.setScale(1.2f,1.2f);
    shopButton.setPosition(x,25);

    sf::Texture SkyT;
    if(!SkyT.loadFromFile("img/test.png",sf::IntRect(0,0,640,480)))
    {
        perror(NULL);
    }
    sf::Sprite Background;
    Background.setTexture(SkyT);


    sf::Texture CursorPic;
    if (!CursorPic.loadFromFile("img/cursor.png",sf::IntRect(0, 0,22, 30)))
    {
        perror(NULL);
    }
    sf::Sprite cursor[9];
    cursor[0].setTexture(CursorPic);


    sf::Texture panelT;
    if (!panelT.loadFromFile("img/panel.png",sf::IntRect(0, 0,640, 480)))
    {
        perror(NULL);
    }
    sf::Sprite panel;
    panel.setTexture(panelT);


    Land land;

    //grass tiles//
    sf::Sprite grass;

    sf::Texture tile8;
    if (!tile8.loadFromFile("img/grass.png",sf::IntRect(121, 11,60, 40)))
    {
        perror(NULL);
    }

    sf::Texture tile7;
    if (!tile7.loadFromFile("img/grass.png",sf::IntRect(181, 11,60, 40)))
    {
        perror(NULL);
    }

    sf::Texture tile6;
    if (!tile6.loadFromFile("img/grass.png",sf::IntRect(301, 11,60, 40)))
    {
        perror(NULL);
    }

    sf::Texture tile5;
    if (!tile5.loadFromFile("img/grass.png",sf::IntRect(361, 11,60, 40)))
    {
        perror(NULL);
    }

    sf::Texture tile4;
    if (!tile4.loadFromFile("img/grass.png",sf::IntRect(421, 11,60, 40)))
    {
        perror(NULL);
    }

    sf::Texture tile3;
    if (!tile3.loadFromFile("img/grass.png",sf::IntRect(481, 11,60, 40)))
    {
        perror(NULL);
    }

    sf::Texture tile2;
    if (!tile2.loadFromFile("img/grass.png",sf::IntRect(541, 11,60, 40)))
    {
        perror(NULL);
    }

    sf::Texture tile1;
    if (!tile1.loadFromFile("img/grass.png",sf::IntRect(601, 11,60, 40)))
    {
        perror(NULL);
    }
    grass.setTexture(tile1);
    sf::Texture tile[8]= {tile1,tile2,tile3,tile4,tile5,tile6,tile7,tile8};
    for(int i=0; i<8; i++)
    {
        land.tile[i]=tile[i];
    }
    land.sprite = grass;
    for(int i=0; i<11*11; i++)
    {
        land.data[i]=data[i];
    }

    //grass tiles end//

    //profile set//
    sf::Texture minimap;
    if(!minimap.loadFromFile("img/player.png",sf::IntRect(0,0,130,128)))
    {
        perror(NULL);
    }

    sf::Texture cubeT;
    if(!cubeT.loadFromFile("img/player.png",sf::IntRect(130,83,49,44)))
    {
        perror(NULL);
    }
    sf::Texture cubeT2;
    if(!cubeT2.loadFromFile("img/player.png",sf::IntRect(180,83,49,44)))
    {
        perror(NULL);
    }
    sf::Texture bloodT;
    if(!bloodT.loadFromFile("img/player.png",sf::IntRect(196,0,8,14)))
    {
        perror(NULL);
    }
    sf::Sprite blood[10];
    for(int i =0; i<10; i++)
    {
        blood[i].setTexture(bloodT);
    }
    blood[0].setPosition(x+268,y-222);

    int cubeNum=10;
    sf::Sprite cube1,cube2,cube3,cube4,cube5,cube6,cube7,cube8,cube9,cube10;
    sf::Sprite cube[10]= {cube1,cube2,cube3,cube4,cube5,cube6,cube7,cube8,cube9,cube10};
    int toolNum=2;
    sf::Sprite tool1,tool2;
    sf::Sprite tool[2]= {tool1,tool2};
    tool[0].setTexture(CursorPic);
    sf::Sprite pickAnimal;
    sf::Texture waterT;
    if(!waterT.loadFromFile("img/cursor.png",sf::IntRect(22, 0,18, 30)))
    {
        perror(NULL);
    }
    tool[1].setTexture(waterT);
    cursor[1].setTexture(waterT);
    cursor[1].setOrigin(cursor[1].getLocalBounds().width/2,0);
    sf::Texture holdAnimal[7];
    if(!holdAnimal[0].loadFromFile("img/cursor.png",sf::IntRect(44, 0,48, 45)))
    {
        perror(NULL);
    }
    if(!holdAnimal[1].loadFromFile("img/cursor.png",sf::IntRect(90, 0,48, 45)))
    {
        perror(NULL);
    }
    if(!holdAnimal[2].loadFromFile("img/cursor.png",sf::IntRect(145, 1,26, 44)))
    {
        perror(NULL);
    }
    if(!holdAnimal[3].loadFromFile("img/cursor.png",sf::IntRect(179, 1,50, 44)))
    {
        perror(NULL);
    }
    if(!holdAnimal[4].loadFromFile("img/cursor.png",sf::IntRect(232, 1,50, 44)))
    {
        perror(NULL);
    }
    if(!holdAnimal[5].loadFromFile("img/cursor.png",sf::IntRect(289, 1,30, 44)))
    {
        perror(NULL);
    }
    if(!holdAnimal[6].loadFromFile("img/cursor.png",sf::IntRect(334, 0,31, 45)))
    {
        perror(NULL);
    }

    for(int i =2; i<9; i++)
    {
        cursor[i].setTexture(holdAnimal[i-2]);
        cursor[i].setOrigin(cursor[i].getLocalBounds().width/2,0);
    }

    for(int i=0; i<cubeNum; i++)
    {
        cube[i].setTexture(cubeT);
        if(i==0)
        {
            cube[i].setPosition(x-175,y+183);
        }
        else
        {
            cube[i].setPosition(cube[i-1].getPosition().x+48,cube[i-1].getPosition().y);
        }
    }
    for(int i=0; i<toolNum; i++)
    {
        if(i==0)
        {
            tool[i].setPosition(x-158,y+190);
        }
        else
        {
            tool[i].setPosition(cube[i-1].getPosition().x+66,tool[i-1].getPosition().y);
        }
    }

    sf::Texture colorBallG;
    if(!colorBallG.loadFromFile("img/player.png",sf::IntRect(130,0,16,16)))
    {
        perror(NULL);
    }
    sf::Texture colorBallG2;
    if(!colorBallG2.loadFromFile("img/player.png",sf::IntRect(130,16,16,16)))
    {
        perror(NULL);
    }
    sf::Texture colorBallG3;
    if(!colorBallG3.loadFromFile("img/player.png",sf::IntRect(130,32,16,16)))
    {
        perror(NULL);
    }
    sf::Sprite ballG;
    ballG.setTexture(colorBallG);
    ballG.setPosition(20+88,340+10);


    sf::Texture colorBallB;
    if(!colorBallB.loadFromFile("img/player.png",sf::IntRect(146,0,16,16)))
    {
        perror(NULL);
    }
    sf::Texture colorBallB2;
    if(!colorBallB2.loadFromFile("img/player.png",sf::IntRect(146,16,16,16)))
    {
        perror(NULL);
    }
    sf::Texture colorBallB3;
    if(!colorBallB3.loadFromFile("img/player.png",sf::IntRect(146,32,16,16)))
    {
        perror(NULL);
    }
    sf::Sprite ballB;
    ballB.setTexture(colorBallB);
    ballB.setPosition(20+104,340+26);

    sf::Texture colorBallR;
    if(!colorBallR.loadFromFile("img/player.png",sf::IntRect(162,0,16,16)))
    {
        perror(NULL);
    }
    sf::Texture colorBallR2;
    if(!colorBallR2.loadFromFile("img/player.png",sf::IntRect(162,16,16,16)))
    {
        perror(NULL);
    }
    sf::Texture colorBallR3;
    if(!colorBallR3.loadFromFile("img/player.png",sf::IntRect(162,32,16,16)))
    {
        perror(NULL);
    }
    sf::Sprite ballR;
    ballR.setTexture(colorBallR);
    ballR.setPosition(20+18,340+96);

    sf::Texture faceT[4];
    for(int i=0; i<4; i++)
    {
        if(!faceT[i].loadFromFile("img/face.png",sf::IntRect(i*48,0,48,48)))
        {
            perror(NULL);
        }
    }
    sf::Sprite face;
    face.setTexture(faceT[0]);
    face.setPosition(x+120,y-220);

    //profile set end//

    ////texture attribute end////

    ////animal////

    int animalType = 6;
    int prize[6];
    prize[0]=15,prize[1]=15,prize[2]=5;
    prize[3]=100,prize[4]=100,prize[5]=50;

    sf::Texture animalT[6];
    if(!animalT[0].loadFromFile("img/porcupine+shark family.png",sf::IntRect(0,0,48,34)))
    {
        perror(NULL);
    }
    if(!animalT[1].loadFromFile("img/porcupine+shark family.png",sf::IntRect(48,0,48,34)))
    {
        perror(NULL);
    }
    if(!animalT[2].loadFromFile("img/porcupine+shark family.png",sf::IntRect(99,10,32,24)))
    {
        perror(NULL);
    }
    if(!animalT[3].loadFromFile("img/porcupine+shark family.png",sf::IntRect(0,35,48,36)))
    {
        perror(NULL);
    }
    if(!animalT[4].loadFromFile("img/porcupine+shark family.png",sf::IntRect(48,35,48,36)))
    {
        perror(NULL);
    }
    if(!animalT[5].loadFromFile("img/porcupine+shark family.png",sf::IntRect(99,45,32,26)))
    {
        perror(NULL);
    }
    sf::Sprite animalButton[6];
    for(int i=0; i<6; i++)
    {
        animalButton[i].setTexture(animalT[i]);
        animalButton[i].setOrigin(animalButton[i].getLocalBounds().width/2,animalButton[i].getLocalBounds().height/2);
        animalButton[i].setPosition(cube[i].getPosition().x+cube[i].getLocalBounds().width/2,cube[i].getPosition().y+cube[i].getLocalBounds().height/2);

    }
    int movement = 0;
    int step = 0;

    while(*state == 1)//main loop
    {
        land.sprite.setPosition(x-32,100);
        windowEvent(screen.window,designedsize,state);
        screen.window->clear(sf::Color::Black);
        screen.window->draw(Background);
        drawMap(&screen,&land,&mapClock[0],&player,&herd,&cursor[0]);
        drawAnimal(&herd,&screen,&land,&player,&movement,&step,&animalButton[0],&animalT[0]);

        if(calendar.hour>17||calendar.hour<5)
        {
            screen.window->draw(night);
        }

        screen.window->draw(panel);
        screen.window->draw(ballR);
        screen.window->draw(ballG);
        screen.window->draw(ballB);
        screen.window->draw(face);

        feed(&herd,&player,&face,&faceT[0],&screen);

        screen.window->draw(blood[0]);
        for(int i=1; i<player.blood; i++)
        {
            blood[i].setPosition(blood[i-1].getPosition().x-8,y-222);
            screen.window->draw(blood[i]);
        }

        if(click(&ballR, &screen,0,1)==1&&!player.holdingAnimal)
        {
            ballR.setTexture(colorBallR3);
        }
        else if(click(&ballR, &screen,0,1)==2)
        {
            ballR.setTexture(colorBallR2);
            showText("HINT",screen.window,ballR.getPosition().x+8,ballR.getPosition().y-10,white,20,Middle);
        }
        else
        {
            ballR.setTexture(colorBallR);
        }

        if(click(&ballG, &screen,0,1)==1&&!player.holdingAnimal)
        {
            player.state = Tool;
            player.holding = Bare;
            ballG.setTexture(colorBallG3);
            showText("TOOL",screen.window,ballG.getPosition().x+8,ballG.getPosition().y-10,white,20,Middle);

        }
        else if(click(&ballG, &screen,0,1)==2&&!player.holdingAnimal)
        {
            ballG.setTexture(colorBallG2);
            showText("TOOL",screen.window,ballG.getPosition().x+8,ballG.getPosition().y-10,white,20,Middle);
        }
        else
        {
            if(player.state==Tool)
            {
                ballG.setTexture(colorBallG2);
            }
            else
            {
                ballG.setTexture(colorBallG);
            }
        }

        if(click(&ballB, &screen,0,1)==1&&!player.holdingAnimal)
        {
            player.holding = Bare;
            player.state = Shop;
            ballB.setTexture(colorBallB3);
            showText("SHOP",screen.window,ballB.getPosition().x+8,ballB.getPosition().y-10,white,20,Middle);

        }
        else if(click(&ballB, &screen,0,1)==2&&!player.holdingAnimal)
        {
            ballB.setTexture(colorBallB2);
            showText("SHOP",screen.window,ballB.getPosition().x+8,ballB.getPosition().y-10,white,20,Middle);
        }
        else
        {
            if(player.state==Shop)
            {
                ballB.setTexture(colorBallB2);
            }
            else
            {
                ballB.setTexture(colorBallB);
            }
        }

        ShopAndTool(&player,&cursor[0],&herd,&prize[0],cubeNum,toolNum,animalType,&cube[0],&tool[0],&animalButton[0],&screen,cubeT,cubeT2,&animalT[0]);

        showCalendar(&screen,&calendar,x-170,y-25);
        if(click(&shopButton,&screen,0.1,2)==1)
        {
            shopButton.setTexture(button3);
            if(instuctionON==true)
            {
                instuctionON = false;
            }
            else
            {
                instuctionON = true;
            }
        }
        else if(click(&shopButton,&screen,0,2)==2)
        {
            shopButton.setTexture(button2);
        }
        else
        {
            shopButton.setTexture(button1);
        }

        screen.window->draw(shopButton);
        showText("Instructions",screen.window,x,shopButton.getPosition().y-2,white,20,Middle);
        itoa(player.money,money,10);
        showText(money,screen.window,x+275,y-175,white,20,Right);


        if(instuctionON==true)
        {
            screen.window->draw(instructS);
        }

        //always show on top
        switch(player.holding)
        {
        case Bare:
            switch(player.holdingAnimal)
            {
            case 0:
                myCursor(&cursor[0],&screen);
                break;
            case 1:
                myCursor(&cursor[2],&screen);
                break;
            case 2:
                myCursor(&cursor[3],&screen);
                break;
            case 3:
                myCursor(&cursor[4],&screen);
                break;
            case 4:
                myCursor(&cursor[5],&screen);
                break;
            case 5:
                myCursor(&cursor[6],&screen);
                break;
            case 6:
                myCursor(&cursor[7],&screen);
                break;
            case 7:
                myCursor(&cursor[8],&screen);
                break;
            }
            break;
        case Water:
            myCursor(&cursor[1],&screen);
            break;
        }
        screen.window->display();
    }
}
