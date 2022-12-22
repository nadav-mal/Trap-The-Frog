#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Macros.h"

/* The Buffers class is in charge of storing all the sound buffers of the game.
 * Buffers uses the singleton method to avoid storing a sound buffer more than once. */
class Buffers
{
public:
	static Buffers& instance(); // Used to gain access to the class.
	sf::SoundBuffer* getGameBuffer(int index); // Used to get a pointer to a sound buffer.
	void loadGameBuffer(const std::string fileName); // Loads a buffer from a file.

private:
	Buffers(); // C-tor
	std::vector<sf::SoundBuffer> m_gameBuffers; // Used to store the sound buffers of the game.
};