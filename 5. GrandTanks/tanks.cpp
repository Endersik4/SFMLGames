#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <windows.h>
#include <sstream>
#include <fstream>
using namespace sf;
using namespace std;

double czas_migniecia_prawego_karabinu=0,czas_migniecia_lewego_karabinu=0,czas_migniecia_lewego_ramienia=0,czas_migniecia_prawego_ramienia=0,czas_migniecia_oka=0;

int ruch_lufy,ilosc_ammo=0,ilosc_naraz_strzalow=1,pozycja_przed_strzalem_x,pozycja_przed_strzalem_y,level=1;
int Zycie_Mecha_1,Zycie_Mecha_2,Zycie_Mecha_3,Zycie_Mecha_4,Zycie_Mecha_5,ilosc_mechow=5,zycie_czolgu=3,jaki_mech=0;
int glosnosc_muzyki=50,glosnosc_dzwiekow=40,pozycja_x=1370;

bool respienie_kuli=false,ruch_kuli=false,poczatkowe_miejsce_kuli=true,pozycja_kuli_po_strzale=false,respienie_mechow=true;
bool strzal_kuli=false,respienie_czolgu=true,respienie_zycia=true,poczatkowa_pozycja_lufy=true,strzal_od_mecha=false,strzal_mecha=false;
bool ruch_ammo_mecha=false,menu_czy_restart,czy_muzyka=false,czy_zmiana_napisu=true,czy_strzal_mecha=false,muzyka_podczas_grania_czy=true;
bool rysowanie_strzalki_muzyki=false,rysowanie_strzalki_dzwiekow=false,rysowanie_wlaczonej_muzyki=false,rysowanie_wlaczonego_dzwieku=false;
bool restart_pozycji_kuli=false,restart_rotacji_lufy=false, restart_pozycji_kuli_strzal=false;
bool poczatkowa_pozycja_creditsow=true,ustawianie_amunicji=true,big_delete_save=false;

double ruch_x_kuli=0.25,ruch_y_kuli=0,ruch_y_kuli_po_strzale=0, rotacja_lufy=0,czas_bez_strzalu=0;

double rotacja_ammo_mecha_1=0,rotacja_ammo_mecha_1_po_strzale=0,rotacja_ammo_mecha_2=-30,rotacja_ammo_mecha_2_po_strzale=-30,
rotacja_ammo_mecha_3=-35,rotacja_ammo_mecha_3_po_strzale=-35, rotacja_ammo_mecha_4=0,rotacja_ammo_mecha_4_po_strzale=0,
rotacja_ammo_mecha_5=-25,rotacja_ammo_mecha_5_po_strzale=-25;

double pozycja_ammo_mecha_1_y=0,pozycja_ammo_mecha_1_y_po_strzale=0,pozycja_ammo_mecha_2_y=0.07,pozycja_ammo_mecha_2_y_po_strzale=0.07,
pozycja_ammo_mecha_3_y=0.07,pozycja_ammo_mecha_3_y_po_strzale=0.07,pozycja_ammo_mecha_4_y=0,pozycja_ammo_mecha_4_y_po_strzale=0,
pozycja_ammo_mecha_5_y=0.04,pozycja_ammo_mecha_5_y_po_strzale=0.04;
string ilosc_ammo_string,menu="menu",Wlaczona_Muzyka="ON",Wlaczony_Dzwiek="ON",sGlosnosc_muzyki,sGlosnosc_dzwiekow;

////////////////////////////////////BOSS/////////////////////////////////////////////////////
double ilosc_zycia_bossa=1;
int ilosc_zycia_prawego_karabinu=4,ilosc_zycia_lewego_karabinu=4,ilosc_zycia_lewe_ramie=4,ilosc_zycia_prawe_ramie=4,
ilosc_zycia_oko=4;
bool migniecie_prawego_karabinu=false,migniecie_lewego_karabinu=false,migniecie_prawego_ramienia=false,
migniecie_lewego_ramienia=false, migniecie_oka=false;
int jaki_otwor=0;
bool rysowanie_ammo_bossa=false;
////////////////////////////////////KONIEC BOSSA//////////////////////////////////////////////

bool isCollide(Sprite s1,Sprite s2)
{
  return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}


int main()
{
    srand(time(0));
    RenderWindow app(VideoMode(1920,1080),"GrandTanks!", Style::Fullscreen);
    ///////////////////////////////TEXTURY//////////////////////////////////////
    Texture lufa,czolg,kula,mech1,mech2,mech3,mech4,glowne_menu,glowne_menu_start,glowne_menu_levels,glowne_menu_settings,
    glowne_menu_quit,wygrana,wygrana_menu,wygrana_next,przegrana,przegrana_menu,przegrana_restart,tlo_w_grze,zycia_3_3,
    zycia_2_3,zycia_1_3,zycia_0_3,ammo_mecha,settings,settings_music,settings_musicvolume,settings_sounds,settings_soundsvolume,
    strzalki,strzalka_w_gore,strzalka_w_dol,change_level,change_level_1,change_level_2,change_level_3,change_level_4,change_level_5,change_level_6,
    opis_level_1,opis_level_2,opis_level_3,opis_level_4,opis_level_5,opis_level_6,boss,lewe_ramie_bossa,prawe_ramie_bossa,oko_bossa,
    prawy_karabin_bossa,lewy_karabin_bossa,zycie_bossa,ammo_bossa,tlo_credits,credits,delete_save,delete_save_big;
    lufa.loadFromFile("Images/lufa.png");
    czolg.loadFromFile("Images/czolg.png");
    kula.loadFromFile("Images/kula.png");
    mech1.loadFromFile("Images/enemy 1 (zwykly).png"); mech2.loadFromFile("images/enemy 2 (sredni).png"); mech3.loadFromFile("images/enemy 3 (ciezki).png"); mech4.loadFromFile("images/enemy 4 (najciezszy).png");
    glowne_menu.loadFromFile("images/tlo_w_menu.png"); glowne_menu_start.loadFromFile("images/tlo_w_menu_start.png"); glowne_menu_levels.loadFromFile("images/tlo_w_menu_levels.png"); glowne_menu_settings.loadFromFile("images/tlo_w_menu_settings.png"); glowne_menu_quit.loadFromFile("images/tlo_w_menu_quit.png");
    wygrana.loadFromFile("images/wygrana.png"); wygrana_menu.loadFromFile("images/wygrana_menu.png"); wygrana_next.loadFromFile("images/wygrana_next.png");
    przegrana.loadFromFile("images/przegrana.png"); przegrana_menu.loadFromFile("images/przegrana_menu.png"); przegrana_restart.loadFromFile("images/przegrana_restart.png");
    zycia_3_3.loadFromFile("images/zycia 3 na 3.png"); zycia_2_3.loadFromFile("images/zycia 2 na 3.png"); zycia_1_3.loadFromFile("images/zycia 1 na 3.png"); zycia_0_3.loadFromFile("images/zycia 0 na 3.png");
    tlo_w_grze.loadFromFile("images/tlo_w_grze.png");
    ammo_mecha.loadFromFile("images/ammo do mecha.png");
    settings.loadFromFile("images/settings.png"); settings_music.loadFromFile("images/settings_music.png"); settings_musicvolume.loadFromFile("images/settings_musicvolume.png"); settings_sounds.loadFromFile("images/settings_sounds.png"); settings_soundsvolume.loadFromFile("images/settings_soundsvolume.png");
    strzalki.loadFromFile("images/strzalki.png"); strzalka_w_dol.loadFromFile("images/strzalka_w_dol.png"); strzalka_w_gore.loadFromFile("images/strzalka_w_gore.png");
    change_level.loadFromFile("images/change_level.png"); change_level_1.loadFromFile("images/change_level_1.png"); change_level_2.loadFromFile("images/change_level_2.png"); change_level_3.loadFromFile("images/change_level_3.png"); change_level_4.loadFromFile("images/change_level_4.png"); change_level_5.loadFromFile("images/change_level_5.png"); change_level_6.loadFromFile("images/change_level_6.png");
    opis_level_1.loadFromFile("images/level 1 - opis.png"); opis_level_2.loadFromFile("images/level 2 - opis.png"); opis_level_3.loadFromFile("images/level 3 - opis.png"); opis_level_4.loadFromFile("images/level 4 - opis.png"); opis_level_5.loadFromFile("images/level 5 - opis.png"); opis_level_6.loadFromFile("images/level 6 - opis.png");
    boss.loadFromFile("Images/boss.png"); lewe_ramie_bossa.loadFromFile("Images/lewe ramie.png"); prawe_ramie_bossa.loadFromFile("Images/prawe ramie.png"); oko_bossa.loadFromFile("Images/oko.png");
    prawy_karabin_bossa.loadFromFile("Images/prawy karabin bossa.png"); lewy_karabin_bossa.loadFromFile("Images/lewy karabin bossa.png");
    zycie_bossa.loadFromFile("images/zycie bossa.png");
    ammo_bossa.loadFromFile("Images/ammo do bossa.png");
    tlo_credits.loadFromFile("images/tlo credits.png");
    credits.loadFromFile("Images/credits.png");
    delete_save.loadFromFile("Images/Delete_save.png"); delete_save_big.loadFromFile("Images/delete_save_big.png");
    ///////////////////////////////KONIEC TEXTUR//////////////////////////////////////
    ///////////////////////////////SPRITE////////////////////////////////////////////
    Sprite sLufa(lufa),sCzolg(czolg),sKula(kula),sAmmo(kula),sMech1,sMech2,sMech3,sMech4,sMech5,sAmmo_Mecha(ammo_mecha),
    sGra(tlo_w_grze),sZycia(zycia_3_3),sPrzegrana(przegrana),sWygrana(wygrana),sMenu(glowne_menu),sSettings(settings),sChange_level(change_level),
    sStrzalki(strzalki),sOpisLevelu,sBoss(boss),sLewyKarabin(lewy_karabin_bossa), sPrawyKarabin(prawy_karabin_bossa),sLeweRamie(lewe_ramie_bossa),
    sZycie_Bossa(zycie_bossa), sPraweRamie(prawe_ramie_bossa), sOko(oko_bossa),sTlo_credits(tlo_credits),sCredits(credits),sDelete(delete_save);
    ///////////////////////////////KONIEC SPRITEu//////////////////////////////////
    /////////////////////////////////TEXT//////////////////////////////////////////
    Font font;
    font.loadFromFile("Bauhaus 93 Regular.ttf");
    Text ammo;
    ///////////////////////////////KONIEC TEXTU//////////////////////////////////////
    ////////////////////////////////DZWIEKI/////////////////////////////////////////
    SoundBuffer bPrzegrana,bWygrana,bStrzal_Mecha,bStrzal_czolgu,bPrzeladowanie,bWybuch,bZmiana_Napisu;
    bPrzegrana.loadFromFile("sounds/przegrana.flac");
    bWygrana.loadFromFile("sounds/wygrana.flac");
    bStrzal_Mecha.loadFromFile("sounds/strzal mecha.flac");
    bStrzal_czolgu.loadFromFile("sounds/strzal czolgu.flac");
    bPrzeladowanie.loadFromFile("sounds/przeladowanie.flac");
    bWybuch.loadFromFile("sounds/wybuch.flac");
    bZmiana_Napisu.loadFromFile("sounds/zmiana.flac");

    Sound sPrzegrana_dzwiek,sWygrana_dzwiek,sStrzal_Mecha,sStrzal_czolgu,sPrzeladowanie,sWybuch,sZmiana_Napisu;
    sPrzegrana_dzwiek.setBuffer(bPrzegrana);
    sWygrana_dzwiek.setBuffer(bWygrana);
    sStrzal_Mecha.setBuffer(bStrzal_Mecha);
    sStrzal_czolgu.setBuffer(bStrzal_czolgu);
    sPrzeladowanie.setBuffer(bPrzeladowanie);
    sWybuch.setBuffer(bWybuch);
    sZmiana_Napisu.setBuffer(bZmiana_Napisu);

    ////////////////////KONIEC glosnosci dzwiekow////////////////////

    Music muzyka_z_menu,muzyka_podczas_grania,muzyka_bossa;
    muzyka_z_menu.openFromFile("sounds/muzyka z menu.flac");
    muzyka_z_menu.play();
    muzyka_z_menu.setVolume(glosnosc_muzyki);
    muzyka_z_menu.setLoop(true);
    muzyka_podczas_grania.openFromFile("sounds/dzwieki podczas grania.flac");
    muzyka_bossa.openFromFile("sounds/muzyka boss.flac");
    ////////////////////////////////KONIEC DZWIEKOW/////////////////////////////////
    ////////////////////////////////////TEXTY//////////////////////////////////////
    Text tGlosnosc_dzwiekow,tGlosnosc_muzyki,tWlaczona_Muzyka,tWlaczony_Dzwiek;

    /////////////////////////////////////KONIEC TEXTU/////////////////////////////

 while (app.isOpen())
 {
    Event e;
    while(app.pollEvent(e))
    {
        if (e.type == Event::Closed)
        app.close();
    }
///////////////////////Menu Gry////////////////////////////////////////////////////////
        if (menu=="menu")
        {
            if(Keyboard::isKeyPressed(Keyboard::Escape)) {app.close(); menu_czy_restart=false;}

            respienie_zycia=true;

                if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 790 && Mouse::getPosition(app).y >= 410
                                    && Mouse::getPosition(app).x <= 1130 && Mouse::getPosition(app).y <= 490) menu="start";

                  else if (Mouse::getPosition(app).x >= 790 && Mouse::getPosition(app).y >= 410 &&
                            Mouse::getPosition(app).x <= 1130 && Mouse::getPosition(app).y <= 490)
                            {
                                sMenu.setTexture(glowne_menu_start);
                                if (czy_zmiana_napisu==true)
                                    {
                                        sZmiana_Napisu.play();
                                        czy_zmiana_napisu=false;
                                    }
                                    czy_muzyka=true;
                            }

                else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 770 && Mouse::getPosition(app).y >= 530
                                    && Mouse::getPosition(app).x <= 1090 && Mouse::getPosition(app).y <= 610) menu="levels";

                  else if (Mouse::getPosition(app).x >= 770 && Mouse::getPosition(app).y >= 530 &&
                            Mouse::getPosition(app).x <= 1090 && Mouse::getPosition(app).y <= 610)
                            {
                                sMenu.setTexture(glowne_menu_levels);
                                if (czy_zmiana_napisu==true)
                                    {
                                        sZmiana_Napisu.play();
                                        czy_zmiana_napisu=false;
                                    }
                                    czy_muzyka=true;
                            }


                else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 690 && Mouse::getPosition(app).y >= 650
                        && Mouse::getPosition(app).x <= 1175 && Mouse::getPosition(app).y <= 730) menu="settings";

                  else if (Mouse::getPosition(app).x >= 690 && Mouse::getPosition(app).y >= 650 &&
                          Mouse::getPosition(app).x <= 1175 && Mouse::getPosition(app).y <= 730)
                          {
                              sMenu.setTexture(glowne_menu_settings);
                              if (czy_zmiana_napisu==true)
                                    {
                                        sZmiana_Napisu.play();
                                        czy_zmiana_napisu=false;
                                    }
                                    czy_muzyka=true;
                          }


                else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 790 && Mouse::getPosition(app).y >= 770
                        && Mouse::getPosition(app).x <= 1065 && Mouse::getPosition(app).y <= 860) app.close();

                  else if (Mouse::getPosition(app).x >= 790 && Mouse::getPosition(app).y >= 770 &&
                           Mouse::getPosition(app).x <= 1065 && Mouse::getPosition(app).y <= 860)
                           {
                               sMenu.setTexture(glowne_menu_quit);
                               if (czy_zmiana_napisu==true)
                                    {
                                        sZmiana_Napisu.play();
                                        czy_zmiana_napisu=false;
                                    }
                                    czy_muzyka=true;
                           }

                    else  {
                            sMenu.setTexture(glowne_menu);
                            if(czy_muzyka==true)
                                {
                                    sZmiana_Napisu.stop();
                                    czy_muzyka=false;
                                    czy_zmiana_napisu=true;
                                }
                          }

          app.clear();
          app.draw(sMenu);
        }
