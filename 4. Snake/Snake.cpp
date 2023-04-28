#include <SFML/Graphics.hpp>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <sstream>
using namespace sf;
using namespace std;

int N=31, M=21;
int size=16;
int w = size*N;
int h= size*M;
int czyjest=1, czysiezrespil=1,dead=0,pause=0,ipunkty=0;
string menu="menu";
string punkty;
string menuczyrestart;

int dir, num=4;

struct Snake
{int x=1,y=1;} s[100];

struct Fruct
{int x=1,y=1;} f;


void Tick()
{
  for (int i=num; i>0; i--)
  {s[i].x=s[i-1].x;
  s[i].y=s[i-1].y;}

  if (dir==0) s[0].y+=1;
  if (dir==1) s[0].x-=1;
  if (dir==2) s[0].x+=1;
  if (dir==3) s[0].y-=1;

  if ((s[0].x==f.x) && (s[0].y==f.y))
  {
      num++;
      ipunkty++;
      f.x=rand() % (N-1) +1;
      f.y=rand() % (M-1) +1;
  }

  if (s[0].x<1 || s[0].x>30) dead=1;
  if (s[0].y<1 || s[0].y>20) dead=1;

int j;
    if (s[0].x == s[j+1].x && s[0].y==s[j+1].y)
    {
        dead=1;
    }



}

