#pragma once

#include <map>
#include "Player.h"
#include "Laser.h"
#include "Enemy.h"

class Game
{
private:
	// Our game window
	sf::RenderWindow* window;

	// Resources
	// A container class, mapping two things together, for each string, there is a texture
	std::map<std::string, sf::Texture*> textures;

	// Keep track of lasers
	std::vector<Laser*> lasers;

	// Player
	Player* player;
	
	// Alternating shots
	bool isLeft = false;

	// Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	// Enemy* enemy;

	// Private functions
	// This function intializes the window
	void initWindow();

	void initTextures();
	void initPlayer();

	void initEnemies();


public:
	Game();
	virtual ~Game();

	// Functions
	void run();

	void updatePollEvents();
	void updateInput();

	void updateLasers();
	void updateEnemiesAndCombat();
	void update();
	void render();
};
