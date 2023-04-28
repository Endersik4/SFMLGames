#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

int wybor,wybor2,kordyX,kordyY,zycia=3,pilka=1,startrys=0,kordyXB,kordyYB,nextlvl=0;
int stop,razy,level=1,kordyX1,kordyY1,backmenu,respienie=0,wygranal1=36 ,wygranal2=45,wygranal3=63,wygranal4=81,wygranal5=99;
int pmv=50,psv=50,dzwieki=1,ulepszenie,randomoweulepszenie=0,pkX,pkY,ilepozycji=0,zmianapaletki=2,zmianapilki=2,niezniszczalnosc=1,los,czyjest=0;
string pm="ON", ps="ON";

clock_t start, stopc;
double czas;

bool isCollide(Sprite s1,Sprite s2)
{
  return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

int main()
{

    srand(time(0));

    RenderWindow app(VideoMode(960, 540), "Arkanoid!");
    app.setFramerateLimit(60);
///////////////////////////Grafika///////////////////////////////////////
    Texture l1,l2,l3,l4,l5,t2,t3,t4,menu,pause,resume,lose,zycie,menustart,menuload,menusett,menuquit,loserestart,losemenu
    ,load,loadl1,loadl2,loadl3,loadl4,loadl5,menuback,win,winnext,winmenu,sett,settm,settmv,setts,settsv,strzalki,strzalkiwgore,strzalkiwdol,
    ulepszeniepaletki,pogorszeniepaletki,ulepszeniepilki,pogorszeniepilki,niezniszczalnoscpilki,ulepszonapaletka,pogorszonapaletka,ulepszonapilka,pogorszonapilka,niezniszczalnapilka;
    l1.loadFromFile("Images/block01.png"); l2.loadFromFile("Images/block02.png"); l3.loadFromFile("Images/block03.png");l4.loadFromFile("Images/block04.png"); l5.loadFromFile("Images/block05.png");
    win.loadFromFile("Images/wygrana.png"); winmenu.loadFromFile("Images/wygranamenu.png"); winnext.loadFromFile("Images/wygrananext.png");
    strzalki.loadFromFile("Images/strzalki.png"); strzalkiwdol.loadFromFile("Images/strzalkawdol.png"); strzalkiwgore.loadFromFile("Images/strzalkawgore.png");
    menu.loadFromFile("Images/menu.png"); menustart.loadFromFile("Images/menustart.png"); menuload.loadFromFile("Images/menuload.png"); menusett.loadFromFile("Images/menusett.png");menuquit.loadFromFile("Images/menuquit.png");
    load.loadFromFile("images/load.png"); loadl1.loadFromFile("images/loadlevel1.png"); loadl2.loadFromFile("images/loadlevel2.png"); loadl3.loadFromFile("images/loadlevel3.png"); loadl4.loadFromFile("images/loadlevel4.png");loadl5.loadFromFile("images/loadlevel5.png");
    sett.loadFromFile("Images/settings.png"); settm.loadFromFile("Images/settingsmusic.png"); settmv.loadFromFile("Images/settingsmusicvolume.png"); setts.loadFromFile("Images/settingssounds.png"); settsv.loadFromFile("Images/settingssoundsvolume.png");
    lose.loadFromFile("Images/gameover.png"); losemenu.loadFromFile("Images/gameovermenu.png"); loserestart.loadFromFile("images/gameoverrestart.png");
    ulepszeniepaletki.loadFromFile("Images/ulepszeniepaletki.png"); pogorszeniepaletki.loadFromFile("Images/pogorszeniepaletki.png");
    ulepszeniepilki.loadFromFile("Images/ulepszeniepilki.png"); pogorszeniepilki.loadFromFile("Images/pogorszeniepilki.png"); niezniszczalnoscpilki.loadFromFile("Images/niezniszczalnoscpilki.png");
    ulepszonapaletka.loadFromFile("Images/ulepszonapaletka.png"); pogorszonapaletka.loadFromFile("Images/pogorszonapaletka.png");
    niezniszczalnapilka.loadFromFile("Images/niezniszczalnapilka.png");
    zycie.loadFromFile("Images/serce.png");
    pause.loadFromFile("Images/pause.png");
    resume.loadFromFile("Images/resume.png");
    menuback.loadFromFile("images/menuback.png");
    t2.loadFromFile("Images/background.jpg");
    t3.loadFromFile("Images/ball.png");
    t4.loadFromFile("Images/paddle.png");

    Sprite sBackground(t2), sBall(t3), sPaddle (t4),sMenu(menu),sPause(pause),sResume(resume)
    ,sLose(lose),sZycie1(zycie),sZycie2(zycie),sZycie3(zycie),sLoad(load),sMenuback{menuback}
    ,sWin(win),sSett(sett),sStrzalki(strzalki),sStrzalki2(strzalki),sUlepszenie;
    sPaddle.setPosition(410,500);
    sBall.setPosition(480,484);

    Sprite block[1000],blockl2[1000],blockl3[1000],blockl4[1000],blockl5[1000];
///////////////////////////DŸwiêki///////////////////////////////////////

    SoundBuffer bPrzegrana,bWygrana,bStrzaly,bUderzenieocegle,bUderzenieopaletke,bUderzenieosciane,BDead;
    bPrzegrana.loadFromFile("sounds/przegrana.wav");
    bWygrana.loadFromFile("sounds/wygrana.wav");
    bStrzaly.loadFromFile("sounds/strzaly.wav");
    bUderzenieocegle.loadFromFile("sounds/uderzenieocegle.wav");
    bUderzenieopaletke.loadFromFile("sounds/uderzenieopaletke.wav");
    bUderzenieosciane.loadFromFile("sounds/uderzenieosciane.wav");
    BDead.loadFromFile("sounds/umieranie.wav");

    Sound sPrzegrana,sWygrana,sStrzaly,sUderzenieocegle,sUderzenieopaletke,sUderzenieosciane,sDead;
    sPrzegrana.setBuffer(bPrzegrana);
    sWygrana.setBuffer(bWygrana);
    sStrzaly.setBuffer(bStrzaly);
    sUderzenieocegle.setBuffer(bUderzenieocegle);
    sUderzenieopaletke.setBuffer(bUderzenieopaletke);
    sUderzenieosciane.setBuffer(bUderzenieosciane);
    sDead.setBuffer(BDead);

    sf::Music meni;
    meni.openFromFile("sounds/menu.flac");
    meni.play();
    meni.setLoop(true);

    Font procenty;
    procenty.loadFromFile("clacon.ttf");
    Text procentym,procentymv,procentys,procentysv,strzalawgore,strzalkawdol;
///////////////////////Respienie Blokow////////////////////////////////////////////////////
    int n=0,n1=0,n2=0,n3=0,n4=0;
        for (int i=1; i<=9; i++){for (int j=1; j<=4; j++) {block[n].setTexture(l1); block[n].setPosition(i*85,j*25); n++;}}

        for (int i=1; i<=9; i++) {for (int j=1; j<=5; j++) {blockl2[n1].setTexture(l2); blockl2[n1].setPosition(i*85,j*25); n1++;}}

        for (int i=1; i<=9; i++) {for (int j=1; j<=7; j++) {blockl3[n2].setTexture(l3); blockl3[n2].setPosition(i*85,j*25); n2++;}}

        for (int i=1; i<=9; i++) {for (int j=1; j<=9; j++) {blockl4[n3].setTexture(l4); blockl4[n3].setPosition(i*85,j*25); n3++;}}

        for (int i=1; i<=9; i++) {for (int j=1; j<=11; j++) {blockl5[n4].setTexture(l5); blockl5[n4].setPosition(i*85,j*25); n4++;}}

///////////////////////////////////////////////////////////////////////////////////////////

    float dx=6, dy=5;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }
//////////////////////////Wypuszczenie piłki/////////////////////////////
        if(Mouse::isButtonPressed(Mouse::Left) && pilka==1 && wybor==1)
        {
          pilka=0;
        }
////////////////////////Kolizje Piłki////////////////////////////////////
        if (pilka==0)
        {
            if (level==1)
            {
                sBall.move(dx,0);
                for (int i=0; i<n; i++)
                    {
                        if (isCollide(sBall,block[i]))
                        {
                            Vector2f pk=block[i].getPosition();
                            pkX=pk.x;
                            pkY=pk.y;
                            block[i].setPosition(-100,0); if (dzwieki==1) {sUderzenieocegle.play(); wygranal1--;}
                            if (niezniszczalnosc==1) {dx=-dx;}
                            los=rand()%12+1;
                            if (los<=5 && czyjest==0) {ulepszenie=rand()%5+1; czyjest=1;}
                        }

                    }


                sBall.move(0,dy);
                for (int i=0; i<n; i++)
                    {
                        if (isCollide(sBall,block[i]))
                            {
                                Vector2f pk=block[i].getPosition();
                                pkX=pk.x;
                                pkY=pk.y;
                                block[i].setPosition(-100,0); if (dzwieki==1) {sUderzenieocegle.play();} wygranal1--;
                                if (niezniszczalnosc==1) {dy=-dy;}
                                los=rand()%12+1;
                                if (los<=5 && czyjest==0) {ulepszenie=rand()%5+1; czyjest=1;}
                            }
                    }
            }

            if (level==2)
            {
                sBall.move(dx,0);
                for (int i=0; i<n1; i++)
                    {
                        if (isCollide(sBall,blockl2[i]))
                        {
                            Vector2f pk=blockl2[i].getPosition();
                            pkX=pk.x;
                            pkY=pk.y;
                            blockl2[i].setPosition(-100,0); if (dzwieki==1) {sUderzenieocegle.play(); wygranal2--;}
                            if (niezniszczalnosc==1) {dx=-dx;}
                            los=rand()%12+1;
                            if (los<=5 && czyjest==0) {ulepszenie=rand()%5+1; czyjest=1;}
                        }

                    }


                sBall.move(0,dy);
                for (int i=0; i<n1; i++)
                    {
                        if (isCollide(sBall,blockl2[i]))
                            {
                                Vector2f pk=blockl2[i].getPosition();
                                pkX=pk.x;
                                pkY=pk.y;
                                blockl2[i].setPosition(-100,0); if (dzwieki==1) {sUderzenieocegle.play();} wygranal2--;
                                if (niezniszczalnosc==1) {dy=-dy;}
                                los=rand()%12+1;
                                if (los<=5 && czyjest==0) {ulepszenie=rand()%5+1; czyjest=1;}
                            }
                    }
            }

            if (level==3)
            {
                sBall.move(dx,0);
                for (int i=0; i<n2; i++)
                    {
                        if (isCollide(sBall,blockl3[i]))
                        {
                            Vector2f pk=blockl3[i].getPosition();
                            pkX=pk.x;
                            pkY=pk.y;
                            blockl3[i].setPosition(-100,0); if (dzwieki==1) {sUderzenieocegle.play(); wygranal3--;}
                            if (niezniszczalnosc==1) {dx=-dx;}
                            los=rand()%12+1;
                            if (los<=5 && czyjest==0) {ulepszenie=rand()%5+1; czyjest=1;}
                        }

                    }


                sBall.move(0,dy);
                for (int i=0; i<n2; i++)
                    {
                        if (isCollide(sBall,blockl3[i]))
                            {
                                Vector2f pk=blockl3[i].getPosition();
                                pkX=pk.x;
                                pkY=pk.y;
                                blockl3[i].setPosition(-100,0); if (dzwieki==1) {sUderzenieocegle.play();} wygranal3--;
                                if (niezniszczalnosc==1) {dy=-dy;}
                                los=rand()%12+1;
                                if (los<=5 && czyjest==0) {ulepszenie=rand()%5+1; czyjest=1;}
                            }
                    }
            }

            if (level==4)
            {
                sBall.move(dx,0);
                for (int i=0; i<n3; i++)
                    {
                        if (isCollide(sBall,blockl4[i]))
                        {
                            Vector2f pk=blockl4[i].getPosition();
                            pkX=pk.x;
                            pkY=pk.y;
                            blockl4[i].setPosition(-100,0); if (dzwieki==1) {sUderzenieocegle.play(); wygranal4--;}
                            if (niezniszczalnosc==1) {dx=-dx;}
                            los=rand()%12+1;
                            if (los<=5 && czyjest==0) {ulepszenie=rand()%5+1; czyjest=1;}
                        }

                    }


                sBall.move(0,dy);
                for (int i=0; i<n3; i++)
                    {
                        if (isCollide(sBall,blockl4[i]))
                            {
                                Vector2f pk=blockl4[i].getPosition();
                                pkX=pk.x;
                                pkY=pk.y;
                                blockl4[i].setPosition(-100,0); if (dzwieki==1) {sUderzenieocegle.play();} wygranal4--;
                                if (niezniszczalnosc==1) {dy=-dy;}
                                los=rand()%12+1;
                                if (los<=5 && czyjest==0) {ulepszenie=rand()%5+1; czyjest=1;}
                            }
                    }
            }

            if (level==5)
            {
                sBall.move(dx,0);
                for (int i=0; i<n4; i++)
                    {
                        if (isCollide(sBall,blockl5[i]))
                        {
                            Vector2f pk=blockl5[i].getPosition();
                            pkX=pk.x;
                            pkY=pk.y;
                            blockl5[i].setPosition(-100,0); if (dzwieki==1) {sUderzenieocegle.play(); wygranal5--;}
                            if (niezniszczalnosc==1) {dx=-dx;}
                            los=rand()%12+1;
                            if (los<=5 && czyjest==0) {ulepszenie=rand()%5+1; czyjest=1;}
                        }

                    }


                sBall.move(0,dy);
                for (int i=0; i<n4; i++)
                    {
                        if (isCollide(sBall,blockl5[i]))
                            {
                                Vector2f pk=blockl5[i].getPosition();
                                pkX=pk.x;
                                pkY=pk.y;
                                blockl5[i].setPosition(-100,0); if (dzwieki==1) {sUderzenieocegle.play();} wygranal5--;
                                if (niezniszczalnosc==1) {dy=-dy;}
                                los=rand()%12+1;
                                if (los<=5 && czyjest==0) {ulepszenie=rand()%5+1; czyjest=1;}
                            }
                    }
            }



        if (isCollide(sPaddle,sBall)) { if (dzwieki==1) {sUderzenieopaletke.play();} dy=-(rand()%5+2);};
        }


        Vector2f b= sBall.getPosition();
        if (b.x<0 || b.x>960) {if (dzwieki==1) {sUderzenieosciane.play();} dx=-dx;};
        if (b.y<0 || b.y>540) {if (dzwieki==1) {sUderzenieosciane.play();} dy=-dy;};

//////////////////////Ruch Paletki///////////////////////////
        Vector2f p= sPaddle.getPosition();

        if(stop==0 && wybor==1)
        {
            if (Keyboard::isKeyPressed(Keyboard::Right) && p.x >= 795 && zmianapaletki==2) sPaddle.move(0,0);
                else if (Keyboard::isKeyPressed(Keyboard::Right) && p.x >= 875 && zmianapaletki==1) sPaddle.move(0,0);
                    else if (Keyboard::isKeyPressed(Keyboard::Right) && p.x >= 715 && zmianapaletki==3) sPaddle.move(0,0);
                else if (Keyboard::isKeyPressed(Keyboard::Right) && pilka==1) {sPaddle.move(6,0); sBall.move(6,0);}
                    else if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6,0);

            if (Keyboard::isKeyPressed(Keyboard::Left) && p.x <= 7) sPaddle.move(0,0);
                else if (Keyboard::isKeyPressed(Keyboard::Left) && pilka==1) {sPaddle.move(-6,0); sBall.move(-6,0);}
                    else if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6,0);
        }
