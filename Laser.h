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
	Laser(sf::Texture& texture, float dir_x, float dir_y, float movement_speed);
	virtual ~Laser();

	void update();
	void render(sf::RenderTarget* target);
};

#endif // !LASER_H