#include "Enemy.h"

void Enemy::initShape()
{
	// Random values for radius and point count
	this->shape.setRadius(rand() % 20 + 20);
	this->shape.setPointCount(rand() % 20 + 3);
}

void Enemy::initVariables()
{
	this->type		= 0;
	this->hp		= 0;
	this->hpMax		= 10;
	this->damage	= 1;
	this->points	= 5;
}

// Constructor
Enemy::Enemy(float pos_x, float pos_y)
{
	this->initShape();
	this->initVariables();
	this->shape.setPosition(pos_x, pos_y);
}

// Destructor
Enemy::~Enemy()
{

}

// Functions
void Enemy::update()
{

}

void Enemy::render(sf::RenderTarget* target)
{
	// Render our enemy
	target->draw(this->shape);
}