///////////////MENU PO PRZEGRANEJ//////////////////
        if (wybor2==1)
        {
            wygranal1=36;
            wygranal2=45;
            wygranal3=63;
            wygranal4=81;
            wygranal5=99;
            ilepozycji=0;
            zmianapaletki=2;
            zmianapilki=2;
            sBall.setTexture(t3);
            sPaddle.setTexture(t4);
            czyjest=0;
            sBall.setScale(1,1);
            sPaddle.setScale(1,1);
            czas=0;
            niezniszczalnosc=1;
            wybor2=0;
            zycia=3;
            startrys=0;
            razy=0;
            wybor=0;
            respienie=0;
                if (backmenu==1)
                {
                    dx=kordyX1;
                    dy=kordyY1;
                    backmenu=0;
                    pilka=1;
                    Vector2f padd= sPaddle.getPosition();
                    padd.x=padd.x+70;
                    sBall.setPosition(padd.x,484);
                }
             n=0,n1=0,n2=0,n3=0,n4=0;
                for (int i=1; i<=9; i++){for (int j=1; j<=4; j++) {block[n].setTexture(l1); block[n].setPosition(i*85,j*25); n++;}}

                    for (int i=1; i<=9; i++) {for (int j=1; j<=5; j++) {blockl2[n1].setTexture(l2); blockl2[n1].setPosition(i*85,j*25); n1++;}}

                for (int i=1; i<=9; i++) {for (int j=1; j<=7; j++) {blockl3[n2].setTexture(l3); blockl3[n2].setPosition(i*85,j*25); n2++;}}

                    for (int i=1; i<=9; i++) {for (int j=1; j<=9; j++) {blockl4[n3].setTexture(l4); blockl4[n3].setPosition(i*85,j*25); n3++;}}

                for (int i=1; i<=9; i++) {for (int j=1; j<=11; j++) {blockl5[n4].setTexture(l5); blockl5[n4].setPosition(i*85,j*25); n4++;}}
        }
        else if (wybor2==2)
        {
          app.clear();
          app.draw(sLose);
          meni.stop();
            if (razy==0 && dzwieki==1) {sPrzegrana.play(); razy=1;}
          //////////CZERWONE MENU I RESTART/////////////
           if ( Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 310 && Mouse::getPosition(app).y >= 330
          && Mouse::getPosition(app).x <= 410 && Mouse::getPosition(app).y <= 380) wybor2=1;

           else if (Mouse::getPosition(app).x >= 310 && Mouse::getPosition(app).y >= 330
          && Mouse::getPosition(app).x <= 410 && Mouse::getPosition(app).y <= 380) sLose.setTexture(losemenu);

           else if ( Mouse::isButtonPressed(Mouse::Left) &&  Mouse::getPosition(app).x >= 475 && Mouse::getPosition(app).y >= 330
          && Mouse::getPosition(app).x <= 670 && Mouse::getPosition(app).y <= 380) {wybor2=3;}

          else if (Mouse::getPosition(app).x >= 475 && Mouse::getPosition(app).y >= 330
          && Mouse::getPosition(app).x <= 670 && Mouse::getPosition(app).y <= 380) sLose.setTexture(loserestart);

          else sLose.setTexture(lose);
          /////////////////////////////////////
        }
          else if (wybor2==6)
        {
          app.clear();
          app.draw(sWin);
          zycia=3;
          sBall.setPosition(480,484);
          meni.stop();
          if (razy==0 && dzwieki==1) {sWygrana.play(); razy=1;}
          //////////CZERWONE MENU I RESTART/////////////
           if ( Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 315 && Mouse::getPosition(app).y >= 310
          && Mouse::getPosition(app).x <= 410 && Mouse::getPosition(app).y <= 340) wybor2=1;

           else if (Mouse::getPosition(app).x >= 315 && Mouse::getPosition(app).y >= 310
          && Mouse::getPosition(app).x <= 410 && Mouse::getPosition(app).y <= 340) sWin.setTexture(winmenu);

           else if ( Mouse::isButtonPressed(Mouse::Left) &&  Mouse::getPosition(app).x >= 510 && Mouse::getPosition(app).y >= 310
          && Mouse::getPosition(app).x <= 605 && Mouse::getPosition(app).y <= 340) {wybor2=3; nextlvl=1;}

          else if (Mouse::getPosition(app).x >= 510 && Mouse::getPosition(app).y >= 310
          && Mouse::getPosition(app).x <= 605 && Mouse::getPosition(app).y <= 340) sWin.setTexture(winnext);

          else sWin.setTexture(win);
          /////////////////////////////////////
        }
         else if (wybor2==3)
        {
            if(nextlvl==1)
            {
              level=level+1;
              nextlvl=0;
            }
            wygranal1=36;
            wygranal2=45;
            wygranal3=63;
            wygranal4=81;
            wygranal5=99;
            ilepozycji=0;
            zmianapaletki=2;
            zmianapilki=2;
            czyjest=0;
            sBall.setScale(1,1);
            sPaddle.setScale(1,1);
            sBall.setTexture(t3);
            sPaddle.setTexture(t4);
            czas=0;
            niezniszczalnosc=1;
            wybor2=4;
            zycia=3;
            startrys=0;
            razy=0;
            wybor=1;
            respienie=0;
             n=0,n1=0,n2=0,n3=0,n4=0;
                for (int i=1; i<=9; i++){for (int j=1; j<=4; j++) {block[n].setTexture(l1); block[n].setPosition(i*85,j*25); n++;}}

                    for (int i=1; i<=9; i++) {for (int j=1; j<=5; j++) {blockl2[n1].setTexture(l2); blockl2[n1].setPosition(i*85,j*25); n1++;}}

                for (int i=1; i<=9; i++) {for (int j=1; j<=7; j++) {blockl3[n2].setTexture(l3); blockl3[n2].setPosition(i*85,j*25); n2++;}}

                    for (int i=1; i<=9; i++) {for (int j=1; j<=9; j++) {blockl4[n3].setTexture(l4); blockl4[n3].setPosition(i*85,j*25); n3++;}}

                for (int i=1; i<=9; i++) {for (int j=1; j<=11; j++) {blockl5[n4].setTexture(l5); blockl5[n4].setPosition(i*85,j*25); n4++;}}
        }
        else if (wybor2==5)
        {
            app.clear();
            wybor=2;
            sMenuback.setPosition(900,7);
            app.draw(sLoad);
            app.draw(sMenuback);

            if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 900 && Mouse::getPosition(app).y >= 7
        && Mouse::getPosition(app).x <= 960 && Mouse::getPosition(app).y <= 57) {wybor2=1;}

            if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 140 && Mouse::getPosition(app).y >= 132
        && Mouse::getPosition(app).x <= 245 && Mouse::getPosition(app).y <= 236) {level=1; wybor=1; wybor2=4; }

           else if(Mouse::getPosition(app).x >= 140 && Mouse::getPosition(app).y >= 132
        && Mouse::getPosition(app).x <= 245 && Mouse::getPosition(app).y <= 236) sLoad.setTexture(loadl1);

          else if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 289 && Mouse::getPosition(app).y >= 132
        && Mouse::getPosition(app).x <= 394 && Mouse::getPosition(app).y <= 236) {level=2; wybor=1; wybor2=4; }

          else if(Mouse::getPosition(app).x >= 289 && Mouse::getPosition(app).y >= 132
        && Mouse::getPosition(app).x <= 394 && Mouse::getPosition(app).y <= 236) sLoad.setTexture(loadl2);

          else if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 438 && Mouse::getPosition(app).y >= 132
        && Mouse::getPosition(app).x <= 544 && Mouse::getPosition(app).y <= 236) {level=3; wybor=1; wybor2=4; }

          else if(Mouse::getPosition(app).x >= 438 && Mouse::getPosition(app).y >= 132
        && Mouse::getPosition(app).x <= 544 && Mouse::getPosition(app).y <= 236) sLoad.setTexture(loadl3);

          else if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 587 && Mouse::getPosition(app).y >= 132
        && Mouse::getPosition(app).x <= 693 && Mouse::getPosition(app).y <= 236) {level=4; wybor=1; wybor2=4; }

          else if(Mouse::getPosition(app).x >= 587 && Mouse::getPosition(app).y >= 132
        && Mouse::getPosition(app).x <= 693 && Mouse::getPosition(app).y <= 236) sLoad.setTexture(loadl4);

          else if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 736 && Mouse::getPosition(app).y >= 132
        && Mouse::getPosition(app).x <= 841 && Mouse::getPosition(app).y <= 236) {level=5; wybor=1; wybor2=4; }

          else if(Mouse::getPosition(app).x >= 736 && Mouse::getPosition(app).y >= 132
        && Mouse::getPosition(app).x <= 841 && Mouse::getPosition(app).y <= 236) sLoad.setTexture(loadl5);

        else sLoad.setTexture(load);

        }
        else if (wybor2==7)
        {
            app.clear();
            wybor=2;
            sMenuback.setPosition(900,7);
            app.draw(sSett);
            app.draw(sMenuback);
            app.draw(sStrzalki);
            app.draw(sStrzalki2);

            stringstream sPmv,sPsv;
             sPmv<<pmv; sPsv<<psv;
            string pPmv,pPsv;

            sPmv>>pPmv;

            sPsv>>pPsv;

            procentym.setFont(procenty); procentym.setString(pm); procentym.setCharacterSize(50); procentym.setColor(Color::White);
            procentymv.setFont(procenty); procentymv.setString(pPmv); procentymv.setCharacterSize(50); procentymv.setFillColor(Color::White);
            procentys.setFont(procenty); procentys.setString(ps); procentys.setCharacterSize(50);   procentys.setFillColor(Color::White);
            procentysv.setFont(procenty); procentysv.setString(pPsv); procentysv.setCharacterSize(50); procentysv.setFillColor(Color::White);

            procentym.setPosition(600,125); procentymv.setPosition(600,190); procentys.setPosition(600,255); procentysv.setPosition(600,320);
            sStrzalki.setPosition(660,216); sStrzalki2.setPosition(660,346);


            if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 900 && Mouse::getPosition(app).y >= 7
                && Mouse::getPosition(app).x <= 960 && Mouse::getPosition(app).y <= 57) {wybor2=1;}

            if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 220 && Mouse::getPosition(app).y >= 149
                && Mouse::getPosition(app).x <= 640 && Mouse::getPosition(app).y <= 176)

                {
                  if (pm=="ON")
                  {
                    meni.pause();
                    pm="OFF";
                    Sleep(100);
                  }
                  else if (pm=="OFF")
                  {
                      meni.play();
                      pm="ON";
                      Sleep(100);
                  }
                }

                else if(Mouse::getPosition(app).x >= 220 && Mouse::getPosition(app).y >= 149
                && Mouse::getPosition(app).x <= 640 && Mouse::getPosition(app).y <= 176) {sSett.setTexture(settm); procentym.setFillColor(Color::Red);}

            else if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 220 && Mouse::getPosition(app).y >= 213
                && Mouse::getPosition(app).x <= 660 && Mouse::getPosition(app).y <= 240) {;}

                else if(Mouse::getPosition(app).x >= 220 && Mouse::getPosition(app).y >= 213
                && Mouse::getPosition(app).x <= 685 && Mouse::getPosition(app).y <= 240)

                {
                    sSett.setTexture(settmv);
                    procentymv.setFillColor(Color::Red);

                    if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 660 && Mouse::getPosition(app).y >= 213
                    && Mouse::getPosition(app).x <= 685 && Mouse::getPosition(app).y <= 226.5)
                    {
                      pmv=pmv+10;
                      if (pmv>=100)
                      {
                        pmv=100;
                      }
                      meni.setVolume(pmv);
                      Sleep(100);
                    }

                        else if(Mouse::getPosition(app).x >= 660 && Mouse::getPosition(app).y >= 213
                        && Mouse::getPosition(app).x <= 685 && Mouse::getPosition(app).y <= 226.5)
                        {
                            sStrzalki.setTexture(strzalkiwgore);
                        }

                    else if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 660 && Mouse::getPosition(app).y >= 226.5
                    && Mouse::getPosition(app).x <= 685 && Mouse::getPosition(app).y <= 240)
                    {
                      pmv=pmv-10;
                      if(pmv<=0)
                      {
                          pmv=0;
                      }
                      meni.setVolume(pmv);
                      Sleep(100);
                    }

                        else if(Mouse::getPosition(app).x >= 660 && Mouse::getPosition(app).y >= 226.5
                    && Mouse::getPosition(app).x <= 685 && Mouse::getPosition(app).y <= 240)
                    {
                      sStrzalki.setTexture(strzalkiwdol);
                    }
                    else {sStrzalki.setTexture(strzalki); sStrzalki.setTexture(strzalki);}

                }

            else if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 220 && Mouse::getPosition(app).y >= 277
                && Mouse::getPosition(app).x <= 640 && Mouse::getPosition(app).y <= 304)

                {
                  if (ps=="ON")
                  {
                    dzwieki=0;
                    ps="OFF";
                    Sleep(100);
                  }
                  else if (ps=="OFF")
                  {
                      dzwieki=1;
                      ps="ON";
                      Sleep(100);
                  }
                }

                else if(Mouse::getPosition(app).x >= 220 && Mouse::getPosition(app).y >= 277
                && Mouse::getPosition(app).x <= 640 && Mouse::getPosition(app).y <= 304) {sSett.setTexture(setts); procentys.setFillColor(Color::Red);}

            else if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 220 && Mouse::getPosition(app).y >= 341
                && Mouse::getPosition(app).x <= 660 && Mouse::getPosition(app).y <= 368) {;}

                else if(Mouse::getPosition(app).x >= 220 && Mouse::getPosition(app).y >= 341
                && Mouse::getPosition(app).x <= 685 && Mouse::getPosition(app).y <= 368)
                {
                    sSett.setTexture(settsv);
                    procentysv.setFillColor(Color::Red);

                    if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 660 && Mouse::getPosition(app).y >= 341
                    && Mouse::getPosition(app).x <= 685 && Mouse::getPosition(app).y <= 354.5)
                    {
                      psv=psv+10;
                      if (psv>=100)
                      {
                        psv=100;
                      }

                        sPrzegrana.setVolume(psv);
                        sWygrana.setVolume(psv);
                        sStrzaly.setVolume(psv);
                        sUderzenieocegle.setVolume(psv);
                        sUderzenieopaletke.setVolume(psv);
                        sUderzenieosciane.setVolume(psv);
                        sDead.setVolume(psv);

                      Sleep(100);
                    }

                        else if(Mouse::getPosition(app).x >= 660 && Mouse::getPosition(app).y >= 341
                        && Mouse::getPosition(app).x <= 685 && Mouse::getPosition(app).y <= 354.5)
                        {
                            sStrzalki2.setTexture(strzalkiwgore);
                        }

                    else if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 660 && Mouse::getPosition(app).y >= 354.5
                    && Mouse::getPosition(app).x <= 685 && Mouse::getPosition(app).y <= 368)
                    {
                      psv=psv-10;
                      if(psv<=0)
                      {
                          psv=0;
                      }

                        sPrzegrana.setVolume(psv);
                        sWygrana.setVolume(psv);
                        sStrzaly.setVolume(psv);
                        sUderzenieocegle.setVolume(psv);
                        sUderzenieopaletke.setVolume(psv);
                        sUderzenieosciane.setVolume(psv);
                        sDead.setVolume(psv);

                      Sleep(100);
                    }

                        else if(Mouse::getPosition(app).x >= 660 && Mouse::getPosition(app).y >= 354.5
                    && Mouse::getPosition(app).x <= 685 && Mouse::getPosition(app).y <= 368)
                    {
                      sStrzalki2.setTexture(strzalkiwdol);
                    }
                    else {sStrzalki2.setTexture(strzalki); sStrzalki2.setTexture(strzalki);}
                }

                else
                {
                    sSett.setTexture(sett);
                    procentym.setFillColor(Color::White);
                    procentymv.setFillColor(Color::White);
                    procentys.setFillColor(Color::White);
                    procentysv.setFillColor(Color::White);
                    sStrzalki.setTexture(strzalki);
                    sStrzalki2.setTexture(strzalki);
                }

                app.draw(procentym); app.draw(procentymv); app.draw(procentys); app.draw(procentysv); app.draw(strzalawgore); app.draw(strzalkawdol);

        }
        else if (wybor2==0) {wybor==0; app.draw(sMenu);}
