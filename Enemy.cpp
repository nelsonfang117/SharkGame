#include "Enemy.h"

void Enemy::initShape()
{
	// Random values for radius and point count
	// this->shape.setRadius(rand() % 20 + 20);
	// this->shape.setPointCount(rand() % 20 + 3);
}

void Enemy::initVariables(int x)
{
	if (x == 0)			// Manta Ray
	{
		this->pointCount = rand() % 8 + 3; // max: 10, min: 3
		this->speed = 0.8f;
		this->type = 0;
		this->hpMax = 10;
		this->hp = this->hpMax;
		this->damage = 2;
		this->points = 4;
	}
	else if (x == 1)	// Normal Fish
	{
		this->pointCount = rand() % 8 + 3; // max: 10, min: 3
		this->speed = 1.3f;
		this->type = 0;
		this->hpMax = 10;
		this->hp = this->hpMax;
		this->damage = 4;
		this->points = 100;
	}
	else if (x == 2)	// Jellyfish
	{
		this->pointCount = rand() % 8 + 3; // max: 10, min: 3
		this->speed = 0.5f;
		this->type = 0;
		this->hpMax = 10;
		this->hp = this->hpMax;
		this->damage = 1;
		this->points = 10;
	}
	
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
	int randomInt = rand() % 10 + 1; // 1 to 10
	int index;
	if (randomInt == 10)
	{
		index = 2;
	}
	else if (randomInt % 2 == 0)
	{
		index = 0;
	}
	else 
	{
		index= 1;
	}

	/*
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
	*/
	this->initVariables(index);
	this->initTexture(index);
	this->initSprite(index);
}

// Destructor
Enemy::~Enemy()
{

}

// ACCESSORS
const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

const int& Enemy::getHp() const
{
	return this->hp;
}

// FUNCTIONS
void Enemy::dealDamage()
{
	this->hp -= 10;
	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void Enemy::update()
{
	// Move enemies
	this->sprite.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	// Render our enemy
	target->draw(this->sprite);
}
