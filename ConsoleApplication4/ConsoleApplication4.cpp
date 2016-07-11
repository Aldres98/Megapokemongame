#include "stdafx.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
using std::stringstream;
//del console
//#include <iostream>

using namespace sf;

//del console
//using namespace std; 
//commads cin, cout ^|^




float setX = 0, setY = 0;//���������� ����������
float mapX = 0, mapY = 0;//���������� �����/������

int w = 600; int h = 800;

class wall {
public:
	float x, y;
	float lh, lw;
	Sprite sprite;

	void set(Texture &image, float sx, float sy, float slh, float slw)
	{
		sprite.setTexture(image);
		x = sx; y = sy; lh = slh; lw = slw;

	}

	void update()
	{
		/*if (setX + p.lw<x&&x + lw<setX)
		{


		}
		if (setY + p.lh<y&&y + lh<setY)
		{


		}*/

		sprite.setTextureRect(IntRect(0, 0, lw, lh));
		//sprite.setScale(1, 1);//������
		sprite.setPosition(x - mapX, y - mapY);



	}





};


//������� ������
class PLAYER {

public:

	float dx, dy;//dif coord
	

	float speed = 0.03;//speed of dif coord
	Sprite sprite;
	float currentFrame;
	float lh = 89, lw = 66.5;//������ ����� �������

	void set(Texture &image)
	{
		sprite.setTexture(image);//������� �������� � ������
		dx = dy = 0.01;//��������� ����������� � ��������
		currentFrame = 0;//��� �����
	}


	void update(float time)
	{

		setX += dx; setY -= dy;//��������� ���������� ���������� ���������

							   //���� ��������� �����
		if (mapX < 3303 - h && setX - mapX > 550)mapX += speed;
		if (mapX > 0 && setX - mapX < 250)mapX -= speed;
		if (mapY < 1554 - w && setY - mapY>400)mapY += speed;
		if (mapY>0 && setY - mapY<200)mapY -= speed;


		//���� ������ �����
		if (setX< 0)setX += speed;
		if (setY + lh / 2 < 0)setY += speed;
		if (setX>3303 - lw)setX -= speed;
		if (setY>1554 - lh)setY -= speed;

		//���� ��������� � ���������
		currentFrame += 0.0001*time;
		if (currentFrame > 8) currentFrame -= 8;
		if (dy>0) sprite.setTextureRect(IntRect(lw * int(currentFrame), lh, lw, lh));//������������ �������� setTextureRect(����� �, ����� �, ����� �, ����� �)
		if (dy<0) sprite.setTextureRect(IntRect(lw * int(currentFrame), 0 * lh, lw, lh));
		if (dx<0) sprite.setTextureRect(IntRect(lw * int(currentFrame), lh * 2, lw, lh));
		if (dx>0) sprite.setTextureRect(IntRect(lw * int(currentFrame), lh * 3, lw, lh));

		//sprite.setScale(1, 1);//������
		sprite.setPosition(setX - mapX, setY - mapY);//������� ������� �� ����������


		dx = 0; dy = 0;
	}

};



PLAYER p;//�������� �����

		 //������� �������� �����
void keyboardFUNK()
{

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		p.dx -= p.speed;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		p.dx += p.speed;
	}

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		p.dy += p.speed;
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		p.dy -= p.speed;
	}

}



void main()
{


	RenderWindow window(VideoMode(h, w), "Test!");//������

	Texture pl;//��������� ������ ��� ��������
	pl.loadFromFile("C:\\Users\\Aldres\\Documents\\Visual Studio 2015\\Projects\\ConsoleApplication4\\ConsoleApplication4\\images\\1.png");//�������� ��������

	p.set(pl);

	Texture map;//��������� ������ ��� ��������
	map.loadFromFile("C:\\Users\\Aldres\\Documents\\Visual Studio 2015\\Projects\\ConsoleApplication4\\ConsoleApplication4\\images\\map.jpg");//�������� ��������

	Sprite maps;//������ �����
	maps.setTexture(map);

	Music music;
	music.openFromFile("C:\\Users\\Aldres\\Documents\\Visual Studio 2015\\Projects\\ConsoleApplication4\\ConsoleApplication4\\audio\\1.ogg");
	music.setVolume(20);
	// music.play(); - �������� ������ 

	Music music1;
	music1.openFromFile("C:\\Users\\Aldres\\Documents\\Visual Studio 2015\\Projects\\ConsoleApplication4\\ConsoleApplication4\\audio\\3.ogg");
	music1.setVolume(20);


	//�������� ������� �����
	wall mywall;
	Texture WALL;
	WALL.loadFromFile("C:\\Users\\Aldres\\Documents\\Visual Studio 2015\\Projects\\ConsoleApplication4\\ConsoleApplication4\\images\\wall.jpg");
	mywall.set(WALL, 400, 400, 30, 30);

	//�������� �����

	//char *charPosText = "GAY";

	Font font;
	font.loadFromFile("C:\\Users\\Aldres\\Documents\\visual studio 2015\\Projects\\ConsoleApplication4\\ConsoleApplication4\\fonts\\arial.ttf");

	Text textx, texty; // ������� ������
	textx.setFont(font); // ��������� ��� �������� ������
	textx.setCharacterSize(20);
	textx.setStyle(sf::Text::Bold);
	textx.setColor(sf::Color::Red);

	texty.setFont(font); // ��������� ��� ���������� ������
	texty.setCharacterSize(20);
	texty.setStyle(sf::Text::Bold);
	texty.setColor(sf::Color::Red);
	

	




	FreeConsole();//������ �������
	Clock clock; //�����
	while (window.isOpen())
	{

		//��������� � ���������
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = 20;//��������

				  //������ ����������
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//�������� ����������
		keyboardFUNK();

		//��� ������
		p.update(time);
		mywall.update();

		//update map
		maps.setTextureRect(IntRect(mapX, mapY, h, w));
		//maps.setScale(1, 1);
		maps.setPosition(0, 0);




		//��������� ������� ������ � �����
		stringstream ssx, ssy;
		ssx << "My X position is: " << setX; // ������� ����� � ������
		textx.setString(ssx.str());
		ssy << "My Y position is: " << setY; // ��������� ����� � ������
		texty.setString(ssy.str());


		

		//����� ������� �� ������� � While(windowsisopen))
		//text.setPosition(setX - mapX, setY - mapY - 60);
		textx.setPosition(0,0);
		texty.setPosition(0, 30);



		//������� ������
		window.clear(Color::White);

	
		window.draw(maps);
		window.draw(mywall.sprite);
		window.draw(p.sprite);
		window.draw(textx);
		window.draw(texty);
		
		window.display();
		
	}
}