//////////////////////////////////////////////////
if (wybor==0)
{
////////////////START/////////////////////////////

        if( Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 330 && Mouse::getPosition(app).y >= 190
       && Mouse::getPosition(app).x <= 590 && Mouse::getPosition(app).y <= 235) {wybor=1;}

        else if(Mouse::getPosition(app).x >= 330 && Mouse::getPosition(app).y >= 190
       && Mouse::getPosition(app).x <= 590 && Mouse::getPosition(app).y <= 235) sMenu.setTexture(menustart);


/////////////////LOAD/////////////////////////////

        else if( Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 310 && Mouse::getPosition(app).y >= 250
       && Mouse::getPosition(app).x <= 575 && Mouse::getPosition(app).y <= 300) wybor2=5;

        else if(Mouse::getPosition(app).x >= 310 && Mouse::getPosition(app).y >= 250
       && Mouse::getPosition(app).x <= 575 && Mouse::getPosition(app).y <= 300) sMenu.setTexture(menuload);


////////////////SETTINGS//////////////////////////

        else if( Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 310 && Mouse::getPosition(app).y >= 320
       && Mouse::getPosition(app).x <= 550 && Mouse::getPosition(app).y <= 380) wybor2=7;

        else if(Mouse::getPosition(app).x >= 310 && Mouse::getPosition(app).y >= 320
       && Mouse::getPosition(app).x <= 550 && Mouse::getPosition(app).y <= 380) sMenu.setTexture(menusett);


////////////////QUITGAME/////////////////////////

        else if ( Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 310 && Mouse::getPosition(app).y >= 400
       && Mouse::getPosition(app).x <= 550 && Mouse::getPosition(app).y <= 450) app.close();

        else if(Mouse::getPosition(app).x >= 310 && Mouse::getPosition(app).y >= 400
       && Mouse::getPosition(app).x <= 550 && Mouse::getPosition(app).y <= 450) sMenu.setTexture(menuquit);

////////////////////////////////////////////////
       else sMenu.setTexture(menu);
}
////////////////Zatrzymywanie Gry///////////////////////////////
      if( Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 900 && Mouse::getPosition(app).y >= -10
       && Mouse::getPosition(app).x <= 960 && Mouse::getPosition(app).y <= 60 && wybor==1)
       {
         if (stop==1)
         {
         sPause.setTexture(pause);
         dx=kordyX;
         dy=kordyY;
         Sleep(100);
         stop=0;
         }
         else
         {
         sPause.setTexture(resume);
         kordyX=dx;
         kordyY=dy;
         dx=0;
         dy=0;
         Sleep(100);
         stop=1;
         }
       }
