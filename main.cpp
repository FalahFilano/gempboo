#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <cstring>
#include <sstream>

#include "SoundTetris.h"
#include "mainmenu.h"
#include "PauseMenu.h"
#include "EndMenu.h"

using namespace sf;
using namespace std;

int MainMenuFunction();
int PauseMenuFunction();
int GameOverFunction();
int GameIn();

const int M=25;
const int N=15;

int field[M][N]={0};

struct point{
    int x, y;
} a[4],b[4];

int figures[7][4]={
    1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

bool check()            //mengecek batas
{
   for (int i=0;i<4;i++)
	  if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
      else if (field[a[i].y][a[i].x]) return 0;

   return 1;
};


int main(){

    //srand(time(0));

    if(MainMenuFunction()==0) return 0;
    GameIn();

	/*RenderWindow window(VideoMode(480, 600), "The Game!");

    Texture t1,t2,t3;
	t1.loadFromFile("images/tiles.png");
	//t2.loadFromFile("images/background.png");
	t3.loadFromFile("images/frame2.png");

	Sprite s(t1);
	Sprite background(t2);
    Sprite frame(t3);

    Font font;
    font.loadFromFile("Geforce Bold.ttf");

    Text scoretext;
    scoretext.setFillColor(Color::White);
    scoretext.setPosition(140, 510);
    scoretext.setCharacterSize(24);
    scoretext.setFont(font);

    int dx=0;
    int score=0;
    bool rotate=false, pause=false;
    int colorNum=1;
	float timer=0,delay=0.3;

	ostringstream scorestring;
    scorestring <<"Score: "<<score;
    scoretext.setString(scorestring.str());

	Clock clock;

    while (window.isOpen())
    {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;

		for (int i=0;i<4;i++) if (field[a[i].y][a[i].x]){       //cek batas / gameover
            field[M][N] = {0};
            //musics.stop();
            window.close();
            cout << "Game Over" << endl;
            GameOverFunction();
            break;
		};

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

			if (e.type == Event::KeyPressed)
			  if (e.key.code==Keyboard::Up) rotate=true;
			  else if (e.key.code==Keyboard::Left) dx=-1;
			  else if (e.key.code==Keyboard::Right) dx=1;
			  else if (e.key.code==Keyboard::Down) delay=0.01;
			  else if (e.key.code==Keyboard::Escape){
                    pause=true;
                    PauseMenuFunction();
                    pause=false;
			  }
		}

        //// <- Move -> ///
        if (check()){               //jika dicek tidak ada yang salah (return 1)
            for (int i=0;i<4;i++){
                b[i]=a[i];
                a[i].x+=dx;
            }
        }else{                      //jika dicek ada salah (return 0)
            for (int i=0;i<4;i++) a[i]=b[i];
            cout<<"move: batas"<<endl;
        }

	//////Rotate//////
        if (rotate){
            if (check()){
                cout<<"rotate"<<endl;
                point p = a[2];     //center of rotation
                for (int i=0;i<4;i++){
                    int x = a[i].y-p.y;
                    int y = a[i].x-p.x;
                    a[i].x = p.x - x;
                    a[i].y = p.y + y;
                    printf("x[%d] %d\ty[%d] %d\n", i, a[i].x, i, a[i].y);
                }
            }else{
                for (int i=0;i<4;i++) a[i]=b[i];
                cout<<"rotate: batas"<<endl;
            }
        }


	///////Tick//////
	if (timer>delay)
	  {
        //printf("timer %d delay %d\n",timer, delay);
	    if(!pause) for (int i=0;i<4;i++){
            b[i]=a[i];
            a[i].y+=1;
        }

		if (!check())
		{
		 for (int i=0;i<4;i++){
            field[b[i].y][b[i].x]=colorNum;
            //cout<< field[b[i].y][b[i].x]<<endl;
		 }

		 colorNum=1+rand()%7;
		 int n=rand()%7;
		 cout<<"Object Keluar"<<endl;

		 for (int i=0;i<4;i++)
		   {
		    a[i].x = figures[n][i] % 2;         //mengconvert posisi figures ke koordinat x
		    a[i].y = figures[n][i] / 2;         //mengconvert posisi figures ke koordinat y
		    //cout<<"a.x "<<a[i].x<<endl;
		    //cout<<"a.y "<<a[i].y<<endl;
		   }
		}

	  	timer=0;
	  }

	///////check lines//////////
    int k=M-1;
	for (int i=M-1;i>0;i--)
	{
		int count=0;
		for (int j=0;j<N;j++)
		{
		    if (field[i][j]) count++;
		    field[k][j]=field[i][j];
		}
		if (count<N) k--;
		else{
            score++;
            cout<<"score "<<score<<endl;
            scorestring.str("");
            scorestring <<"Score: "<<score;
            scoretext.setString(scorestring.str());
		}
	}

    dx=0; rotate=0; delay=0.3;

    /////////draw//////////

    window.clear(Color::White);
    window.draw(background);

	for (int i=0;i<M;i++)
    for (int j=0;j<N;j++){
        if (field[i][j]==0) continue;
        s.setTextureRect(IntRect(field[i][j]*18,0,18,18));
        s.setPosition(j*18,i*18);
        s.move(28,31); //offset
        window.draw(s);
	   }

	for (int i=0;i<4;i++)
	  {
		s.setTextureRect(IntRect(colorNum*18,0,18,18));
		s.setPosition(a[i].x*18,a[i].y*18);
		s.move(28,31); //offset
		window.draw(s);
	  }

	window.draw(frame);
	window.draw(scoretext);
 	window.display();
	}*/

    return 0;
}

int GameIn()
{
    //srand(time(0));

    //if(MainMenuFunction()==0) return 0;

	RenderWindow window(VideoMode(480, 600), "The Game!");

    Texture t1,t2,t3;
	t1.loadFromFile("images/tiles.png");
	//t2.loadFromFile("images/background.png");
	//t3.loadFromFile("images/frame.png");

	Sprite s(t1);
	Sprite background(t2);
    Sprite frame(t3);

    int dx=0;
    int score=0;
    bool rotate=false, pause=false;
    int colorNum=1;
	float timer=0,delay=0.3;

	Clock clock;

    while (window.isOpen())
    {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;

		for (int i=0;i<4;i++) if (field[a[i].y][a[i].x]){       //cek batas / gameover
           for(int j=0;j<=M;j++) for(int k=0;k<=N;k++)
            field[j][k] = {0};
            window.clear();
            window.close();
            cout << "Game Over" << endl;
            if(GameOverFunction() == 0) return 0;
            break;
		};

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

			if (e.type == Event::KeyPressed)
			  if (e.key.code==Keyboard::Up) rotate=true;
			  else if (e.key.code==Keyboard::Left) dx=-1;
			  else if (e.key.code==Keyboard::Right) dx=1;
			  else if (e.key.code==Keyboard::Down) delay=0.01;
			  else if (e.key.code==Keyboard::Escape){
                    pause=true;
                    PauseMenuFunction();
                    pause=false;
			  }
		}

        //// <- Move -> ///
        if (check()){               //jika dicek tidak ada yang salah (return 1)
            for (int i=0;i<4;i++){
                b[i]=a[i];
                a[i].x+=dx;
            }
        }else{                      //jika dicek ada salah (return 0)
            for (int i=0;i<4;i++) a[i]=b[i];
            cout<<"move: batas"<<endl;
        }

	//////Rotate//////
        if (rotate){
            if (check()){
                cout<<"rotate"<<endl;
                point p = a[2];     //center of rotation
                for (int i=0;i<4;i++){
                    int x = a[i].y-p.y;
                    int y = a[i].x-p.x;
                    a[i].x = p.x - x;
                    a[i].y = p.y + y;
                    printf("x[%d] %d\ty[%d] %d\n", i, a[i].x, i, a[i].y);
                }
            }else{
                for (int i=0;i<4;i++) a[i]=b[i];
                cout<<"rotate: batas"<<endl;
            }
        }


	///////Tick//////
	if (timer>delay)
	  {
        //printf("timer %d delay %d\n",timer, delay);
	    if(!pause) for (int i=0;i<4;i++){
            b[i]=a[i];
            a[i].y+=1;
        }

		if (!check())
		{
		 for (int i=0;i<4;i++){
            field[b[i].y][b[i].x]=colorNum;
            //cout<< field[b[i].y][b[i].x]<<endl;
		 }

		 colorNum=1+rand()%7;
		 int n=rand()%7;
		 cout<<"Object Keluar"<<endl;

		 for (int i=0;i<4;i++)
		   {
		    a[i].x = figures[n][i] % 2;         //mengconvert posisi figures ke koordinat x
		    a[i].y = figures[n][i] / 2;         //mengconvert posisi figures ke koordinat y
		    //cout<<"a.x "<<a[i].x<<endl;
		    //cout<<"a.y "<<a[i].y<<endl;
		   }
		}

	  	timer=0;
	  }

	///////check lines//////////
    int k=M-1;
	for (int i=M-1;i>0;i--)
	{
		int count=0;
		for (int j=0;j<N;j++)
		{
		    if (field[i][j]) count++;
		    field[k][j]=field[i][j];
		}
		if (count<N) k--;
		else{
            score++;
            cout<<"score "<<score<<endl;
		}
	}

    dx=0; rotate=0; delay=0.3;

    /////////draw//////////
    window.clear(Color::White);
    window.draw(background);

	for (int i=0;i<M;i++)
    for (int j=0;j<N;j++){
        if (field[i][j]==0) continue;
        s.setTextureRect(IntRect(field[i][j]*18,0,18,18));
        s.setPosition(j*18,i*18);
        s.move(28,31); //offset
        window.draw(s);
	   }

	for (int i=0;i<4;i++)
	  {
		s.setTextureRect(IntRect(colorNum*18,0,18,18));
		s.setPosition(a[i].x*18,a[i].y*18);
		s.move(28,31); //offset
		window.draw(s);
	  }

	window.draw(frame);
 	window.display();
	}

    return 0;
}

