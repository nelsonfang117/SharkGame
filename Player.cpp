#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 6.f;
	this->attackCooldownMax = 15.f;
	// We set this so that our first attack is instant
	this->attackCooldown = this->attackCooldownMax;
}

void Player::initTexture()
{
	// Load a texture from file
	if (!this->texture.loadFromFile("Textures/player_cannonshark.png"))
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
	this->initVariables();
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

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

// Check if the player can attack again
const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		// Reset and return true
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
	{
		this->attackCooldown += 0.5f;
	}
	
}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	// Draw out our player sprite
	target.draw(this->sprite);
}
