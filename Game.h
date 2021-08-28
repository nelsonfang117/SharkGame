#pragma once

#include <map>
#include "Player.h"
#include "Laser.h"
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

	// Private functions
	// This function intializes the window
	void initWindow();
	void initTextures();
	void initPlayer();
public:
	Game();
	virtual ~Game();

	// Functions
	void run();

	void updatePollEvents();
	void updateInput();

	void updateLasers();

	void update();
	void render();
};
