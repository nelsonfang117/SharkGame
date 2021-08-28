#include "Player.h"

void Player::initTexture()
{
	// Load a texture from file
	if (!this->texture.loadFromFile("Textures/sharkyface.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << std::endl;
	}
}

void Player::initSprite()
{
	// Set the texture to the sprite
	// This might need a pointer sometimes, be careful
	this->sprite.setTexture(this->texture);

	// Resize the sprite (scales, negative flips)
	this->sprite.scale(0.4f, 0.3f);
}

Player::Player()
{
	this->movementSpeed = 5.f;
	// Texture first!
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{
	// Return the player position
	return this->sprite.getPosition();
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::update()
{

}

void Player::render(sf::RenderTarget& target)
{
	// Draw out our player sprite
	target.draw(this->sprite);
}
