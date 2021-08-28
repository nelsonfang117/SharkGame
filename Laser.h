#pragma once
#ifndef LASER_H
#define LASER_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Laser
{
private:
	sf::Sprite shape;


	sf::Vector2f direction;
	float movementSpeed;

public:
	Laser();
	// Pos x and pos y is where we create origin position
	Laser(sf::Texture *texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Laser();


	// Accessor
	const sf::FloatRect getBound() const;

	void update();
	void render(sf::RenderTarget* target);
};

#endif // !LASER_H