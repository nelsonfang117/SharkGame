#include "Albert.h"

void Albert::initVariables()
{
	this->alive = true;
	this->hpMax = 300;
	this->hp = this->hpMax;
	this->speed = 0.4f;
	this->damage = 90;
	this->points = 1000;
}

void Albert::initTexture()
{
	if (!this->texture.loadFromFile("Textures/enemy_albertfinalboss3.png"))
	{
		std::cout << "ERROR::ALBERT::INITTEXTURE::Could not load texture file." << std::endl;
	}
}

void Albert::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.6f, 0.6f);
}

// Constructor
Albert::Albert(float pos_x, float pos_y)
{
	// Initialized everything
	sprite.setPosition(pos_x, pos_y);
	this->initVariables();
	this->initTexture();
	this->initSprite();
	
}

// Destructor
Albert::~Albert()
{

}

// ACCESSORS
const sf::FloatRect Albert::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Albert::getPoints() const
{
	return this->points;
}

const int& Albert::getDamage() const
{
	return this->damage;
}

const int& Albert::getHp() const
{
	return this->hp;
}

// MUTATORS
void Albert::dealDamage()
{
	this->hp -= 10;
	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

// Functions
void Albert::update()
{
	// Move only if it's not yet 80 pixels past 
	if (getBounds().top < 40.f)
	{
		this->sprite.move(0.f, this->speed);
	}
}

void Albert::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}