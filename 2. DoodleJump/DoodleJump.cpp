#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include <windows.h>
using namespace sf;
using namespace std;

int g=0;

struct point
{int x,y ;};

double o;

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    app.setFramerateLimit(60);

    Font font;
    font.loadFromFile("al-seana.ttf");
    Text text;

    SoundBuffer  start,jump,dead;
    Sound start1,jump1,dead1;
    start.loadFromFile("music/start.flac");
    jump.loadFromFile("music/jump.flac");
    dead.loadFromFile("music/pada.flac");
    jump1.setBuffer(jump);
    start1.setBuffer(start);
    dead1.setBuffer(dead);

    Texture t1,t2,t3,t4;
    t1.loadFromFile("Images/background.png");
    t2.loadFromFile("Images/platform.png");
    t3.loadFromFile("Images/doodleleft.png");
    t4.loadFromFile("Images/doodleright.png");

    Sprite sBackground(t1), sPlat(t2), sPers(t3);

    point plat[20];

    for (int i=0; i<10; i++)
    {
        //int u,u1;
        plat[i].x=rand()%400;
        //u=plat[i+1].x;
        plat[i].y=rand()%533;
        /*u1=plat[i+1].y;
        if (plat[i].x <= u)
        {
            plat[i].x+=68;
        }
        if (plat[i].y <= u1)
        {
            plat[i].y+=14;
        }
        if (plat[i].x > 370 )
        {
            plat[i].x-=30;
        }
*/

    }

     int x=100, y=100, h=200;
     float dx=0, dy=0;
    while (app.isOpen())
    {

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }
            if( Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 360 && Mouse::getPosition(app).y >= 0
       && Mouse::getPosition(app).x <= 390 && Mouse::getPosition(app).y <= 30)
       {
        system("pause");
       }
        if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                sPers.setTexture(t4);
                 x+=5;

            }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            sPers.setTexture(t3);
            x-=5;
        }
         stringstream ss;
        ss<<o;
        string p;
        ss>>p;
        text.setFont(font);
        text.setString(p);
        text.setCharacterSize(30);
        text.setFillColor(Color::Black);


        dy+=0.2;
        y+=dy;
        if (y>600) {dy=-10; dead1.play(); Sleep(2000); return 0;}

        if (y<h) //sluzy do podnoszenia okienka
            for (int i=0; i<10; i++)
        {
            y=h;
            o=o+0.2;
            plat[i].y=plat[i].y-dy;
            if (plat[i].y>533)
                {
                    //int u;
                    plat[i].y=0;
                    plat[i].x=rand()%400;
                    /*u=plat[i].x;
                    if (plat[i].x <= u)
                    {
                        plat[i].x+=68;
                    }
                    */
                }
        }

        for (int i=0; i<10; i++)
    if ((x+50>plat[i].x) && (x+20<plat[i].x+68)
        && (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0))
        {
            jump1.play();
            dy=-10;
        }



        app.draw(sBackground);
        sPers.setPosition(x,y);
        int k,l;
        if (x>400)
        {
            x=l;
          sPers.setPosition(l,y);
        }
        if (x < -60)
        {
            x=k;
            k=400;
         sPers.setPosition(k,y);
        }
        app.draw(sPers);



        for (int i=0; i<10; i++)
        {
            if  (plat[i].x >= 330)
            {
                plat[i].x -=70;
            }
            sPlat.setPosition(plat[i].x, plat[i].y);
            int u,u1;
            u=plat[i].x;
            u1=plat[i].y;
            if (plat[i].x > u && plat[i].x < u+68)
            {
              plat[i].x +=68;
            }
            if (plat[i].y > u1 && plat[i].y < u1+68)
            {
              plat[i].y +=20;
            }
            app.draw(sPlat);
        }

        app.draw(text);

        app.display();
        if (g==0)
        {
            Sleep(3000);
            g=1;
        }
        if (g==1)
        {
        start1.setVolume(50.f);
        start1.play();
        g=2;
        }

    }


    return 0;
}