int MainMenuFunction()
{
	sf::RenderWindow window(sf::VideoMode(480, 600), "TETRYSSS !!!");
	MainMenu menu(window.getSize().x, window.getSize().y);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
					    cout<<"Play"<<endl;
                        window.clear();
						window.close();
						return 1;
						break;
					case 1:
					    cout<<"keluar"<<endl;
                        window.clear();
						window.close();
						return 0;
						break;
					}

					break;
				}

				break;
                case sf::Event::Closed:
				window.close();

				break;
			}
		}

		window.clear();
		menu.draw(window);
		window.display();
	}
}

int PauseMenuFunction()
{
    sf::RenderWindow window(sf::VideoMode(480, 600), "PAUSE");
	PauseMenu pause(window.getSize().x, window.getSize().y);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					pause.MoveUp1();
					break;
<<<<<<< HEAD
=======

>>>>>>> 308ae492283ad5d2963ed4b6d1cd6b7628bc67f5
				case sf::Keyboard::Down:
					pause.MoveDown1();
					break;

				case sf::Keyboard::Return:
					switch (pause.GetPressedItem1())
					{
					case 0:
					    cout<<"Resume"<<endl;
                        window.clear();
						window.close();
						return 1;
						//break;
					case 1:
					    cout<<"Restart"<<endl;
                        window.clear();
						window.close();
						GameIn();
						break;
					}

					break;
				}

				break;
                case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();
		pause.draw1(window);
		window.display();
	}
}

int GameOverFunction()
{
    sf::RenderWindow window(sf::VideoMode(480, 600), "GAME OVER");
	EndMenu gameover(window.getSize().x, window.getSize().y);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					gameover.MoveUp2();
					break;

				case sf::Keyboard::Down:
					gameover.MoveDown2();
					break;

				case sf::Keyboard::Return:
					switch (gameover.GetPressedItem2())
					{
					case 0:
					    cout<<"Restart"<<endl;
                        window.clear();
						window.close();
						GameIn();
						break;
						//break;
					case 1:
					    cout<<"keluar"<<endl;
                        window.clear();
						window.close();
						return 0;
						break;
					}

					break;
				}

				break;
                case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();
		gameover.draw2(window);
		window.display();
	}
}





