#include "Laser.h"

Laser::Laser()
{
	this->movementSpeed = 0;
}

Laser::Laser(sf::Texture& texture, float dir_x, float dir_y, float movement_speed)
{
	this->shape.setTexture(texture);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
}

Laser::~Laser()
{

}

void Laser::update()
{
	// Movement
	this->shape.move(this->movementSpeed * this->direction);
}

void Laser::render(sf::RenderTarget* target)
{
	// Draw our target
	target->draw(this->shape);
}