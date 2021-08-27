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

}

void Game::initPlayer()
{
	this->player = new Player();
}

/*
Public
*/
// Our constructor
Game::Game()
{
	// Start the window as game object is made
	this->initWindow();
	this->initPlayer();
}

// Destructor
Game::~Game()
{
	delete this->window;
	delete this->player;
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
}

// Update data
void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
}

// Draws the updated data
void Game::render()
{
	// Clear the old frame
	this->window->clear();

	// Draw all stuffs
	this->player->render(*this->window);

	// Finish drawing and then display
	this->window->display();
}