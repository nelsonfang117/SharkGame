#include "Enemy.h"

void Enemy::initShape()
{
	// Random values for radius and point count
	// this->shape.setRadius(rand() % 20 + 20);
	// this->shape.setPointCount(rand() % 20 + 3);
}

void Enemy::initVariables()
{
	this->type		= 0;
	this->hp		= 0;
	this->hpMax		= 10;
	this->damage	= 1;
	this->points	= 5;
}

void Enemy::initTexture(int x)
{
	if (!this->texture.loadFromFile(names[x]))
	{
		std::cout << "ERROR::ENEMY::INITTEXTURE::Could not load texture file." << std::endl;
	}
}

void Enemy::initSprite(int x)
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.2f, 0.2f);
}

// Constructor
Enemy::Enemy(float pos_x, float pos_y)
{
	// Set the sprite location
	sprite.setPosition(pos_x, pos_y);
	int randomInt = rand() % 10 + 1;
	int index;
	if (randomInt % 2 == 0)
	{
		index = 0;
	}
	else
	{
		index = 1;
	}

	/*
	this->initShape();
	this->initVariables();
	this->shape.setPosition(pos_x, pos_y);
	*/
	this->initTexture(index);
	this->initSprite(index);
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
	target->draw(this->sprite);
}

// Code before changing enemies to sprites
/*
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
*/