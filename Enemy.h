#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
class Enemy
{
private:
	unsigned int pointCount;
	const char* names[3] = { "Textures/enemy_mantarayyellow.png", 
		"Textures/enemy_fishwhite.png", 
		"Textures/enemy_jellyfish.png"};
	// sf::CircleShape shape;
	sf::Sprite sprite;
	sf::Texture texture;

	float speed;

	int type;
	int hp;
	int hpMax;
	int damage;
	int points;
	
	void initShape();
	void initVariables(int x);

	void initTexture(int x);
	void initSprite(int x);

public:
	// Enemy();
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	// Accessor
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	const int& getHp() const; // Find enemy hp

	// Mutator
	void dealDamage();

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
