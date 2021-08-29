#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Albert
{
private:
	// Albert sprite
	sf::Sprite sprite;
	sf::Texture texture;

	float speed;
	bool alive;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initVariables();
	void initTexture();
	void initSprite();

public:
	Albert(float pos_x, float pos_y);
	virtual ~Albert();

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