//////////////////////WRACANIE DO MENU//////////////////////////////////////////////////////////////
            if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 850 && Mouse::getPosition(app).y >= 7
        && Mouse::getPosition(app).x <= 900 && Mouse::getPosition(app).y <= 57 && wybor==1)
         {
         kordyX1=dx;
         kordyY1=dy;
         dx=0;
         dy=0;
         wybor2=1;
         backmenu=1;
         }
/////////////////////Wygrana/////////////////////////////////////////////////////////////////////
         if (wygranal1==0) {wygranal1=36; wybor=2; wybor2=6; sBall.setPosition(480,484); }
         if (wygranal2==0) {wygranal2=45; wybor=2; wybor2=6; sBall.setPosition(480,484); }
         if (wygranal3==0) {wygranal3=63; wybor=2; wybor2=6; sBall.setPosition(480,484); }
         if (wygranal4==0) {wygranal4=81; wybor=2; wybor2=6; sBall.setPosition(480,484); }
         if (wygranal5==0) {wygranal5=99; wybor=2; wybor2=6; sBall.setPosition(480,484); }

/////////////////////Przegrana///////////////////////////////////////////////////////////////////
        if (b.y >=520 && b.y <=540)
        {
            sDead.play();
            if(zycia==0)
            {
             wybor=2;
             wybor2=2;
            }
           zycia=zycia-1;
            Vector2f p= sPaddle.getPosition();

            if (zmianapaletki==1) p.x=p.x+30;
            else if (zmianapaletki==2) p.x=p.x+70;
            else if (zmianapaletki==3) p.x=p.x+110;

            if (zmianapilki==1) sBall.setPosition(p.x,492);
            else if (zmianapilki==2) sBall.setPosition(p.x,484);
            else if (zmianapilki==3) sBall.setPosition(p.x,476);


           pilka=1;
       }
