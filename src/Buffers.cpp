#include "Buffers.h"

/* Constructor of Buffers class. */
Buffers::Buffers()
{
	// Loads all the sound buffers.
	loadGameBuffer("clickOnEmptyTileSound.ogg");
	loadGameBuffer("clickOnBlockedTileSound.ogg");
	loadGameBuffer("winLevelSound.ogg");
	loadGameBuffer("loseLevelSound.ogg");
	loadGameBuffer("winGameSound.ogg");
	loadGameBuffer("buttonClick.ogg");
	loadGameBuffer("hoverSound.ogg");
	loadGameBuffer("winGameSound.ogg");
}

/* Function to gain access to the buffers. */
sf::SoundBuffer* Buffers::getGameBuffer(int index)
{
	return &(this->m_gameBuffers[index]);
}

// Makes an instance and is created only once.
Buffers& Buffers::instance()
{
	static Buffers instance;
	return instance;
}

// Function to load a sound buffer.
void Buffers::loadGameBuffer(const std::string fileName)
{
	sf::SoundBuffer temp;
	temp.loadFromFile(fileName);
	this->m_gameBuffers.push_back(temp);
}
