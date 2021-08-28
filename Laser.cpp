#include "Laser.h"

Laser::Laser()
{
	this->movementSpeed = 0;
}

Laser::Laser(sf::Texture *texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->shape.setTexture(*texture);
	// Laser position
	this->shape.setPosition(pos_x, pos_y);

	this->direction.x = dir_x;
	this->direction.y = dir_y;

	this->movementSpeed = movement_speed;
}

Laser::~Laser()
{

}

const sf::FloatRect Laser::getBound() const
{
	// Get global bounds returns the bounds of the sprite after all of our translations, rotations, scaling, etc.
	return this->shape.getGlobalBounds();
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