///////////////////////////////////
int jakieulepszenie;
    if (ulepszenie==1)
    {
        czyjest=1;
        sUlepszenie.setTexture(ulepszeniepaletki);

        if (ilepozycji==0)
        {
            sUlepszenie.setPosition(pkX,pkY);
            ilepozycji=1;
            randomoweulepszenie=1;
        }

        if (stop==0) sUlepszenie.move(0,3);
        Vector2f kordyU = sUlepszenie.getPosition();

        if (kordyU.y >= 525)
        {
            ilepozycji=0;
            randomoweulepszenie=0;
            ulepszenie=0;
            czyjest=0;
        }

        if (isCollide(sPaddle,sUlepszenie))
        {
            start = clock();
            sPaddle.setScale(1.5,1);
            zmianapaletki=3;
            jakieulepszenie=1;
            czyjest=0;
            randomoweulepszenie=0;
        }
    }
    else if (ulepszenie==2)
    {
        czyjest=1;
        sUlepszenie.setTexture(pogorszeniepaletki);

        if (ilepozycji==0)
        {
            sUlepszenie.setPosition(pkX,pkY);
            ilepozycji=1;
            randomoweulepszenie=1;
        }

        if (stop==0) sUlepszenie.move(0,3);
        Vector2f kordyU = sUlepszenie.getPosition();

        if (kordyU.y >= 525)
        {
            ilepozycji=0;
            randomoweulepszenie=0;
            ulepszenie=0;
            czyjest=0;
        }

        if (isCollide(sPaddle,sUlepszenie))
        {
            start = clock();
            sPaddle.setScale(0.5,1);
            zmianapaletki=1;
            jakieulepszenie=1;
            czyjest=0;
            randomoweulepszenie=0;
        }
    }
    else if  (ulepszenie==3)
    {
        czyjest=1;
        sUlepszenie.setTexture(ulepszeniepilki);

        if (ilepozycji==0)
        {
            sUlepszenie.setPosition(pkX,pkY);
            ilepozycji=1;
            randomoweulepszenie=1;
        }
        if (stop==0) sUlepszenie.move(0,3);
        Vector2f kordyU = sUlepszenie.getPosition();

        if (kordyU.y >= 525)
        {
            ilepozycji=0;
            randomoweulepszenie=0;
            ulepszenie=0;
            czyjest=0;
        }

        if (isCollide(sPaddle,sUlepszenie))
        {
            start = clock();
            sBall.setScale(1.5,1.5);
            jakieulepszenie=1;
            zmianapilki=3;
            czyjest=0;
            randomoweulepszenie=0;
        }
    }
    else if  (ulepszenie==4)
    {
        czyjest=1;
        sUlepszenie.setTexture(pogorszeniepilki);

        if (ilepozycji==0)
        {
            sUlepszenie.setPosition(pkX,pkY);
            ilepozycji=1;
            randomoweulepszenie=1;
        }

        if (stop==0) sUlepszenie.move(0,3);
        Vector2f kordyU = sUlepszenie.getPosition();

        if (kordyU.y >= 525)
        {
            ilepozycji=0;
            randomoweulepszenie=0;
            ulepszenie=0;
            czyjest=0;
        }

        if (isCollide(sPaddle,sUlepszenie))
        {
            start = clock();
            sBall.setScale(0.5,0.5);
            jakieulepszenie=1;
            zmianapilki=1;
            czyjest=0;
            randomoweulepszenie=0;
        }
    }
    else if  (ulepszenie==5)
    {
        czyjest=1;
        sUlepszenie.setTexture(niezniszczalnoscpilki);

        if (ilepozycji==0)
        {
            sUlepszenie.setPosition(pkX,pkY);
            ilepozycji=1;
            randomoweulepszenie=1;
        }

        if (stop==0) sUlepszenie.move(0,3);
        Vector2f kordyU = sUlepszenie.getPosition();

        if (kordyU.y >= 525)
        {
            ilepozycji=0;
            randomoweulepszenie=0;
            ulepszenie=0;
            czyjest=0;
        }

        if (isCollide(sPaddle,sUlepszenie))
        {
            start = clock();
            sBall.setTexture(niezniszczalnapilka);
            niezniszczalnosc=0;
            jakieulepszenie=2;
            zmianapilki=2;
            czyjest=0;
            randomoweulepszenie=0;
        }
    }
    else
    {
        stopc= clock();
        czas = (double)(stopc - start)/ CLOCKS_PER_SEC;
        if (czas>=4 && jakieulepszenie==1) {sPaddle.setScale(1,1); zmianapaletki=2; sBall.setScale(1,1); czas=0; niezniszczalnosc=1; sBall.setTexture(t3); ilepozycji=0; jakieulepszenie=0; zmianapilki=2; czyjest=0;}
        if (czas>=2 && jakieulepszenie==2) {sPaddle.setScale(1,1); zmianapaletki=2; sBall.setScale(1,1); czas=0; niezniszczalnosc=1; sBall.setTexture(t3); ilepozycji=0; jakieulepszenie=0; zmianapilki=2; czyjest=0;}
    }

