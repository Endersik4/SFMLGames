#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <windows.h>

using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = {0};

struct Point    // wspó³rzêdne figur X i Y
{int x,y;} a[4], b[4];

int figures[7][4] =  // pierwsza tablica oznacza ile figur jest a 4 ile wspolrzednych jest
{
    1,3,5,7, // I
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

bool check()
{
    for (int i=0; i<4; i++)
        if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
        else if (field[a[i].y][a[i].x]) return 0;

        return 1;
};



int main()
{
    sf::Music music;
    music.openFromFile("music/tetris.flac");

    srand(time(0));

    RenderWindow window(VideoMode(540, 990), "Tetris!");

    Texture t,t1,t2;
    t.loadFromFile("Images/tiles.png");
    t1.loadFromFile("Images/background.png");

    Sprite s(t),s1(t1);



    int dx=0; bool rotate=0; int colorNum=1;
    float timer=0, delay=0.4;

    Clock clock;

    music.setVolume(20.f);
    music.play();

    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asSeconds();

        clock.restart();
        timer+=time;


        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed)
              if (e.key.code==Keyboard::Up) rotate=true;
              else if (e.key.code==Keyboard::Left) dx=-1;
              else if (e.key.code==Keyboard::Right) dx=1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;
        //// <- Ruch -> ////
        for (int i=0; i<4; i++) {b[i]=a[i]; a[i].x+=dx;}
        if (!check()) for (int i=0; i<4; i++) a[i]=b[i];
        ////Rotate////
        if (rotate)
        {
            Point p = a[1]; //centrum rotacji
            for (int i=0; i<4; i++)
            {
                int x = a[i].y-p.y;
                int y = a[i].x-p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if (!check()) for (int i=0; i<4; i++) a[i]=b[i];
        }

        /////Tick/////
        if (timer>delay)
        {
            for (int i=0;i<4;i++) { b[i]=a[i]; a[i].y+=1; }

            if (!check())
            {
              for (int i=0; i<4; i++) field[b[i].y][b[i].x]=colorNum;

              colorNum=1+rand()%7;
              int n=rand()%7;
              for (int i=0; i<4; i++)
              {
                  a[i].x = figures[n][i] % 2;
                  a[i].y = figures[n][i] / 2;
              }
            }

            timer=0;
        }

        //////sprawdza czy jest linia z figur///////
        int k=M-1;
        for (int i=M-1; i>0; i--)
        {
            int count=0;
            for (int j=0; j<N; j++)
            {
                if (field[i][j]) count++;
                if (field[1][j])
                {
                Sleep(3000);

                 return 0;
                }
                field[k][j]=field[i][j];
            }
            if (count<N) k--;
        }


        dx=0; rotate=0; delay=0.4;

//////////////draw///////////////

        window.clear(Color::White);
        window.draw(s1);
        for (int i=0; i<M; i++)
            for(int j=0; j<N; j++)
        {
            if (field[i][j]==0) continue;
            s.setTextureRect(IntRect(field[i][j]*45,0,45,45));
            s.setPosition(j*45,i*45);
            s.move(44.5,44.5); //cos tam
            window.draw(s);
        }

        for (int i=0; i<4; i++)
        {
            s.setTextureRect(IntRect(colorNum*45,0,45,45));
            s.setPosition(a[i].x*45,a[i].y*45);
            s.move(44.5,44.5);
            window.draw(s);
        }
        window.display();
    }
    return 0;
}