int main()
{
    srand(time(0));

   RenderWindow window(VideoMode(512,352), "Snake!");

   Texture trawa1,trawa2,ramka,jablko,glowawezaUP,glowawezaDOWN,glowawezaRIGHT,glowawezaLEFT,waz,przegrana,menuglowne,menustart,menuquit
   ,przegranamenu,przegranarestart;
   trawa1.loadFromFile("Images/trawa1.png");
   trawa2.loadFromFile("Images/trawa2.png");
   ramka.loadFromFile("Images/ramka.png");
   jablko.loadFromFile("Images/jablko.png");
   glowawezaDOWN.loadFromFile("Images/glowawezaDOWN.png");
   glowawezaRIGHT.loadFromFile("Images/glowawezaRIGHT.png");
   glowawezaLEFT.loadFromFile("Images/glowawezaLEFT.png");
   glowawezaUP.loadFromFile("Images/glowawezaUP.png");
   waz.loadFromFile("Images/waz.png");
   przegrana.loadFromFile("Images/przegrana.png");
   menuglowne.loadFromFile("Images/menu.png");
   menustart.loadFromFile("images/startmenu.png");
   menuquit.loadFromFile("Images/quitmenu.png");
   przegranamenu.loadFromFile("images/przegranamenu.png");
   przegranarestart.loadFromFile("images/przegranarestart.png");

   Sprite sTrawa1(trawa1), sTrawa2(trawa2), sRamka(ramka), sJablko(jablko), sGlowaweza(glowawezaDOWN), sWaz(waz),
   sPrzegrana(przegrana),sMenu(menuglowne);

   Clock clock;
   float timer=0, delay=0.1;

   f.x=10;
   f.y=10;

   while (window.isOpen())
   {
       float time = clock.getElapsedTime().asSeconds();
       clock.restart();
       timer+=time;

       Font font;
       font.loadFromFile("Bahnschrift.ttf");
       Text tPunkty;

       Event e;
       while (window.pollEvent(e))
       {
           if (e.type== Event::Closed)
            window.close();
       }
      if(menu=="start")
      {
           if (Keyboard::isKeyPressed(Keyboard::Left)) {dir=1; sGlowaweza.setTexture(glowawezaLEFT);}

           if (Keyboard::isKeyPressed(Keyboard::Right)) {dir=2; sGlowaweza.setTexture(glowawezaRIGHT);}

           if (Keyboard::isKeyPressed(Keyboard::Up)) {dir=3; sGlowaweza.setTexture(glowawezaUP);}

           if (Keyboard::isKeyPressed(Keyboard::Down)) {dir=0; sGlowaweza.setTexture(glowawezaDOWN);}
      }


       if (menu=="start" && timer>delay) {timer=0; Tick();}

    if( menu=="start" && dead==1)
     {
         pause=1;
         menu="przegrana";
      }

/////////////draw///////////////////}
    if (menu=="menu")
    {
      window.clear();
      if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(window).x >=187 && Mouse::getPosition(window).y >=151
          && Mouse::getPosition(window).x <=313 && Mouse::getPosition(window).y<=175) menu="start";
            else if (Mouse::getPosition(window).x >=187 && Mouse::getPosition(window).y >=151 &&
                     Mouse::getPosition(window).x <=313 && Mouse::getPosition(window).y <=175 ) sMenu.setTexture(menustart);
            else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(window).x >=225 && Mouse::getPosition(window).y >=191
                     && Mouse::getPosition(window).x<=269 && Mouse::getPosition(window).y <=215) return 0;
                        else if (Mouse::getPosition(window).x >=225 && Mouse::getPosition(window).y >=191
                                 && Mouse::getPosition(window).x <=269 && Mouse::getPosition(window).y <=215) sMenu.setTexture(menuquit);
            else sMenu.setTexture(menuglowne);

                  window.draw(sMenu);

    }

    if (menu=="restart")
    {
      czyjest=1; czysiezrespil=1; dead=0; pause=0; ipunkty=0; num=4; dir=0;
      window.clear();

      s[0].x=1;
      s[0].y=1;

      sGlowaweza.setTexture(glowawezaDOWN);
      if (menuczyrestart=="restart")
      {
        menu="start";
      }
      else if (menuczyrestart=="menu")
      {
        menu="menu";
      }
    }

    if (menu=="start")
    {
       window.clear();

            for (int i=0; i<=N; i++)
                for (int j=0; j<=M; j++)
                {
                    if  ((i==2 || i==4 || i==6 || i==8 || i==10 || i==12 || i==14 || i==16 || i==18 || i==20 || i==22 || i==24 || i==26 || i==28 || i==30)
                         && (j==2 || j==4 || j==6 || j==8 || j==10 || j==12 || j==14 || j==16 || j==18 || j==20))
                    {
                            sTrawa1.setTexture(trawa2);
                    }
                    else if  ((i==1 || i==3 || i==5 || i==7 || i==9 || i==11 || i==13 || i==15 || i==17 || i==19 || i==21 || i==23 || i==25 || i==27 || i==29)
                         && (j==1 || j==3 || j==5 || j==7 || j==9 || j==11 || j==13 || j==15 || j==17 || j==19))
                    {
                           sTrawa1.setTexture(trawa2);
                    }
                    else if ((i>=0 && j==0) || (i==0 && j>=0) )
                    {
                      sTrawa1.setTexture(ramka);
                    }
                    else if ((i==31 && j>=0) || (i>=0 && j==21) )
                    {
                      sTrawa1.setTexture(ramka);
                    }
                    else sTrawa1.setTexture(trawa1);
                    sTrawa1.setPosition(i*size, j*size);
                     window.draw(sTrawa1);
                }
                if(pause==0)
                {
                  for (int i=1; i<num; i++)
                    {
                        sWaz.setPosition(s[i].x*size,s[i].y*size);
                        sGlowaweza.setPosition(s[0].x*size,s[0].y*size);
                        window.draw(sGlowaweza);
                        window.draw(sWaz);
                    }
                }
                sJablko.setPosition(f.x*size, f.y*size); window.draw(sJablko);

                stringstream ss;
                ss<<ipunkty;
                ss>>punkty;
                tPunkty.setFont(font);
                tPunkty.setString(punkty);
                tPunkty.setCharacterSize(30);
                tPunkty.setFillColor(Color::Black);
                tPunkty.setPosition(480,13);

                if (ipunkty>=10 && ipunkty<=19)
                {
                    tPunkty.setPosition(470,13);
                }
                else if (ipunkty>=20)
                {
                    tPunkty.setPosition(465,13);
                }
                window.draw(tPunkty);
     }
                    if(menu=="przegrana")
                   {
                     sPrzegrana.setPosition(128,96);
                        if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(window).x >=189 && Mouse::getPosition(window).y>=182
                           && Mouse::getPosition(window).x <=233 && Mouse::getPosition(window).y<=192) {menu="restart"; menuczyrestart="menu";}
                            else if (Mouse::getPosition(window).x>=189 && Mouse::getPosition(window).y>=172
                                     && Mouse::getPosition(window).x <=  243 && Mouse::getPosition(window).y<=187) sPrzegrana.setTexture(przegranamenu);
                        else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(window).x>=262 && Mouse::getPosition(window).y>=171
                                     && Mouse::getPosition(window).x<=312 && Mouse::getPosition(window).y<=186)  {menu="restart"; menuczyrestart="restart";}
                            else if (Mouse::getPosition(window).x>=262 && Mouse::getPosition(window).y>=171
                                     && Mouse::getPosition(window).x<=312 && Mouse::getPosition(window).y<=186) sPrzegrana.setTexture(przegranarestart);
                                        else sPrzegrana.setTexture(przegrana);
                      window.draw(sPrzegrana);
                   }


            window.display();
   }


  return 0;
}