////////////////////////////////////////////////////////////////////
        if (wybor==1)
        {
/////////////////////1 LEVEL///////////////////////////////////////
          if (level==1)
          {
            app.clear();
            app.draw(sBackground);
            app.draw(sBall);
            app.draw(sPaddle);
            if (zycia>=1) app.draw(sZycie1);
            if (zycia>=2) {app.draw(sZycie2); sZycie2.setPosition(25,0);}
            if (zycia==3) {app.draw(sZycie3); sZycie3.setPosition(50,0);}
            app.draw(sPause);
            sPause.setPosition(900,-10);
            app.draw(sMenuback);
            sMenuback.setPosition(850,7);
            if (randomoweulepszenie==1) app.draw(sUlepszenie);

            for (int i=0; i<n; i++){app.draw(block[i]);}

            if (startrys==0 && wybor==1) {Sleep(100); startrys=1; }
            respienie=1;
          }
/////////////////////2 LEVEL///////////////////////////////////////
          else if (level==2)
          {
            app.clear();
            app.draw(sBackground);
            app.draw(sBall);
            app.draw(sPaddle);
            if (zycia>=1) app.draw(sZycie1);
            if (zycia>=2) {app.draw(sZycie2); sZycie2.setPosition(25,0);}
            if (zycia==3) {app.draw(sZycie3); sZycie3.setPosition(50,0);}
            app.draw(sPause);
            sPause.setPosition(900,-10);
            app.draw(sMenuback);
            sMenuback.setPosition(850,7);
            if (randomoweulepszenie==1) app.draw(sUlepszenie);

            for (int i=0; i<n1; i++){app.draw(blockl2[i]);}

            if (startrys==0 && wybor==1) {Sleep(100); startrys=1; }
          }
/////////////////////3 LEVEL///////////////////////////////////////
          else if (level==3)
          {
            app.clear();
            app.draw(sBackground);
            app.draw(sBall);
            app.draw(sPaddle);
            if (zycia>=1) app.draw(sZycie1);
            if (zycia>=2) {app.draw(sZycie2); sZycie2.setPosition(25,0);}
            if (zycia==3) {app.draw(sZycie3); sZycie3.setPosition(50,0);}
            app.draw(sPause);
            sPause.setPosition(900,-10);
            app.draw(sMenuback);
            sMenuback.setPosition(850,7);
            if (randomoweulepszenie==1) app.draw(sUlepszenie);

            for (int i=0; i<n2; i++){app.draw(blockl3[i]);}

            if (startrys==0 && wybor==1) {Sleep(100); startrys=1; }
          }
/////////////////////4 LEVEL///////////////////////////////////////
          else if (level==4)
          {
            app.clear();
            app.draw(sBackground);
            app.draw(sBall);
            app.draw(sPaddle);
            if (zycia>=1) app.draw(sZycie1);
            if (zycia>=2) {app.draw(sZycie2); sZycie2.setPosition(25,0);}
            if (zycia==3) {app.draw(sZycie3); sZycie3.setPosition(50,0);}
            app.draw(sPause);
            sPause.setPosition(900,-10);
            app.draw(sMenuback);
            sMenuback.setPosition(850,7);
            if (randomoweulepszenie==1) app.draw(sUlepszenie);

            for (int i=0; i<n3; i++){app.draw(blockl4[i]);}

            if (startrys==0 && wybor==1) {Sleep(100); startrys=1; }
          }
/////////////////////5 LEVEL///////////////////////////////////////
          else if (level==5)
          {
            app.clear();
            app.draw(sBackground);
            app.draw(sBall);
            app.draw(sPaddle);
            if (zycia>=1) app.draw(sZycie1);
            if (zycia>=2) {app.draw(sZycie2); sZycie2.setPosition(25,0);}
            if (zycia==3) {app.draw(sZycie3); sZycie3.setPosition(50,0);}
            app.draw(sPause);
            sPause.setPosition(900,-10);
            app.draw(sMenuback);
            sMenuback.setPosition(850,7);
            if (randomoweulepszenie==1) app.draw(sUlepszenie);

            for (int i=0; i<n4; i++){app.draw(blockl5[i]);}

            if (startrys==0 && wybor==1) {Sleep(100); startrys=1; }
          }
///////////////////////////////////////////////////////////////////
       }
///////////////////////////////////////////////////////////////////
        app.display();
    }

    return 0;
}

