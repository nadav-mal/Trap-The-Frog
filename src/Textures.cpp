#include "Textures.h";

// Loads an object's texture.
void Textures::loadObjectTexture(const std::string fileName)
{
	sf::Texture temp;
	temp.loadFromFile(fileName);
	temp.setSmooth(true);
	temp.setRepeated(true);
	m_objectsTextures.push_back(temp);
}

// Loads the game's background.
void Textures::loadGameBG(const std::string fileName)
{
	this->m_gameBG.loadFromFile(fileName);
}

// Loads a button's texture.
void Textures::loadButtonTexture(const std::string fileName)
{
	sf::Texture temp;
	temp.loadFromFile(fileName);
	temp.setSmooth(true);
	temp.setRepeated(true);
	m_buttonsTextures.push_back(temp);
}

// Loads win/lose level textures.
void Textures::loadLevelWinLoseTextures(const std::string fileName1, const std::string fileName2)
{
	this->m_levelWinTexture.loadFromFile(fileName1);
	this->m_levelLoseTexture.loadFromFile(fileName2);
}

// Loads game win texture.
void Textures::loadGameWinTexture(const std::string fileName)
{
	this->m_gameWinTexture.loadFromFile(fileName);
}
