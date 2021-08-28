#include <iostream>
#include "Game.h"
#include <time.h>
#include <string>
#include <SFML/Audio.hpp>
using namespace std;

int main()
{
	// Give a random seed for time
	srand(static_cast<unsigned int>(time(0)));

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Music/music_projectyi.wav"))
	{
		return -1;
	}
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.setVolume(20.f);
	sound.setLoop(true);
	sound.play();
	Game game;
	game.run();
	return 0;
}