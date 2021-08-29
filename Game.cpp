#include "Game.h"
#include <SFML/Audio.hpp>
/*
Private
*/
// Funciton to initialize window
void Game::initWindow()
{
	// "|" is a bitwise operator so that our window can close and have a title bar
	this->window = new sf::RenderWindow(sf::VideoMode(800, 1200), "Space Shark Revenger", sf::Style::Close | sf::Style::Titlebar);
	// We must limit frame rate
	this->window->setFramerateLimit(144);
	// No VSYNC
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	// Adds to map
	this->textures["LASER"] = new sf::Texture();
	// Load texture into map
	this->textures["LASER"]->loadFromFile("Textures/improved_laser.png");
}

// This is where we put text and graphics such as health and points
void Game::initGUI()
{
	// Load font
	if (!this->font.loadFromFile("Fonts/PAPYRUS.ttf"))
	{
		std::cout << "ERROR::GAME::Failed to load font" << std::endl;
	}

	// Init point text
	this->pointText.setPosition(25.f, 80.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(30);
	this->pointText.setFillColor(sf::Color::White);
	// this->pointText.setString("That time I reincarnated as a \nspace shark whose family was \n murdered by an army of \nrobot space fish.");

	// GAME OVER screen
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("GAME OVER!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f, 
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
	

	// Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));


	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Backgrounds/ocean_space4.png"))
	{
		std::cout << "ERROR::GAME::Could not load background texture" << std::endl;
	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initPlayer()
{
	this->player = new Player();
	player->setPosition(350,800);
	// Enemy pos at 20 20
	//this->enemy = new Enemy(20.f, 20.f);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initEnemies()
{
	// Make sure the enemies don't spawn too fast
	this->spawnTimerMax = 20.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initAlbert()
{
	this->finalboss = new Albert(120.f, -400.f);
}
/*
Public
*/
// Our constructor
Game::Game()
{	
	// set soundeffects
	bufferExplosion.loadFromFile("Music/alt_explosion_sfx.wav");
	bufferHit.loadFromFile("Music/hit_sfx.wav");
	bufferUserHit.loadFromFile("Music/player_hit_sound_alt.wav");
	bufferLaser.loadFromFile("Music/laser.wav");
	this->soundLaser.setBuffer(this->bufferLaser);
	this->soundLaser.setVolume(1.f);
	this->soundUserHit.setBuffer(this->bufferUserHit);
	this->soundUserHit.setVolume(5.f);
	this->soundHit.setBuffer(this->bufferHit);
	this->soundHit.setVolume(3.f);
	this->soundExplosion.setBuffer(this->bufferExplosion);
	this->soundExplosion.setVolume(5.f);




	// Start the window as game object is made
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initPlayer();
	this->initSystems();
	this->initEnemies();
}

// Destructor
Game::~Game()
{
	delete this->window;
	delete this->player;

	// Remove all the textures
	// For each thing in map
	for (auto& i : this->textures)
	{
		// Textures is a map, the second of the map is the *texture and the first is simply the string
		delete i.second;
	}

	// Delete all lasers
	for (auto *i : this->lasers)
	{
		delete i;
	}

	// Delete enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}
	if (finalboss != nullptr)
	{
		delete finalboss;
	}
}

// Our game loop
void Game::run()
{
	// Keep running until user leaves
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		if (this->player->getHp() > 0)
		{
			this->update();
		}
		this->render();
	}
}

void Game::updatePollEvents()
{
	// Event, grabs event from window and puts it in e
	sf::Event e;

	while (this->window->pollEvent(e))
	{
		// Close window if close button or escape was pressed
		if ((e.Event::type == sf::Event::Closed) || (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape))
		{
			this->window->close();
		}
	}

}

void Game::updateInput()
{
	// Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		this->player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		this->player->move(0.f, 1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		this->player->move(1.f, 0.f);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		soundLaser.play();
		if (!isLeft)
		{
			this->lasers.push_back(
				new Laser(this->textures["LASER"],
					this->player->getPos().x + 61,
					this->player->getPos().y - 110,
					0.f,
					-1.f,
					5.f));
			isLeft = true;
		}
		else
		{
			this->lasers.push_back(
				new Laser(this->textures["LASER"],
					this->player->getPos().x + 14,
					this->player->getPos().y - 110,
					0.f,
					-1.f,
					5.f));
			isLeft = false;
		}
		/*
		this->lasers.push_back(
			new Laser(this->textures["LASER"], 
			this->player->getPos().x + 48, 
			this->player->getPos().y - 110,
			0.f, 
			-1.f,
			5.f));
		*/
		
	}
}

// Update our GUI
void Game::updateGUI()
{
	// Shows points the player has
	std::stringstream ss;
	ss << "Points: " << this->points;
	this->pointText.setString(ss.str());

	// Update player GUI
	// this->player->setHp(2);
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
	
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	// Collision with left side of screen
	if (this->player->getBounds().left < 0.f)
	{
		// Snap back the player to the 0 x position
		this->player->setPosition(0.f, this->player->getBounds().top);
	}

	// Collision with right side of screen
	 else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	// Collision with top of screen
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}

	// Collision with bottom of screen
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

// Update our bullets
void Game::updateLasers()
{
	unsigned int counter = 0;
	for (auto* laser : this->lasers)
	{
		// Render each laser to the window
		laser->update();

		// Cull laser at top of screen
		if (laser->getBound().top + laser->getBound().height < 0.f)
		{
			// Delete laser
			delete this->lasers.at(counter);
			// Start at beginning of vector, add counter
			this->lasers.erase(this->lasers.begin() + counter);
			// Check how many bullets there are
			//std::cout << this->lasers.size() << std::endl;
		}

		++counter;
	}
}

// Update our enemies
void Game::updateEnemies()
{
	// Spawning

	if (this->points <= 100)
	{
		this->spawnTimer += 0.5f;
	}

	if (this->spawnTimer >= this->spawnTimerMax)
	{
		int point = rand() % this->window->getSize().x;
		if (point >= 0 && point <= 80)
		{
			point += 80;
		}
		else if (point <= 800 && point >= 720)
		{
			point -= 80;
		}
		this->enemies.push_back(new Enemy((float)point, -150.f));
		// Reset to zero
		this->spawnTimer = 0.f;
	}
	
	// Update
	unsigned int counter = 0;
	for (auto* enemy : this->enemies)
	{
		// Render each enemy to the window
		enemy->update();

		// Enemies go off screen
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			// Delete enemy
			delete this->enemies.at(counter);
			// Start at beginning of vector, add counter
			this->enemies.erase(this->enemies.begin() + counter);
		}
		// Collision with enemies
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			// play damage sound effect
			soundUserHit.play();
			// Lose hp
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			// Start at beginning of vector, add counter
			this->enemies.erase(this->enemies.begin() + counter);
		}

		++counter;
	}
}

// Update our final boss
void Game::updateAlbert()
{
	this->finalboss->update();
	if (finalboss->getBounds().intersects(this->player->getBounds()))
	{
		this->player->loseHp(this->finalboss->getDamage());
	}
}

// Update our combat
void Game::updateCombat()
{

	// Update each enemy
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (int k = 0; k < this->lasers.size() && !enemy_deleted; k++)
		{
			// Check if enemy intersects with laser
			if (this->enemies[i]->getBounds().intersects(this->lasers[k]->getBound()))
			{
				this->soundHit.play();
				// Deal damage, only destroy if enemy hp is 0
				this->enemies[i]->dealDamage();
				if (this->enemies[i]->getHp() == 0)
				{
					soundExplosion.play();
					// Increase points for killing enemies.
					this->points += this->enemies[i]->getPoints();
					// Delete enemy
					delete this->enemies[i];
					// Start at beginning of vector, add counter
					this->enemies.erase(this->enemies.begin() + i);
					enemy_deleted = true;
					
				}
				
				delete this->lasers[k];
				this->lasers.erase(this->lasers.begin() + k);
				Sleep(30);
				this->soundHit.stop();
			}
		}
	}

	if (this->points > 100)
	{
		for (int k = 0; k < this->lasers.size(); k++)
		{
			if (firstTime)
			{
				// Call init
				this->initAlbert();
				firstTime = false;
			}
			if (this->finalboss->getBounds().intersects(this->lasers[k]->getBound()))
			{
				// Play sound here:
				this->sound.play();
				this->finalboss->dealDamage();
				if (this->finalboss->getHp() == 0)
				{
					this->points += this->finalboss->getPoints();
					delete this->finalboss;
					dead = true;
				}
				delete this->lasers[k];
				this->lasers.erase(this->lasers.begin() + k);
				Sleep(25);
				this->sound.stop();
			}
		}
	}
	
}

// Update data
void Game::update()
{
	this->updateInput();
	this->player->update();
	this->updateCollision();
	this->updateLasers();

	this->updateEnemies();
	if (this->points > 100)
	{
		if (firstTime)
		{
			// Call init
			this->initAlbert();
			firstTime = false;
		}
		this->updateAlbert();
	}
	this->updateCombat();
	this->updateGUI();
	this->updateWorld();
}

// Draw GUI
void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

// Draw the world stuff (background, etc)
void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

// Draws the updated data
void Game::render()
{
	// Clear the old frame
	this->window->clear();

	// Draw world
	this->renderWorld();

	// Draw all stuffs
	this->player->render(*this->window);

	// Render each laser to the window
	for (auto* laser : this->lasers)
	{
		laser->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	if (this->points > 100)
	{
		if (firstTime)
		{
			// Call init
			this->initAlbert();
			firstTime = false;
		}
		if (finalboss != nullptr)
		{
			if (!dead)
			{
				finalboss->render(this->window);
			}
		}
		
	}
	// this->enemy->render(this->window);

	this->renderGUI();

	// Game over screen
	if (this->player->getHp() <= 0)
	{
		this->window->draw(this->gameOverText);
	}
	// Finish drawing and then display
	this->window->display();
}