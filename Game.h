#pragma once

#include <map>
#include <string>
#include <sstream>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Laser.h"
#include "Enemy.h"
#include "Albert.h"
#include <windows.h>

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

	// GUI
	sf::Font font;
	sf::Text pointText;
	sf::Text gameOverText;
	sf::Text endingText;

	// World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Systems
	unsigned int points;

	// Player
	Player* player;
	
	// Player GUI (our health bar)
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	// Alternating shots
	bool isLeft = false;

	// Enemies
	Albert* finalboss;
	bool firstTime = true;
	bool dead = false;

	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	// Enemy* enemy;


	// Private functions
	// This function intializes the window
	void initWindow();

	void initTextures();
	void initGUI();
	void initWorld();
	void initPlayer();
	void initSystems();

	void initEnemies();
	void initAlbert();

	// music 
	sf::SoundBuffer bufferHit;
	sf::SoundBuffer bufferExplosion;
	sf::SoundBuffer bufferUserHit;
	sf::SoundBuffer bufferUserBoundary;
	sf::SoundBuffer bufferLaser;
	sf::SoundBuffer bufferLaugh;
	sf::SoundBuffer bufferAlbertDamage;
	sf::SoundBuffer bufferAlbertDies;

	sf::Sound soundLaser;
	sf::Sound soundUserBoundary;
	sf::Sound soundHit;
	sf::Sound soundExplosion;
	sf::Sound soundUserHit;
	sf::Sound soundLaugh;
	sf::Sound soundAlbertDamage;
	sf::Sound soundAlbertDies;
	sf::Music music;

	bool newMusic = false;

public:
	Game();
	virtual ~Game();

	// Functions
	void run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateLasers();
	void updateEnemies();
	void updateAlbert();
	void updateCombat();

	void update();
	void renderGUI();
	void renderWorld();
	void render();
};
