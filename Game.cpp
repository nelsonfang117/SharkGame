#include "Game.h"

/*
Private
*/
// Funciton to initialize window
void Game::initWindow()
{
	// "|" is a bitwise operator so that our window can close and have a title bar
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Sharks", sf::Style::Close | sf::Style::Titlebar);
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
	this->enemy = new Enemy(20.f, 20.f);
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->lasers.push_back(new Laser(this->textures["LASER"], this->player->getPos().x + 48, this->player->getPos().y - 110, 0.f, 0.f, 0.f));
	}
}

// Update our bullets
void Game::updateLasers()
{
	for (auto* laser : this->lasers)
	{
		// Render each laser to the window
		laser->update();
	}
}


// Update data
void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->updateLasers();
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

	this->enemy->render(this->window);

	// Finish drawing and then display
	this->window->display();
}