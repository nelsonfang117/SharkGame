#include "Game.h"

/*
Private
*/
// Funciton to initialize window
void Game::initWindow()
{
	// "|" is a bitwise operator so that our window can close and have a title bar
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Shark Revenger", sf::Style::Close | sf::Style::Titlebar);
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
	this->textures["LASER"]->loadFromFile("Textures/laser3.png");
}

void Game::initPlayer()
{
	this->player = new Player();
	// Enemy pos at 20 20
	//this->enemy = new Enemy(20.f, 20.f);
}

void Game::initEnemies()
{
	// Make sure the enemies don't spawn too fast
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

/*
Public
*/
// Our constructor
Game::Game()
{
	// Start the window as game object is made
	this->initWindow();
	this->initTextures();
	this->initPlayer();
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
}

// Our game loop
void Game::run()
{
	// Keep running until user leaves
	while (this->window->isOpen())
	{
		this->update();
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
		if (!isLeft)
		{
			this->lasers.push_back(
				new Laser(this->textures["LASER"],
					this->player->getPos().x + 71,
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
					this->player->getPos().x + 25,
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
			--counter;

			// Check how many bullets there are
			//std::cout << this->lasers.size() << std::endl;
		}

		++counter;
	}
}

// Update our enemies and also combat
void Game::updateEnemiesAndCombat()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -150.f));
		// Reset to zero
		this->spawnTimer = 0.f;
	}

	// Update each enemy
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		this->enemies[i]->update();
		// Top is y coordinate. Remove enemy at the bottom of the screen
		if (this->enemies[i]->getBounds().top > this->window->getSize().y)
		{
			// Remove from vector
			this->enemies.erase(this->enemies.begin() + i);
			--i;
			std::cout << this->enemies.size() << std::endl;
		}
	}
	for (auto* enemy : this->enemies)
	{
		enemy->update();
	}
}

// Update data
void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateLasers();
	this->updateEnemiesAndCombat();
}

// Draws the updated data
void Game::render()
{
	// Clear the old frame
	this->window->clear();

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

	// this->enemy->render(this->window);

	// Finish drawing and then display
	this->window->display();
}