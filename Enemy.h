#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
class Enemy
{
private:

	const char* names[2] = { "Textures/enemy_mantaray.png", "Textures/enemy_fish.png" };
	// sf::CircleShape shape;
	sf::Sprite sprite;
	sf::Texture texture;
	int type;
	int hp;
	int hpMax;
	int damage;
	int points;
	
	void initShape();
	void initVariables();

	void initTexture(int x);
	void initSprite(int x);

public:
	// Enemy();
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	// Functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif // !ENEMY_H

// Code before making enemies sprites
/*
#include <SFML/Graphics.hpp>

class Enemy
{
private:
	sf::CircleShape shape;
	int type;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initShape();
	void initVariables();
public:
	// Enemy();
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	// Functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif // !ENEMY_H
*/