////////////////////KONIEC MENU GRY///////////////////////////////////////////////////
/////////////////////Start Gry////////////////////////////////////////////////////////
        if(menu=="start")
        {
               if (level==6) sAmmo_Mecha.setTexture(ammo_bossa);
               else sAmmo_Mecha.setTexture(ammo_mecha);

               if (muzyka_podczas_grania_czy==true)
               {
                   muzyka_podczas_grania.setVolume(25);
                    muzyka_z_menu.play();
                    //muzyka_podczas_grania.play();
                    muzyka_podczas_grania.setLoop(true);
                    muzyka_podczas_grania_czy=false;
               }
              if (poczatkowa_pozycja_lufy==true) {sLufa.setPosition(160,870); poczatkowa_pozycja_lufy=false;}
              rotacja_lufy = sLufa.getRotation();
              if (restart_rotacji_lufy==true) {sLufa.setRotation(0); restart_rotacji_lufy=false;}

              if (poczatkowe_miejsce_kuli==true) {sKula.setPosition(280,880); poczatkowe_miejsce_kuli=false;}
              Vector2f pozycja_lufy = sLufa.getPosition();
              Vector2f pozycja_kuli = sKula.getPosition();

              if (restart_pozycji_kuli_strzal==true) {pozycja_przed_strzalem_x = 280; pozycja_przed_strzalem_y = 880; restart_pozycji_kuli_strzal=false;}
              if (restart_pozycji_kuli==true) {pozycja_kuli.y = 880; restart_pozycji_kuli=false;}

              if(Keyboard::isKeyPressed(Keyboard::Escape)) {menu_czy_restart=true; menu="restart"; Sleep(200); }

             /////////////////////Mechanika Czolgu/////////////////////
             sAmmo_Mecha.setScale(2,2);

              if (Keyboard::isKeyPressed(Keyboard::W) && rotacja_lufy==290 ) ;
                else if (Keyboard::isKeyPressed(Keyboard::S) && rotacja_lufy == 0) ;
              else if (Keyboard::isKeyPressed(Keyboard::W) && ruch_kuli==false)
                {
                    sLufa.rotate(-1);  sLufa.setPosition(pozycja_lufy.x,pozycja_lufy.y+0.8);

                    if (ruch_kuli==false)
                    {
                        if  (rotacja_lufy<=314) sKula.setPosition(pozycja_kuli.x-2,pozycja_kuli.y-0.9);
                        else sKula.setPosition(pozycja_kuli.x-0.4,pozycja_kuli.y-1.5);
                    }

                    ruch_y_kuli=ruch_y_kuli+0.002;
                    ruch_x_kuli=ruch_x_kuli-0.002;
                    Sleep(10);
                }
                else if (Keyboard::isKeyPressed(Keyboard::S)  && ruch_kuli==false)
                {
                    sLufa.rotate(1); sLufa.setPosition(pozycja_lufy.x,pozycja_lufy.y-0.8);

                    if (ruch_kuli==false)
                    {
                        if  (rotacja_lufy<=314) sKula.setPosition(pozycja_kuli.x+2,pozycja_kuli.y+0.9);
                        else sKula.setPosition(pozycja_kuli.x+0.4,pozycja_kuli.y+1.5);
                    }

                    if (ruch_y_kuli>0.002) ruch_y_kuli=ruch_y_kuli-0.002;
                    else if(ruch_y_kuli<=0.001) ruch_y_kuli=0;

                    ruch_x_kuli=ruch_x_kuli+0.002;
                    Sleep(10);
                }


                if(Keyboard::isKeyPressed(Keyboard::Space) && ruch_kuli==false && ilosc_ammo>0
                    && pozycja_kuli.x <= 350 && pozycja_kuli.y >= 700)
                    {
                        sStrzal_czolgu.play();

                        Vector2f pozycja_przed_strzalem=sKula.getPosition();
                        pozycja_przed_strzalem_x=pozycja_przed_strzalem.x;
                        pozycja_przed_strzalem_y=pozycja_przed_strzalem.y;

                        ruch_y_kuli_po_strzale=ruch_y_kuli;
                        respienie_kuli=true;  ruch_kuli=true;
                        ilosc_ammo--;
                        sPrzeladowanie.play();
                    }
                        stringstream ss;  ss<<ilosc_ammo; ss>>ilosc_ammo_string;
                           ammo.setFont(font);  ammo.setString(ilosc_ammo_string); ammo.setPosition(16,60);
                           ammo.setCharacterSize(60);ammo.setFillColor(Color::White);
                        if (ilosc_ammo>=10) sAmmo.setPosition(90,75);
                        else if (ilosc_ammo<=9) {sAmmo.setPosition(55,75);  sAmmo.setScale(1.3,1.3);}


                if (pozycja_kuli_po_strzale==true)
                {
                   sKula.setPosition(pozycja_przed_strzalem_x,pozycja_przed_strzalem_y);
                   pozycja_kuli_po_strzale=false;
                }

                if (ruch_kuli==true)
                {
                       sKula.move(ruch_x_kuli,-ruch_y_kuli);
                       ruch_y_kuli=ruch_y_kuli-0.000002;
                }
              ////////KONIEC MECHANIKI CZOLGU///////////

              ///////////////////level 1/////////////////////////
              if (level==1)
              {
                sMech1.setTexture(mech1); sMech2.setTexture(mech1); sMech3.setTexture(mech1); sMech4.setTexture(mech1); sMech5.setTexture(mech1);

                if (ustawianie_amunicji==true) {ilosc_ammo=15;ustawianie_amunicji=false;}

                if (respienie_mechow==true) {sMech1.setPosition(1020,787); sMech2.setPosition(1070,255); sMech3.setPosition(1300,0); sMech4.setPosition(1620,787); sMech5.setPosition(1570,255); respienie_mechow=false;}
                if (respienie_zycia==true) {Zycie_Mecha_1=1; Zycie_Mecha_2=1; Zycie_Mecha_3=1; Zycie_Mecha_4=1; Zycie_Mecha_5=1; respienie_zycia=false;}

                if (strzal_od_mecha==false) {jaki_mech=rand()%6+1; czy_strzal_mecha=true;}
                if (jaki_mech==1 && strzal_od_mecha==false && Zycie_Mecha_1 > 0) {sAmmo_Mecha.setPosition(1020,877);sAmmo_Mecha.setRotation(0); strzal_od_mecha=true;}
                else if (jaki_mech==2 && strzal_od_mecha==false && Zycie_Mecha_2 > 0) {sAmmo_Mecha.setPosition(1070,355); sAmmo_Mecha.setRotation(-30);strzal_od_mecha=true;}
                else if (jaki_mech==3 && strzal_od_mecha==false && Zycie_Mecha_3 > 0) {sAmmo_Mecha.setPosition(1300,110); sAmmo_Mecha.setRotation(-35);strzal_od_mecha=true;}
                else if (jaki_mech==4 && strzal_od_mecha==false && Zycie_Mecha_4 > 0) {sAmmo_Mecha.setPosition(1620,877); sAmmo_Mecha.setRotation(0); strzal_od_mecha=true;}
                else if (jaki_mech==5 && strzal_od_mecha==false && Zycie_Mecha_5 > 0) {sAmmo_Mecha.setPosition(1570,355); sAmmo_Mecha.setRotation(-25);strzal_od_mecha=true;}
                else if (jaki_mech >= 6 && strzal_od_mecha==false) {strzal_od_mecha=true; sAmmo_Mecha.setPosition(10,10);}

                if (jaki_mech >= 6 && strzal_od_mecha==true) {czas_bez_strzalu=czas_bez_strzalu+0.01;}
                if (czas_bez_strzalu >= 80) {strzal_od_mecha=false; czas_bez_strzalu=0;}
              }
              /////////////////////KONIEC LEVELU 1///////////////

              ///////////////////level 2/////////////////////////
              else if (level==2)
              {
                sMech1.setTexture(mech1); sMech2.setTexture(mech1); sMech3.setTexture(mech2); sMech4.setTexture(mech1); sMech5.setTexture(mech1);
                if (respienie_mechow==true) {sMech1.setPosition(1020,787); sMech2.setPosition(1070,255); sMech3.setPosition(1300,0); sMech4.setPosition(1620,787); sMech5.setPosition(1570,255); respienie_mechow=false;}
                if (respienie_zycia==true){Zycie_Mecha_1=1; Zycie_Mecha_2=1; Zycie_Mecha_3=1; Zycie_Mecha_4=1; Zycie_Mecha_5=1; respienie_zycia=false;}

                if (ustawianie_amunicji==true) {ilosc_ammo=20;ustawianie_amunicji=false;}

                Vector2f pozycja_mecha_3=sMech3.getPosition();

                bool gora_dol_mecha3;

                if (pozycja_mecha_3.y <= 3 ) {gora_dol_mecha3=false;pozycja_ammo_mecha_3_y=0.07;}
                if (pozycja_mecha_3.y >= 815 ) {gora_dol_mecha3=true; pozycja_ammo_mecha_3_y=0;}

                if (gora_dol_mecha3==true)
                    {
                        sMech3.move(0,-0.1);
                        rotacja_ammo_mecha_3=rotacja_ammo_mecha_3-0.004;
                        pozycja_ammo_mecha_3_y=pozycja_ammo_mecha_3_y+0.00001;

                    }     //leci do gory

                else if (gora_dol_mecha3==false)
                 {
                     sMech3.move(0,0.1);
                     rotacja_ammo_mecha_3=rotacja_ammo_mecha_3+0.004;
                     pozycja_ammo_mecha_3_y=pozycja_ammo_mecha_3_y-0.00001;

                 } //leci w dol

                if (strzal_mecha==false) {rotacja_ammo_mecha_3_po_strzale=rotacja_ammo_mecha_3;pozycja_ammo_mecha_3_y_po_strzale=pozycja_ammo_mecha_3_y;}
                if (jaki_mech==3) sAmmo_Mecha.setRotation(rotacja_ammo_mecha_3_po_strzale);

                if (strzal_od_mecha==false) {jaki_mech=rand()%6+1; czy_strzal_mecha=true;}
                if (jaki_mech==1 && strzal_od_mecha==false  && Zycie_Mecha_1 > 0) {sAmmo_Mecha.setPosition(1020,877); sAmmo_Mecha.setRotation(0); strzal_od_mecha=true;}
                else if (jaki_mech==2 && strzal_od_mecha==false && Zycie_Mecha_2 > 0) {sAmmo_Mecha.setPosition(1070,355); sAmmo_Mecha.setRotation(-30);strzal_od_mecha=true;}
                else if (jaki_mech==3 && strzal_od_mecha==false && Zycie_Mecha_3 > 0) {sAmmo_Mecha.setPosition(pozycja_mecha_3.x,pozycja_mecha_3.y+110); sAmmo_Mecha.setRotation(rotacja_ammo_mecha_3_po_strzale);strzal_od_mecha=true;}
                else if (jaki_mech==4 && strzal_od_mecha==false && Zycie_Mecha_4 > 0) {sAmmo_Mecha.setPosition(1620,877); sAmmo_Mecha.setRotation(0); strzal_od_mecha=true;}
                else if (jaki_mech==5 && strzal_od_mecha==false && Zycie_Mecha_5 > 0) {sAmmo_Mecha.setPosition(1570,355); sAmmo_Mecha.setRotation(-25);strzal_od_mecha=true;}
                else if (jaki_mech >= 6 && strzal_od_mecha==false) {strzal_od_mecha=true; sAmmo_Mecha.setPosition(10,10);}

                if (jaki_mech >= 6 && strzal_od_mecha==true) {czas_bez_strzalu=czas_bez_strzalu+0.01;}
                if (czas_bez_strzalu >= 80) {strzal_od_mecha=false; czas_bez_strzalu=0;}
             }
              /////////////////////KONIEC LEVELU 2///////////////

              ///////////////////level 3/////////////////////////
              else if (level==3)
              {
                sMech1.setTexture(mech1); sMech2.setTexture(mech1); sMech3.setTexture(mech3); sMech4.setTexture(mech2); sMech5.setTexture(mech2);
                if (respienie_mechow==true) {sMech1.setPosition(1020,787); sMech2.setPosition(1070,255); sMech3.setPosition(1300,0); sMech4.setPosition(1620,787); sMech5.setPosition(1570,255); respienie_mechow=false;}
                if (respienie_zycia==true) {Zycie_Mecha_1=1; Zycie_Mecha_2=1; Zycie_Mecha_3=3; Zycie_Mecha_4=1; Zycie_Mecha_5=1; respienie_zycia=false;}

                if (ustawianie_amunicji==true) {ilosc_ammo=20;ustawianie_amunicji=false;}

                Vector2f pozycja_mecha_4=sMech4.getPosition();
                Vector2f pozycja_mecha_5=sMech5.getPosition();

                bool gora_dol_mecha4,gora_dol_mecha5;
                ////////////////////MECH 4//////////////////////////
                if (pozycja_mecha_4.y <= 3 ) {gora_dol_mecha4=false; pozycja_ammo_mecha_4_y=0.06;}
                if (pozycja_mecha_4.y >= 815 ) {gora_dol_mecha4=true;pozycja_ammo_mecha_4_y=0;}

                if (gora_dol_mecha4==true)
                {
                    sMech4.move(0,-0.1);
                    rotacja_ammo_mecha_4=rotacja_ammo_mecha_4-0.004;
                    pozycja_ammo_mecha_4_y=pozycja_ammo_mecha_4_y+0.000008;
                }
                else if (gora_dol_mecha4==false)
                {
                  sMech4.move(0,0.1);
                  rotacja_ammo_mecha_4=rotacja_ammo_mecha_4+0.004;
                  pozycja_ammo_mecha_4_y=pozycja_ammo_mecha_4_y-0.000008;
                }


                ////////////////////KONIEC MECHu 4////////////////////
                ////////////////////MECH 5//////////////////////////
                if (pozycja_mecha_5.y <= 3 ) {gora_dol_mecha5=false; pozycja_ammo_mecha_5_y=0.06;}
                if (pozycja_mecha_5.y >= 815 ) {gora_dol_mecha5=true;pozycja_ammo_mecha_5_y=0;}

                if (gora_dol_mecha5==true)
                {
                    sMech5.move(0,-0.1);
                    rotacja_ammo_mecha_5=rotacja_ammo_mecha_5-0.004;
                    pozycja_ammo_mecha_5_y=pozycja_ammo_mecha_5_y+0.000008;
                }
                else if (gora_dol_mecha5==false)
                {
                  sMech5.move(0,0.1);
                  rotacja_ammo_mecha_5=rotacja_ammo_mecha_5+0.004;
                  pozycja_ammo_mecha_5_y=pozycja_ammo_mecha_5_y-0.000008;
                }


                ////////////////////KONIEC MECHU 5//////////////////////////
                if (strzal_mecha==false)
                    {
                        rotacja_ammo_mecha_4_po_strzale=rotacja_ammo_mecha_4;
                        pozycja_ammo_mecha_4_y_po_strzale=pozycja_ammo_mecha_4_y;

                        rotacja_ammo_mecha_5_po_strzale=rotacja_ammo_mecha_5;
                        pozycja_ammo_mecha_5_y_po_strzale=pozycja_ammo_mecha_5_y;
                    }

                if (jaki_mech==4) sAmmo_Mecha.setRotation(rotacja_ammo_mecha_4_po_strzale);
                if (jaki_mech==5) sAmmo_Mecha.setRotation(rotacja_ammo_mecha_5_po_strzale);

                if (strzal_od_mecha==false) {jaki_mech=rand()%6+1; czy_strzal_mecha=true;}
                if (jaki_mech==1 && strzal_od_mecha==false && Zycie_Mecha_1 > 0) {sAmmo_Mecha.setPosition(1020,877); sAmmo_Mecha.setRotation(0); strzal_od_mecha=true;}
                else if (jaki_mech==2 && strzal_od_mecha==false && Zycie_Mecha_2 > 0) {sAmmo_Mecha.setPosition(1070,355); sAmmo_Mecha.setRotation(-30);strzal_od_mecha=true;}
                else if (jaki_mech==3 && strzal_od_mecha==false && Zycie_Mecha_3 > 0) {sAmmo_Mecha.setPosition(1300,110); sAmmo_Mecha.setRotation(-35);strzal_od_mecha=true;}
                else if (jaki_mech==4 && strzal_od_mecha==false && Zycie_Mecha_4 > 0) {sAmmo_Mecha.setPosition(pozycja_mecha_4.x,pozycja_mecha_4.y+110); sAmmo_Mecha.setRotation(rotacja_ammo_mecha_4_po_strzale); strzal_od_mecha=true;}
                else if (jaki_mech==5 && strzal_od_mecha==false && Zycie_Mecha_5 > 0) {sAmmo_Mecha.setPosition(pozycja_mecha_5.x,pozycja_mecha_5.y+110); sAmmo_Mecha.setRotation(rotacja_ammo_mecha_5_po_strzale);strzal_od_mecha=true;}
                else if (jaki_mech >= 6 && strzal_od_mecha==false) {strzal_od_mecha=true; sAmmo_Mecha.setPosition(10,10);}

                if (jaki_mech >= 6 && strzal_od_mecha==true) {czas_bez_strzalu=czas_bez_strzalu+0.01;}
                if (czas_bez_strzalu >= 80) {strzal_od_mecha=false; czas_bez_strzalu=0;}
              }
              /////////////////////KONIEC LEVELU 3///////////////

              ///////////////////level 4/////////////////////////
              else if (level==4)
              {
                sMech1.setTexture(mech3); sMech2.setTexture(mech2); sMech3.setTexture(mech3); sMech4.setTexture(mech2); sMech5.setTexture(mech3);
                if (respienie_mechow==true) {sMech1.setPosition(1020,787); sMech2.setPosition(1070,255); sMech3.setPosition(1300,0); sMech4.setPosition(1620,787); sMech5.setPosition(1570,255); respienie_mechow=false;}
                if (respienie_zycia==true) {Zycie_Mecha_1=3; Zycie_Mecha_2=1; Zycie_Mecha_3=3; Zycie_Mecha_4=1; Zycie_Mecha_5=3; respienie_zycia=false;}

                if (ustawianie_amunicji==true) {ilosc_ammo=25;ustawianie_amunicji=false;}

                Vector2f pozycja_mecha_2=sMech2.getPosition();
                Vector2f pozycja_mecha_4=sMech4.getPosition();

                bool gora_dol_mecha4,gora_dol_mecha2;

                ////////////////////MECH 4//////////////////////////
                if (pozycja_mecha_4.y <= 3 ) {gora_dol_mecha4=false; pozycja_ammo_mecha_4_y=0.06;}
                if (pozycja_mecha_4.y >= 815 ) {gora_dol_mecha4=true;pozycja_ammo_mecha_4_y=0;}

                if (gora_dol_mecha4==true)
                {
                    sMech4.move(0,-0.1);
                    rotacja_ammo_mecha_4=rotacja_ammo_mecha_4-0.004;
                    pozycja_ammo_mecha_4_y=pozycja_ammo_mecha_4_y+0.000008;
                }
                else if (gora_dol_mecha4==false)
                {
                  sMech4.move(0,0.1);
                  rotacja_ammo_mecha_4=rotacja_ammo_mecha_4+0.004;
                  pozycja_ammo_mecha_4_y=pozycja_ammo_mecha_4_y-0.000008;
                }


                ////////////////////KONIEC MECHu 4////////////////////
                ////////////////////MECH 2//////////////////////////
                if (pozycja_mecha_2.y <= 3 ) {gora_dol_mecha2=false; pozycja_ammo_mecha_2_y=0.07;}
                if (pozycja_mecha_2.y >= 815 ) {gora_dol_mecha2=true;pozycja_ammo_mecha_2_y=0;}

                if (gora_dol_mecha2==true)
                {
                    sMech2.move(0,-0.1);
                    rotacja_ammo_mecha_2=rotacja_ammo_mecha_2-0.004;
                    pozycja_ammo_mecha_2_y=pozycja_ammo_mecha_2_y+0.000012;
                }
                else if (gora_dol_mecha2==false)
                {
                  sMech2.move(0,0.1);
                  rotacja_ammo_mecha_2=rotacja_ammo_mecha_2+0.004;
                  pozycja_ammo_mecha_2_y=pozycja_ammo_mecha_2_y-0.000012;
                }


                ////////////////////KONIEC MECHU 2//////////////////////////
                if (strzal_mecha==false)
                    {
                        rotacja_ammo_mecha_4_po_strzale=rotacja_ammo_mecha_4;
                        pozycja_ammo_mecha_4_y_po_strzale=pozycja_ammo_mecha_4_y;

                        rotacja_ammo_mecha_2_po_strzale=rotacja_ammo_mecha_2;
                        pozycja_ammo_mecha_2_y_po_strzale=pozycja_ammo_mecha_2_y;
                    }

                if (jaki_mech==4) sAmmo_Mecha.setRotation(rotacja_ammo_mecha_4_po_strzale);
                else if (jaki_mech==2) sAmmo_Mecha.setRotation(rotacja_ammo_mecha_2_po_strzale);

                if (strzal_od_mecha==false) {jaki_mech=rand()%6+1; czy_strzal_mecha=true;}
                if (jaki_mech==1 && strzal_od_mecha==false && Zycie_Mecha_1 > 0) {sAmmo_Mecha.setPosition(1020,877); sAmmo_Mecha.setRotation(0); strzal_od_mecha=true;}
                else if (jaki_mech==2 && strzal_od_mecha==false && Zycie_Mecha_2 > 0) {sAmmo_Mecha.setPosition(pozycja_mecha_2.x,pozycja_mecha_2.y+110); sAmmo_Mecha.setRotation(rotacja_ammo_mecha_2_po_strzale);strzal_od_mecha=true;}
                else if (jaki_mech==3 && strzal_od_mecha==false && Zycie_Mecha_3 > 0) {sAmmo_Mecha.setPosition(1300,110); sAmmo_Mecha.setRotation(-35);strzal_od_mecha=true;}
                else if (jaki_mech==4 && strzal_od_mecha==false && Zycie_Mecha_4 > 0) {sAmmo_Mecha.setPosition(pozycja_mecha_4.x,pozycja_mecha_4.y+110); sAmmo_Mecha.setRotation(rotacja_ammo_mecha_4_po_strzale); strzal_od_mecha=true;}
                else if (jaki_mech==5 && strzal_od_mecha==false && Zycie_Mecha_5 > 0) {sAmmo_Mecha.setPosition(1570,355); sAmmo_Mecha.setRotation(-25);strzal_od_mecha=true;}
                else if (jaki_mech >= 6 && strzal_od_mecha==false) {strzal_od_mecha=true; sAmmo_Mecha.setPosition(10,10);}

                if (jaki_mech >= 6 && strzal_od_mecha==true) {czas_bez_strzalu=czas_bez_strzalu+0.01;}
                if (czas_bez_strzalu >= 80) {strzal_od_mecha=false; czas_bez_strzalu=0;}
              }
              /////////////////////KONIEC LEVELU 4///////////////

              ///////////////////level 5/////////////////////////
              else if (level==5)
              {
                sMech1.setTexture(mech4); sMech2.setTexture(mech3); sMech3.setTexture(mech4); sMech4.setTexture(mech3); sMech5.setTexture(mech4);
                if (respienie_mechow==true) {sMech1.setPosition(1020,787); sMech2.setPosition(1070,255); sMech3.setPosition(1300,0); sMech4.setPosition(1620,787); sMech5.setPosition(1570,255); respienie_mechow=false;}
                if (respienie_zycia==true) {Zycie_Mecha_1=3; Zycie_Mecha_2=3; Zycie_Mecha_3=3; Zycie_Mecha_4=3; Zycie_Mecha_5=3; respienie_zycia=false;}

                if (ustawianie_amunicji==true) {ilosc_ammo=30;ustawianie_amunicji=false;}

                Vector2f pozycja_mecha_1=sMech1.getPosition();
                Vector2f pozycja_mecha_3=sMech3.getPosition();
                Vector2f pozycja_mecha_5=sMech5.getPosition();

                bool gora_dol_mecha1,gora_dol_mecha5,gora_dol_mecha3;
                ///////////////////////MECH 1///////////////////////////////
                if (pozycja_mecha_1.y <= 3 ) {gora_dol_mecha1=false;pozycja_ammo_mecha_1_y=0.07;}
                if (pozycja_mecha_1.y >= 815 ) {gora_dol_mecha1=true; pozycja_ammo_mecha_1_y=0;}

                if (gora_dol_mecha1==true)
                    {
                        sMech1.move(0,-0.1);
                        rotacja_ammo_mecha_1=rotacja_ammo_mecha_1-0.004;
                        pozycja_ammo_mecha_1_y=pozycja_ammo_mecha_1_y+0.00001;

                    }     //leci do gory

                else if (gora_dol_mecha1==false)
                 {
                     sMech1.move(0,0.1);
                     rotacja_ammo_mecha_1=rotacja_ammo_mecha_1+0.004;
                     pozycja_ammo_mecha_1_y=pozycja_ammo_mecha_1_y-0.00001;

                 } //leci w dol
                //////////////////////KONIEC MECHU 1///////////////////////////////

                ///////////////////////MECH 3///////////////////////////////
                if (pozycja_mecha_3.y <= 3 ) {gora_dol_mecha3=false;pozycja_ammo_mecha_3_y=0.07;}
                if (pozycja_mecha_3.y >= 815 ) {gora_dol_mecha3=true; pozycja_ammo_mecha_3_y=0;}

                if (gora_dol_mecha3==true)
                    {
                        sMech3.move(0,-0.1);
                        rotacja_ammo_mecha_3=rotacja_ammo_mecha_3-0.004;
                        pozycja_ammo_mecha_3_y=pozycja_ammo_mecha_3_y+0.00001;

                    }     //leci do gory

                else if (gora_dol_mecha3==false)
                 {
                     sMech3.move(0,0.1);
                     rotacja_ammo_mecha_3=rotacja_ammo_mecha_3+0.004;
                     pozycja_ammo_mecha_3_y=pozycja_ammo_mecha_3_y-0.00001;

                 } //leci w dol
                ///////////////////////KONIEC MECHU 3///////////////////////

                ///////////////////////MECH 5///////////////////////////////
                if (pozycja_mecha_5.y <= 3 ) {gora_dol_mecha5=false; pozycja_ammo_mecha_5_y=0.06;}
                if (pozycja_mecha_5.y >= 815 ) {gora_dol_mecha5=true;pozycja_ammo_mecha_5_y=0;}

                if (gora_dol_mecha5==true)
                {
                    sMech5.move(0,-0.1);
                    rotacja_ammo_mecha_5=rotacja_ammo_mecha_5-0.004;
                    pozycja_ammo_mecha_5_y=pozycja_ammo_mecha_5_y+0.000008;
                }
                else if (gora_dol_mecha5==false)
                {
                  sMech5.move(0,0.1);
                  rotacja_ammo_mecha_5=rotacja_ammo_mecha_5+0.004;
                  pozycja_ammo_mecha_5_y=pozycja_ammo_mecha_5_y-0.000008;
                }
                ///////////////////////KONIEC MECHU 5///////////////////////

                if (strzal_mecha==false)
                    {
                        rotacja_ammo_mecha_1_po_strzale=rotacja_ammo_mecha_1;
                        pozycja_ammo_mecha_1_y_po_strzale=pozycja_ammo_mecha_1_y;

                        rotacja_ammo_mecha_3_po_strzale=rotacja_ammo_mecha_3;
                        pozycja_ammo_mecha_3_y_po_strzale=pozycja_ammo_mecha_3_y;

                        rotacja_ammo_mecha_5_po_strzale=rotacja_ammo_mecha_5;
                        pozycja_ammo_mecha_5_y_po_strzale=pozycja_ammo_mecha_5_y;
                    }

                if (jaki_mech==1) sAmmo_Mecha.setRotation(rotacja_ammo_mecha_1_po_strzale);
                else if (jaki_mech==3) sAmmo_Mecha.setRotation(rotacja_ammo_mecha_3_po_strzale);
                else if (jaki_mech==5) sAmmo_Mecha.setRotation(rotacja_ammo_mecha_5_po_strzale);

                if (strzal_od_mecha==false) {jaki_mech=rand()%6+1; czy_strzal_mecha=true;}
                if (jaki_mech==1 && strzal_od_mecha==false  && Zycie_Mecha_1 > 0) {sAmmo_Mecha.setPosition(pozycja_mecha_1.x,pozycja_mecha_1.y+110); sAmmo_Mecha.setRotation(rotacja_ammo_mecha_1_po_strzale); strzal_od_mecha=true;}
                else if (jaki_mech==2 && strzal_od_mecha==false && Zycie_Mecha_2 > 0) {sAmmo_Mecha.setPosition(1070,355); sAmmo_Mecha.setRotation(-30);strzal_od_mecha=true;}
                else if (jaki_mech==3 && strzal_od_mecha==false && Zycie_Mecha_3 > 0) {sAmmo_Mecha.setPosition(pozycja_mecha_3.x,pozycja_mecha_3.y+110); sAmmo_Mecha.setRotation(rotacja_ammo_mecha_3_po_strzale);strzal_od_mecha=true;}
                else if (jaki_mech==4 && strzal_od_mecha==false && Zycie_Mecha_4 > 0) {sAmmo_Mecha.setPosition(1620,877); sAmmo_Mecha.setRotation(0); strzal_od_mecha=true;}
                else if (jaki_mech==5 && strzal_od_mecha==false && Zycie_Mecha_5 > 0) {sAmmo_Mecha.setPosition(pozycja_mecha_5.x,pozycja_mecha_5.y+110); sAmmo_Mecha.setRotation(rotacja_ammo_mecha_5_po_strzale);strzal_od_mecha=true;}
                else if (jaki_mech >= 6 && strzal_od_mecha==false) {strzal_od_mecha=true; sAmmo_Mecha.setPosition(10,10);}

                if (jaki_mech >= 6 && strzal_od_mecha==true) {czas_bez_strzalu=czas_bez_strzalu+0.01;}
                if (czas_bez_strzalu >= 80) {strzal_od_mecha=false; czas_bez_strzalu=0;}
              }
              /////////////////////KONIEC LEVELU 5///////////////

              ///////////////////level 6/////////////////////////
              else if (level==6)
              {
                sBoss.setPosition(900,-10); sZycie_Bossa.setPosition(451,5); sOko.setPosition(1210,-1);
                sLewyKarabin.setPosition(1522,380);sPrawyKarabin.setPosition(910,393);
                sLeweRamie.setPosition(1421,16);sPraweRamie.setPosition(1032,33);

                if (ustawianie_amunicji==true) {ilosc_ammo=20;ustawianie_amunicji=false;}

                 if (migniecie_prawego_karabinu==true) czas_migniecia_prawego_karabinu=czas_migniecia_prawego_karabinu+0.01;
                 if (migniecie_lewego_karabinu==true) czas_migniecia_lewego_karabinu=czas_migniecia_lewego_karabinu+0.01;
                 if (migniecie_prawego_ramienia==true) czas_migniecia_prawego_ramienia=czas_migniecia_prawego_ramienia+0.01;
                 if (migniecie_lewego_ramienia==true) czas_migniecia_lewego_ramienia=czas_migniecia_lewego_ramienia+0.01;
                 if (migniecie_oka==true) czas_migniecia_oka=czas_migniecia_oka+0.01;

                 if (isCollide(sKula,sPrawyKarabin) && ilosc_zycia_prawego_karabinu != 0)
                    {

                        ilosc_zycia_bossa=ilosc_zycia_bossa-0.05;
                        sZycie_Bossa.setScale(ilosc_zycia_bossa,1);
                        ilosc_zycia_prawego_karabinu=ilosc_zycia_prawego_karabinu-1;

                        if (ilosc_zycia_prawego_karabinu != 0) migniecie_prawego_karabinu=true;

                        respienie_kuli=false; ruch_kuli=false; pozycja_kuli_po_strzale=true;
                        ruch_y_kuli=ruch_y_kuli_po_strzale;

                        if (ilosc_zycia_prawego_karabinu <= 0) ilosc_ammo=ilosc_ammo+3;

                    }// prawy karabin*/

                    if (isCollide(sKula,sLewyKarabin) && ilosc_zycia_lewego_karabinu != 0)
                    {

                        ilosc_zycia_bossa=ilosc_zycia_bossa-0.05;
                        sZycie_Bossa.setScale(ilosc_zycia_bossa,1);
                        ilosc_zycia_lewego_karabinu=ilosc_zycia_lewego_karabinu-1;

                        if (ilosc_zycia_lewego_karabinu != 0) migniecie_lewego_karabinu=true;

                        respienie_kuli=false; ruch_kuli=false; pozycja_kuli_po_strzale=true;
                        ruch_y_kuli=ruch_y_kuli_po_strzale;

                        if (ilosc_zycia_lewego_karabinu <= 0) ilosc_ammo=ilosc_ammo+3;

                    }// lewy karabin*/

                    if (isCollide(sKula,sLeweRamie) && ilosc_zycia_lewe_ramie != 0)
                    {

                        ilosc_zycia_bossa=ilosc_zycia_bossa-0.05;
                        sZycie_Bossa.setScale(ilosc_zycia_bossa,1);
                        ilosc_zycia_lewe_ramie=ilosc_zycia_lewe_ramie-1;

                        if (ilosc_zycia_lewe_ramie != 0) migniecie_lewego_ramienia=true;

                        respienie_kuli=false; ruch_kuli=false; pozycja_kuli_po_strzale=true;
                        ruch_y_kuli=ruch_y_kuli_po_strzale;

                        if (ilosc_zycia_lewe_ramie <= 0) ilosc_ammo=ilosc_ammo+3;

                    }// lewe Ramie*/

                    if (isCollide(sKula,sPraweRamie) && ilosc_zycia_prawe_ramie != 0)
                    {

                        ilosc_zycia_bossa=ilosc_zycia_bossa-0.05;
                        sZycie_Bossa.setScale(ilosc_zycia_bossa,1);
                        ilosc_zycia_prawe_ramie=ilosc_zycia_prawe_ramie-1;

                        if (ilosc_zycia_prawe_ramie != 0) migniecie_prawego_ramienia=true;

                        respienie_kuli=false; ruch_kuli=false; pozycja_kuli_po_strzale=true;
                        ruch_y_kuli=ruch_y_kuli_po_strzale;

                        if (ilosc_zycia_prawe_ramie <= 0) ilosc_ammo=ilosc_ammo+3;

                    }// prawy karabin*/

                    if (isCollide(sKula,sOko) && ilosc_zycia_oko != 0 && ilosc_zycia_lewego_karabinu <= 0 &&
                        ilosc_zycia_prawego_karabinu <= 0 && ilosc_zycia_prawe_ramie <= 0 && ilosc_zycia_lewe_ramie <= 0)
                    {

                        ilosc_zycia_bossa=ilosc_zycia_bossa-0.05;
                        sZycie_Bossa.setScale(ilosc_zycia_bossa,1);
                        ilosc_zycia_oko=ilosc_zycia_oko-1;

                        if (ilosc_zycia_oko != 0) migniecie_oka=true;

                        respienie_kuli=false; ruch_kuli=false; pozycja_kuli_po_strzale=true;
                        ruch_y_kuli=ruch_y_kuli_po_strzale;
                    }// OKO*/

                    // 1 to prawy karabin i dolny otwor, 2 to prawy karabin i gorny otwor, 3 to lewy karabin i dolny otwor, 4 to lewy karabin i gorny otwor
                    if (strzal_od_mecha==false) {jaki_mech=rand()%5+1; czy_strzal_mecha=true;}
                    if      (jaki_mech==1 && strzal_od_mecha==false && ilosc_zycia_prawego_karabinu > 0) {sAmmo_Mecha.setPosition(930,615);sAmmo_Mecha.setRotation(-20); strzal_od_mecha=true;}
                    else if (jaki_mech==2 && strzal_od_mecha==false && ilosc_zycia_prawego_karabinu > 0) {sAmmo_Mecha.setPosition(930,560); sAmmo_Mecha.setRotation(-25);strzal_od_mecha=true;}
                    else if (jaki_mech==3 && strzal_od_mecha==false && ilosc_zycia_lewego_karabinu  > 0) {sAmmo_Mecha.setPosition(1520,640); sAmmo_Mecha.setRotation(-15);strzal_od_mecha=true;}
                    else if (jaki_mech==4 && strzal_od_mecha==false && ilosc_zycia_lewego_karabinu  > 0) {sAmmo_Mecha.setPosition(1520,575); sAmmo_Mecha.setRotation(-17); strzal_od_mecha=true;}
                    else if (jaki_mech>=5 && strzal_od_mecha==false) {strzal_od_mecha=true; sAmmo_Mecha.setPosition(10,10);}

                    if (jaki_mech >= 5 && strzal_od_mecha==true) {czas_bez_strzalu=czas_bez_strzalu+0.01;}
                    if (czas_bez_strzalu >= 80) {strzal_od_mecha=false; czas_bez_strzalu=0;}
               }
              /////////////////////KONIEC LEVELU 6///////////////


                  app.clear();
                  if (respienie_czolgu==true) {sCzolg.setPosition(0,840); respienie_czolgu=false;}
                  app.draw(sGra);
                  app.draw(ammo);
                  app.draw(sAmmo);
                  if (level==6) {app.draw(sBoss);}

                  if (level==6 && ilosc_zycia_prawego_karabinu <= 0) {app.draw(sPrawyKarabin);}
                  if (level==6 && ilosc_zycia_lewego_karabinu <= 0) {app.draw(sLewyKarabin);}
                  if (level==6 && ilosc_zycia_lewe_ramie <= 0) {app.draw(sLeweRamie);}
                  if (level==6 && ilosc_zycia_prawe_ramie <= 0) {app.draw(sPraweRamie);}
                  if (level==6 && ilosc_zycia_oko <= 0) {app.draw(sOko);}

                  if (migniecie_lewego_karabinu==true)  {app.draw(sLewyKarabin);  if(czas_migniecia_lewego_karabinu >= 10){migniecie_lewego_karabinu=false; czas_migniecia_lewego_karabinu=0;}}
                  if (migniecie_lewego_ramienia==true)  {app.draw(sLeweRamie);    if (czas_migniecia_lewego_ramienia >= 10) {migniecie_lewego_ramienia=false; czas_migniecia_lewego_ramienia=0;}}
                  if (migniecie_prawego_karabinu==true) {app.draw(sPrawyKarabin); if (czas_migniecia_prawego_karabinu >= 10) {migniecie_prawego_karabinu=false; czas_migniecia_prawego_karabinu=0;}}
                  if (migniecie_prawego_ramienia==true) {app.draw(sPraweRamie);   if (czas_migniecia_prawego_ramienia >= 10) {migniecie_prawego_ramienia=false; czas_migniecia_prawego_ramienia=0;}}
                  if (migniecie_oka==true)              {app.draw(sOko);          if (czas_migniecia_oka >= 10) {migniecie_oka=false; czas_migniecia_oka=0;}}

                  if (level==6) { app.draw(sZycie_Bossa); }
                  if (respienie_kuli==true) app.draw(sKula);
                  app.draw(sLufa);
                  app.draw(sCzolg);
                  //270 szerokosc i 350 wysokosc maja mechy
                  if (isCollide(sKula,sMech1) && Zycie_Mecha_1 > 0 && level < 6)
                  {
                      respienie_kuli=false; ruch_kuli=false; pozycja_kuli_po_strzale=true;
                        ruch_y_kuli=ruch_y_kuli_po_strzale;
                        Zycie_Mecha_1--;
                  }

                    if (isCollide(sKula,sMech2) && Zycie_Mecha_2 > 0 && level < 6)
                    {
                          respienie_kuli=false; ruch_kuli=false; pozycja_kuli_po_strzale=true;
                            ruch_y_kuli=ruch_y_kuli_po_strzale;
                            Zycie_Mecha_2--;
                    }

                  if (isCollide(sKula,sMech3) && Zycie_Mecha_3 > 0 && level < 6)
                  {
                      respienie_kuli=false; ruch_kuli=false; pozycja_kuli_po_strzale=true;
                        ruch_y_kuli=ruch_y_kuli_po_strzale;
                        Zycie_Mecha_3--;
                  }

                   if (isCollide(sKula,sMech4) && Zycie_Mecha_4 > 0 && level < 6)
                   {
                          respienie_kuli=false; ruch_kuli=false; pozycja_kuli_po_strzale=true;
                            ruch_y_kuli=ruch_y_kuli_po_strzale;
                            Zycie_Mecha_4--;
                   }

                  if (isCollide(sKula,sMech5) && Zycie_Mecha_5 > 0 && level < 6)
                  {
                      respienie_kuli=false; ruch_kuli=false; pozycja_kuli_po_strzale=true;
                        ruch_y_kuli=ruch_y_kuli_po_strzale;
                        Zycie_Mecha_5--;
                  }

                  sZycia.setPosition(16,30);
                  if (zycie_czolgu==3) {sZycia.setTexture(zycia_3_3); app.draw(sZycia);}
                  else if (zycie_czolgu==2) {sZycia.setTexture(zycia_2_3); app.draw(sZycia);}
                  else if (zycie_czolgu==1) {sZycia.setTexture(zycia_1_3); app.draw(sZycia);}
                  else if (zycie_czolgu==0) {sZycia.setTexture(zycia_0_3); app.draw(sZycia);}


                  if (level!=0 && level < 6)
                    {
                        if (Zycie_Mecha_1 > 0) app.draw(sMech1);
                        if (Zycie_Mecha_1 == 0)  {sWybuch.play(); ilosc_mechow--; Zycie_Mecha_1--;}
                        if (Zycie_Mecha_3 > 0) app.draw(sMech3);
                        if (Zycie_Mecha_3 == 0)  {sWybuch.play(); ilosc_mechow--; Zycie_Mecha_3--;}
                        if (Zycie_Mecha_2 > 0) app.draw(sMech2);
                        if (Zycie_Mecha_2 == 0)  {sWybuch.play(); ilosc_mechow--; Zycie_Mecha_2--;}
                        if (Zycie_Mecha_4 > 0)  app.draw(sMech4);
                        if (Zycie_Mecha_4 == 0)  {sWybuch.play(); ilosc_mechow--; Zycie_Mecha_4--;}
                        if (Zycie_Mecha_5 > 0) app.draw(sMech5);
                        if (Zycie_Mecha_5 == 0)  {sWybuch.play(); ilosc_mechow--; Zycie_Mecha_5--;}
                    }

                   if (strzal_od_mecha==true && jaki_mech <= 5 && level < 6)
                    {
                        if (czy_strzal_mecha==true) {sStrzal_Mecha.play(); czy_strzal_mecha=false;}
                        if (jaki_mech==1) {sAmmo_Mecha.move(-0.1,pozycja_ammo_mecha_1_y_po_strzale); strzal_mecha=true;}
                        else if (jaki_mech==2) {sAmmo_Mecha.move(-0.1,pozycja_ammo_mecha_2_y_po_strzale); strzal_mecha=true;}
                        else if (jaki_mech==3) {sAmmo_Mecha.move(-0.1,pozycja_ammo_mecha_3_y_po_strzale); strzal_mecha=true;}
                        else if (jaki_mech==4) {sAmmo_Mecha.move(-0.1,pozycja_ammo_mecha_4_y_po_strzale); strzal_mecha=true;}
                        else if (jaki_mech==5) {sAmmo_Mecha.move(-0.1,pozycja_ammo_mecha_5_y_po_strzale); strzal_mecha=true;}
                        app.draw(sAmmo_Mecha);
                    }

                  if (strzal_od_mecha==true && jaki_mech <= 4 && level >= 6)
                    {
                        if (czy_strzal_mecha==true) {sStrzal_Mecha.play(); czy_strzal_mecha=false;}
                        if (jaki_mech==1) {sAmmo_Mecha.move(-0.09,0.04); strzal_mecha=true;}
                        else if (jaki_mech==2) {sAmmo_Mecha.move(-0.09,0.045); strzal_mecha=true;}
                        else if (jaki_mech==3) {sAmmo_Mecha.move(-0.095,0.02); strzal_mecha=true;}
                        else if (jaki_mech==4) {sAmmo_Mecha.move(-0.095,0.025); strzal_mecha=true;}
                        app.draw(sAmmo_Mecha);
                    }

                  if (isCollide(sCzolg,sAmmo_Mecha) && jaki_mech <= 5)
                  {
                    strzal_od_mecha=false;
                    strzal_mecha=false;
                    zycie_czolgu--;
                  }


                  if (isCollide(sKula,sAmmo_Mecha) && jaki_mech <= 5)
                  {
                      strzal_od_mecha=false; strzal_mecha=false;
                        respienie_kuli=false; ruch_kuli=false; pozycja_kuli_po_strzale=true;
                        ruch_y_kuli=ruch_y_kuli_po_strzale;
                  }


                  Vector2f czy_za_ekran_mech=sAmmo_Mecha.getPosition();
                  Vector2f czy_za_ekran_kula=sKula.getPosition();

                  if (czy_za_ekran_kula.x <= 0 || czy_za_ekran_kula.x >= 1920 || czy_za_ekran_kula.y <= 0 || czy_za_ekran_kula.y >= 1080)
                  {
                    respienie_kuli=false; ruch_kuli=false; pozycja_kuli_po_strzale=true;
                        ruch_y_kuli=ruch_y_kuli_po_strzale;

                  }
                  if(czy_za_ekran_mech.x <= 0 || czy_za_ekran_mech.x >= 1920 || czy_za_ekran_mech.y <= 0 || czy_za_ekran_mech.y >= 1080)
                  {
                    strzal_od_mecha=false; strzal_mecha=false;
                  }

                  if (ilosc_mechow<=0) {menu="wygrana"; ilosc_mechow=5; sWygrana_dzwiek.play();}
                  if (ilosc_zycia_bossa <= 0) {menu="credits"; ilosc_zycia_bossa = 1; sWygrana_dzwiek.play(); poczatkowa_pozycja_creditsow=true; Sleep(1000);}

                    if(zycie_czolgu <= 0)
                        {
                            sWybuch.play();
                            Sleep(1000);
                            menu="przegrana";
                            sPrzegrana_dzwiek.play();
                            zycie_czolgu=3;
                        }
        }
        //////////////////CREDITSY///////////////////////
        if (menu=="credits")
        {
           app.clear();

              if (poczatkowa_pozycja_creditsow==true)
              {
                 sCredits.setPosition(296, 1100);
                 poczatkowa_pozycja_creditsow=false;
              }
           Vector2f pozycja_creditsow = sCredits.getPosition();
           sCredits.move(0, -0.05);
           if (pozycja_creditsow.y <= -150) menu="menu";

           app.draw(sTlo_credits);
           app.draw(sCredits);
        }
        /////////////////KONIEC CREDITSOW///////////////
        ///////////////////RESTART/////////////////////
        if (menu=="restart")
        {
            ilosc_ammo=0; ilosc_naraz_strzalow=1;
            ilosc_mechow=5; zycie_czolgu=3; jaki_mech=0;
            respienie_kuli=false; ruch_kuli=false; pozycja_kuli_po_strzale=true;
            strzal_kuli=false; respienie_czolgu=true; respienie_zycia=true; strzal_od_mecha=false;
            respienie_mechow=true; ruch_ammo_mecha=false; strzal_mecha=false;
            if (menu_czy_restart==true) menu="menu";
            else if (menu_czy_restart==false) menu="start";
            czy_muzyka=false,czy_zmiana_napisu=true,czy_strzal_mecha=false;
            muzyka_podczas_grania.stop();
            czas_bez_strzalu=0;
            ustawianie_amunicji=true;

            ruch_x_kuli=0.25;ruch_y_kuli=0;ruch_y_kuli_po_strzale=0;rotacja_lufy=0;

            ilosc_zycia_bossa=1;ilosc_zycia_prawe_ramie=4;
            ilosc_zycia_prawego_karabinu=4;ilosc_zycia_lewego_karabinu=4;
            ilosc_zycia_oko=4;ilosc_zycia_lewe_ramie=4;
            migniecie_prawego_karabinu=false;migniecie_lewego_karabinu=false;
            migniecie_lewego_ramienia=false; migniecie_oka=false;
            jaki_otwor=0;migniecie_prawego_ramienia=false;
            rysowanie_ammo_bossa=false;
            poczatkowa_pozycja_creditsow=true;
            sZycie_Bossa.setScale(1,1);

            poczatkowe_miejsce_kuli=true;
            restart_pozycji_kuli=true;
            restart_rotacji_lufy=true;
            poczatkowa_pozycja_lufy=true;
            restart_pozycji_kuli_strzal=true;

            rotacja_ammo_mecha_1=0;rotacja_ammo_mecha_1_po_strzale=0;rotacja_ammo_mecha_2=-30;rotacja_ammo_mecha_2_po_strzale=-30;
            rotacja_ammo_mecha_3=-35;rotacja_ammo_mecha_3_po_strzale=-35; rotacja_ammo_mecha_4=0;rotacja_ammo_mecha_4_po_strzale=0;
            rotacja_ammo_mecha_5=-25;rotacja_ammo_mecha_5_po_strzale=-25;

            pozycja_ammo_mecha_1_y=0;pozycja_ammo_mecha_1_y_po_strzale=0;pozycja_ammo_mecha_2_y=0.07;pozycja_ammo_mecha_2_y_po_strzale=0.07;
            pozycja_ammo_mecha_3_y=0.07;pozycja_ammo_mecha_3_y_po_strzale=0.07;pozycja_ammo_mecha_4_y=0;pozycja_ammo_mecha_4_y_po_strzale=0;
            pozycja_ammo_mecha_5_y=0.04;pozycja_ammo_mecha_5_y_po_strzale=0.04;

            Sleep(50);

        }
        ////////////////////KONIEC RESTARTU/////////////////
        ////////////////////Wygrana////////////////////
        if (menu=="wygrana")
        {
           app.clear();

           if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 490 && Mouse::getPosition(app).y >= 560 &&
                    Mouse::getPosition(app).x <= 800 && Mouse::getPosition(app).y <= 640) {menu="restart"; menu_czy_restart=true;}

              else if (Mouse::getPosition(app).x >= 490 && Mouse::getPosition(app).y >= 560 &&
                       Mouse::getPosition(app).x <= 800 && Mouse::getPosition(app).y <= 640)
                       {
                           sWygrana.setTexture(wygrana_menu);
                           if (czy_zmiana_napisu==true)
                           {
                                sZmiana_Napisu.play();
                                czy_zmiana_napisu=false;
                           }
                           czy_muzyka=true;
                       }

          else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 990 && Mouse::getPosition(app).y >= 560 &&
                    Mouse::getPosition(app).x <= 1535 && Mouse::getPosition(app).y <= 640) {menu="restart"; level++; menu_czy_restart=false;}

              else if (Mouse::getPosition(app).x >= 990 && Mouse::getPosition(app).y >= 560 &&
                       Mouse::getPosition(app).x <= 1535 && Mouse::getPosition(app).y <= 640)
                       {
                           sWygrana.setTexture(wygrana_next);
                           if (czy_zmiana_napisu==true)
                           {
                            sZmiana_Napisu.play();
                            czy_zmiana_napisu=false;
                           }
                           czy_muzyka=true;
                       }

          else
          {
              sWygrana.setTexture(wygrana);
              if(czy_muzyka==true)
              {
                 sZmiana_Napisu.stop();
                 czy_muzyka=false;
                 czy_zmiana_napisu=true;
              }
          }

           app.draw(sWygrana);
        }
        if (menu=="przegrana")
        {
          app.clear();

          if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 490 && Mouse::getPosition(app).y >= 560 &&
                    Mouse::getPosition(app).x <= 800 && Mouse::getPosition(app).y <= 640) {menu="restart"; menu_czy_restart=true;}

              else if (Mouse::getPosition(app).x >= 490 && Mouse::getPosition(app).y >= 560 &&
                       Mouse::getPosition(app).x <= 800 && Mouse::getPosition(app).y <= 640)
                       {
                        sPrzegrana.setTexture(przegrana_menu);
                        if (czy_zmiana_napisu==true)
                           {
                            sZmiana_Napisu.play();
                            czy_zmiana_napisu=false;
                           }
                        czy_muzyka=true;
                       }

          else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 990 && Mouse::getPosition(app).y >= 560 &&
                    Mouse::getPosition(app).x <= 1535 && Mouse::getPosition(app).y <= 640) {menu="restart"; menu_czy_restart=false;}

              else if (Mouse::getPosition(app).x >= 990 && Mouse::getPosition(app).y >= 560 &&
                       Mouse::getPosition(app).x <= 1535 && Mouse::getPosition(app).y <= 640)
                       {
                           sPrzegrana.setTexture(przegrana_restart);
                           if (czy_zmiana_napisu==true)
                           {
                            sZmiana_Napisu.play();
                            czy_zmiana_napisu=false;
                           }
                           czy_muzyka=true;
                       }

          else
            {
             sPrzegrana.setTexture(przegrana);
             if(czy_muzyka==true)
             {
                 sZmiana_Napisu.stop();
                 czy_muzyka=false;
                 czy_zmiana_napisu=true;
             }
            }

          app.draw(sPrzegrana);
        }
        /////////////////KONIEC WYGRANEJ///////////////
        ////////////////////Ustawienia/////////////////
        if (menu=="levels")
        {
            app.clear();
            app.draw(sChange_level);
            Vector2i pozycja_kursora=Mouse::getPosition(app);

            if (Keyboard::isKeyPressed(Keyboard::Escape)) menu="menu";

            if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 200 && Mouse::getPosition(app).y >= 100 && Mouse::getPosition(app).x <= 550 && Mouse::getPosition(app).y <= 450)
            {
                level=1; menu="start";
            }
               else if (Mouse::getPosition(app).x >= 200 && Mouse::getPosition(app).y >= 100 && Mouse::getPosition(app).x <= 550 && Mouse::getPosition(app).y <= 450)
               {
                 sChange_level.setTexture(change_level_1);
                 sOpisLevelu.setTexture(opis_level_1);
                 sOpisLevelu.setPosition(pozycja_kursora.x,pozycja_kursora.y);
                 app.draw(sOpisLevelu);
                 if (czy_zmiana_napisu==true)
                 {
                   sZmiana_Napisu.play();
                   czy_zmiana_napisu=false;
                 }
                 czy_muzyka=true;
               }
            else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 790 && Mouse::getPosition(app).y >= 100 && Mouse::getPosition(app).x <= 1140 && Mouse::getPosition(app).y <= 450)
            {
                level=2; menu="start";
            }
                else if (Mouse::getPosition(app).x >= 790 && Mouse::getPosition(app).y >= 100 && Mouse::getPosition(app).x <= 1140 && Mouse::getPosition(app).y <= 450)
                {
                  sChange_level.setTexture(change_level_2);
                  sOpisLevelu.setTexture(opis_level_2);
                  sOpisLevelu.setPosition(pozycja_kursora.x,pozycja_kursora.y);
                  app.draw(sOpisLevelu);
                  if (czy_zmiana_napisu==true)
                  {
                   sZmiana_Napisu.play();
                   czy_zmiana_napisu=false;
                  }
                  czy_muzyka=true;
                }
            else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 1370 && Mouse::getPosition(app).y >= 100 && Mouse::getPosition(app).x <= 1720 && Mouse::getPosition(app).y <= 450)
            {
                level=3; menu="start";
            }
                else if (Mouse::getPosition(app).x >= 1370 && Mouse::getPosition(app).y >= 100 && Mouse::getPosition(app).x <= 1720 && Mouse::getPosition(app).y <= 450)
                {
                    sChange_level.setTexture(change_level_3);
                    sOpisLevelu.setTexture(opis_level_3);
                    sOpisLevelu.setPosition(pozycja_kursora.x,pozycja_kursora.y);
                    app.draw(sOpisLevelu);
                    if (czy_zmiana_napisu==true)
                    {
                     sZmiana_Napisu.play();
                     czy_zmiana_napisu=false;
                    }
                    czy_muzyka=true;
                }
            else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 200 && Mouse::getPosition(app).y >= 630 && Mouse::getPosition(app).x <= 550 && Mouse::getPosition(app).y <= 980)
            {
                level=4; menu="start";
            }
                else if (Mouse::getPosition(app).x >= 200 && Mouse::getPosition(app).y >= 630 && Mouse::getPosition(app).x <= 550 && Mouse::getPosition(app).y <= 980)
                {
                    sChange_level.setTexture(change_level_4);
                    sOpisLevelu.setTexture(opis_level_4);
                    sOpisLevelu.setPosition(pozycja_kursora.x,pozycja_kursora.y);
                    app.draw(sOpisLevelu);
                    if (czy_zmiana_napisu==true)
                    {
                     sZmiana_Napisu.play();
                     czy_zmiana_napisu=false;
                    }
                    czy_muzyka=true;
                }
            else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 790 && Mouse::getPosition(app).y >= 630 && Mouse::getPosition(app).x <= 1140 && Mouse::getPosition(app).y <= 980)
            {
                level=5; menu="start";
            }
                else if (Mouse::getPosition(app).x >= 790 && Mouse::getPosition(app).y >= 630 && Mouse::getPosition(app).x <= 1140 && Mouse::getPosition(app).y <= 980)
                {
                    sChange_level.setTexture(change_level_5);
                    sOpisLevelu.setTexture(opis_level_5);
                    sOpisLevelu.setPosition(pozycja_kursora.x,pozycja_kursora.y);
                    app.draw(sOpisLevelu);
                    if (czy_zmiana_napisu==true)
                    {
                        sZmiana_Napisu.play();
                        czy_zmiana_napisu=false;
                    }
                    czy_muzyka=true;
                }
            else if (Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(app).x >= 1370 && Mouse::getPosition(app).y >= 630 && Mouse::getPosition(app).x <= 1720 && Mouse::getPosition(app).y <= 980)
            {
                level=6; menu="start";
            }
                else if (Mouse::getPosition(app).x >= 1370 && Mouse::getPosition(app).y >= 630 && Mouse::getPosition(app).x <= 1720 && Mouse::getPosition(app).y <= 980)
                {
                    sChange_level.setTexture(change_level_6);
                    sOpisLevelu.setTexture(opis_level_6);
                    sOpisLevelu.setPosition(pozycja_kursora.x,pozycja_kursora.y);
                    app.draw(sOpisLevelu);
                    if (czy_zmiana_napisu==true)
                    {
                        sZmiana_Napisu.play();
                        czy_zmiana_napisu=false;
                    }
                    czy_muzyka=true;
                }
            else
            {
                sChange_level.setTexture(change_level);
                if(czy_muzyka==true)
                {
                     sZmiana_Napisu.stop();
                     czy_muzyka=false;
                     czy_zmiana_napisu=true;
                }
            }
        }

        if (menu=="settings")
        {
            app.clear();
            Color szary(127, 127, 127);
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {menu="menu";Sleep(200);}

            Vector2i pozycja_kursora=Mouse::getPosition();


            if (Mouse::getPosition(app).x >= 470 && Mouse::getPosition(app).y >= 345 && Mouse::getPosition(app).x <= 1545 && Mouse::getPosition(app).y <= 470)
            {
                sSettings.setTexture(settings_music);
                if (czy_zmiana_napisu==true)
                {
                    sZmiana_Napisu.play();
                    czy_zmiana_napisu=false;
                }
                czy_muzyka=true;

                rysowanie_wlaczonej_muzyki=true;
                rysowanie_strzalki_muzyki=false;
                rysowanie_wlaczonego_dzwieku=false;
                rysowanie_strzalki_dzwiekow=false;

                if (Wlaczona_Muzyka=="ON") tWlaczona_Muzyka.setPosition(1370,335);
                else if (Wlaczona_Muzyka=="OFF") tWlaczona_Muzyka.setPosition(1320,335);
                tWlaczona_Muzyka.setFont(font);  tWlaczona_Muzyka.setCharacterSize(120);


                if (Mouse::isButtonPressed(Mouse::Left) && pozycja_kursora.x >= pozycja_x && pozycja_kursora.y >= 335 && pozycja_kursora.x <= 1536 && pozycja_kursora.y <= 455)
                {
                   if (Wlaczona_Muzyka=="ON")
                    {
                            Wlaczona_Muzyka="OFF";
                            pozycja_x=1320;
                            muzyka_bossa.setVolume(0);
                            muzyka_podczas_grania.setVolume(0);
                            muzyka_z_menu.stop();

                    }
                   else if (Wlaczona_Muzyka=="OFF")
                    {
                        Wlaczona_Muzyka="ON";
                        pozycja_x=1370;
                        muzyka_bossa.setVolume(glosnosc_muzyki);
                        muzyka_podczas_grania.setVolume(glosnosc_muzyki);
                        muzyka_z_menu.play();
                        muzyka_z_menu.setVolume(glosnosc_muzyki);
                    }
                   tWlaczona_Muzyka.setString(Wlaczona_Muzyka);
                   Sleep(100);
                }
                else if(pozycja_kursora.x >= pozycja_x && pozycja_kursora.y >= 335 && pozycja_kursora.x <= 1536 && pozycja_kursora.y <= 455) tWlaczona_Muzyka.setColor(Color::White);

                else
                    {
                        tWlaczona_Muzyka.setColor(szary);
                        tWlaczona_Muzyka.setString(Wlaczona_Muzyka);
                    }
            }
            else if (Mouse::getPosition(app).x >= 470 && Mouse::getPosition(app).y >= 490 && Mouse::getPosition(app).x <= 1545 && Mouse::getPosition(app).y <= 600)
            {
              sSettings.setTexture(settings_musicvolume);
              if (czy_zmiana_napisu==true)
              {
                    sZmiana_Napisu.play();
                    czy_zmiana_napisu=false;
              }
              czy_muzyka=true;

              rysowanie_strzalki_muzyki=true;
              rysowanie_wlaczonego_dzwieku=false;
              rysowanie_wlaczonej_muzyki=false;
              rysowanie_strzalki_dzwiekow=false;

              sStrzalki.setPosition(1470,493);

              stringstream glosnosc_muzyki_ss;  glosnosc_muzyki_ss<<glosnosc_muzyki; glosnosc_muzyki_ss>>sGlosnosc_muzyki;
              tGlosnosc_muzyki.setFont(font);  tGlosnosc_muzyki.setString(sGlosnosc_muzyki);

              if (glosnosc_muzyki >= 100) tGlosnosc_muzyki.setPosition(1260,460);
              else if (glosnosc_muzyki < 10) tGlosnosc_muzyki.setPosition(1400,460);
              else tGlosnosc_muzyki.setPosition(1330,460);

              tGlosnosc_muzyki.setCharacterSize(120); tGlosnosc_muzyki.setFillColor(szary);

                if (Mouse::isButtonPressed(Mouse::Left) && pozycja_kursora.x >= 1470 && pozycja_kursora.y >= 493 && pozycja_kursora.x <= 1526 && pozycja_kursora.y <= 538)
                {
                   glosnosc_muzyki=glosnosc_muzyki+1;
                   Sleep(75);

                   muzyka_bossa.setVolume(glosnosc_muzyki);
                   muzyka_podczas_grania.setVolume(glosnosc_muzyki);
                   muzyka_z_menu.setVolume(glosnosc_muzyki);

                   if (glosnosc_muzyki >= 100) glosnosc_muzyki=100;
                }
                else if(pozycja_kursora.x >= 1470 && pozycja_kursora.y >= 493 && pozycja_kursora.x <= 1526 && pozycja_kursora.y <= 538) sStrzalki.setTexture(strzalka_w_gore);

                else if (Mouse::isButtonPressed(Mouse::Left) && pozycja_kursora.x >= 1470 && pozycja_kursora.y >= 543 && pozycja_kursora.x <= 1526 && pozycja_kursora.y <= 588)
                {
                  glosnosc_muzyki=glosnosc_muzyki-1;
                   Sleep(75);
                   muzyka_bossa.setVolume(glosnosc_muzyki);
                   muzyka_podczas_grania.setVolume(glosnosc_muzyki);
                   muzyka_z_menu.setVolume(glosnosc_muzyki);

                   if (glosnosc_muzyki <= 0) glosnosc_muzyki=0;
                }
                else if (pozycja_kursora.x >= 1470 && pozycja_kursora.y >= 543 && pozycja_kursora.x <= 1526 && pozycja_kursora.y <= 588) sStrzalki.setTexture(strzalka_w_dol);

                else sStrzalki.setTexture(strzalki);

            }
            else if (Mouse::getPosition(app).x >= 470 && Mouse::getPosition(app).y >= 600 && Mouse::getPosition(app).x <= 1545 && Mouse::getPosition(app).y <= 720)
            {
               sSettings.setTexture(settings_sounds);
               if (czy_zmiana_napisu==true)
               {
                    sZmiana_Napisu.play();
                    czy_zmiana_napisu=false;
               }
               czy_muzyka=true;

                rysowanie_wlaczonego_dzwieku=true;
                rysowanie_wlaczonej_muzyki=false;
                rysowanie_strzalki_muzyki=false;
                rysowanie_strzalki_dzwiekow=false;

                if (Wlaczony_Dzwiek=="ON") tWlaczony_Dzwiek.setPosition(1370,580);
                else if (Wlaczony_Dzwiek=="OFF") tWlaczony_Dzwiek.setPosition(1320,580);
                tWlaczony_Dzwiek.setFont(font);  tWlaczony_Dzwiek.setCharacterSize(120);


                if (Mouse::isButtonPressed(Mouse::Left) && pozycja_kursora.x >= pozycja_x && pozycja_kursora.y >= 605 && pozycja_kursora.x <= 1536 && pozycja_kursora.y <= 715)
                {
                   if (Wlaczony_Dzwiek=="ON")
                    {
                            Wlaczony_Dzwiek="OFF";
                            pozycja_x=1320;

                            sZmiana_Napisu.setVolume(0);
                            sPrzegrana_dzwiek.setVolume(0);
                            sWygrana_dzwiek.setVolume(0);
                            sStrzal_czolgu.setVolume(0);
                            sStrzal_Mecha.setVolume(0);
                            sPrzeladowanie.setVolume(0);
                            sWybuch.setVolume(0);

                    }
                   else if (Wlaczony_Dzwiek=="OFF")
                    {
                        Wlaczony_Dzwiek="ON";
                        pozycja_x=1370;

                        sZmiana_Napisu.setVolume(glosnosc_dzwiekow);
                        sPrzegrana_dzwiek.setVolume(glosnosc_dzwiekow);
                        sWygrana_dzwiek.setVolume(glosnosc_dzwiekow);
                        sStrzal_czolgu.setVolume(glosnosc_dzwiekow);
                        sStrzal_Mecha.setVolume(glosnosc_dzwiekow);
                        sPrzeladowanie.setVolume(glosnosc_dzwiekow);
                        sWybuch.setVolume(glosnosc_dzwiekow);
                    }
                   tWlaczony_Dzwiek.setString(Wlaczony_Dzwiek);
                   Sleep(100);
                }
                else if(pozycja_kursora.x >= pozycja_x && pozycja_kursora.y >= 610 && pozycja_kursora.x <= 1536 && pozycja_kursora.y <= 710) tWlaczony_Dzwiek.setColor(Color::White);

                else
                    {
                        tWlaczony_Dzwiek.setColor(szary);
                        tWlaczony_Dzwiek.setString(Wlaczony_Dzwiek);
                    }
            }
            else if (Mouse::getPosition(app).x >= 470 && Mouse::getPosition(app).y >= 730 && Mouse::getPosition(app).x <= 1545 && Mouse::getPosition(app).y <= 845)
            {
               sSettings.setTexture(settings_soundsvolume);
               if (czy_zmiana_napisu==true)
               {
                   sZmiana_Napisu.play();
                   czy_zmiana_napisu=false;
               }
               czy_muzyka=true;

              rysowanie_strzalki_muzyki=false;
              rysowanie_strzalki_dzwiekow=true;
              rysowanie_wlaczonego_dzwieku=false;
              rysowanie_wlaczonej_muzyki=false;

              sStrzalki.setPosition(1470,737);

              stringstream glosnosc_dzwiekow_ss;  glosnosc_dzwiekow_ss<<glosnosc_dzwiekow; glosnosc_dzwiekow_ss>>sGlosnosc_dzwiekow;
              tGlosnosc_dzwiekow.setFont(font);  tGlosnosc_dzwiekow.setString(sGlosnosc_dzwiekow);

              if (glosnosc_dzwiekow >= 100) tGlosnosc_dzwiekow.setPosition(1260,705);
              else if (glosnosc_dzwiekow < 10) tGlosnosc_dzwiekow.setPosition(1400,705);
              else tGlosnosc_dzwiekow.setPosition(1330,705);

              tGlosnosc_dzwiekow.setCharacterSize(120); tGlosnosc_dzwiekow.setFillColor(szary);

                if (Mouse::isButtonPressed(Mouse::Left) && pozycja_kursora.x >= 1470 && pozycja_kursora.y >= 733 && pozycja_kursora.x <= 1526 && pozycja_kursora.y <= 779)
                {
                   glosnosc_dzwiekow=glosnosc_dzwiekow+1;
                   Sleep(75);

                    sZmiana_Napisu.setVolume(glosnosc_dzwiekow);
                    sPrzegrana_dzwiek.setVolume(glosnosc_dzwiekow);
                    sWygrana_dzwiek.setVolume(glosnosc_dzwiekow);
                    sStrzal_czolgu.setVolume(glosnosc_dzwiekow);
                    sStrzal_Mecha.setVolume(glosnosc_dzwiekow);
                    sPrzeladowanie.setVolume(glosnosc_dzwiekow);
                    sWybuch.setVolume(glosnosc_dzwiekow);

                   if (glosnosc_dzwiekow >= 100) glosnosc_dzwiekow=100;
                }
                else if(pozycja_kursora.x >= 1470 && pozycja_kursora.y >= 733 && pozycja_kursora.x <= 1526 && pozycja_kursora.y <= 779) sStrzalki.setTexture(strzalka_w_gore);

                else if (Mouse::isButtonPressed(Mouse::Left) && pozycja_kursora.x >= 1470 && pozycja_kursora.y >= 784 && pozycja_kursora.x <= 1526 && pozycja_kursora.y <= 830)
                {
                  glosnosc_dzwiekow=glosnosc_dzwiekow-1;
                   Sleep(75);

                    sZmiana_Napisu.setVolume(glosnosc_dzwiekow);
                    sPrzegrana_dzwiek.setVolume(glosnosc_dzwiekow);
                    sWygrana_dzwiek.setVolume(glosnosc_dzwiekow);
                    sStrzal_czolgu.setVolume(glosnosc_dzwiekow);
                    sStrzal_Mecha.setVolume(glosnosc_dzwiekow);
                    sPrzeladowanie.setVolume(glosnosc_dzwiekow);
                    sWybuch.setVolume(glosnosc_dzwiekow);

                   if (glosnosc_dzwiekow <= 0) glosnosc_dzwiekow=0;
                }
                else if (pozycja_kursora.x >= 1470 && pozycja_kursora.y >= 784 && pozycja_kursora.x <= 1526 && pozycja_kursora.y <= 830) sStrzalki.setTexture(strzalka_w_dol);

                else sStrzalki.setTexture(strzalki);
            }
            else if(Mouse::getPosition(app).x >= 565 && Mouse::getPosition(app).y >= 875 && Mouse::getPosition(app).x <= 1190 && Mouse::getPosition(app).y <= 1112)
            {
               sDelete.setTexture(delete_save_big);
               big_delete_save=true;
            }

            else
            {
                sSettings.setTexture(settings);
                sDelete.setTexture(delete_save);
                big_delete_save=false;
                if(czy_muzyka==true)
                {
                     sZmiana_Napisu.stop();
                     czy_muzyka=false;
                     czy_zmiana_napisu=true;
                }
                rysowanie_strzalki_muzyki=false;
                rysowanie_wlaczonej_muzyki=false;
                rysowanie_wlaczonego_dzwieku=false;
                rysowanie_strzalki_dzwiekow=false;
            }

            if(big_delete_save == false) {sDelete.setPosition(565, 875); }
            if(big_delete_save == true) {sDelete.setPosition(520, 865);}
            app.draw(sSettings);
            app.draw(sDelete);

            if (rysowanie_strzalki_muzyki==true) {app.draw(sStrzalki); app.draw(tGlosnosc_muzyki);}
            if (rysowanie_wlaczonej_muzyki==true) app.draw(tWlaczona_Muzyka);
            if (rysowanie_wlaczonego_dzwieku==true) app.draw(tWlaczony_Dzwiek);
            if (rysowanie_strzalki_dzwiekow==true) {app.draw(sStrzalki); app.draw(tGlosnosc_dzwiekow);}
        }

      app.display();
 }

  return 0;
}
