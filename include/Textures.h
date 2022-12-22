#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

// Textures class uses the singleton method to store textures.
class Textures
{
public:
	// Instance.
	static Textures& instance() {
		static Textures instance;
		return instance;
	}

	// Load textures.
	void loadObjectTexture(const std::string fileName);
	void loadGameBG(const std::string fileName);
	void loadButtonTexture(const std::string fileName);
	void loadLevelWinLoseTextures(const std::string fileName1, const std::string fileName2);
	void loadGameWinTexture(const std::string fileName);

	// Getters.
	sf::Texture* getObjectTexture(int index) { return &(this->m_objectsTextures[index]); }
	sf::Texture* getGameBG() { return &(this->m_gameBG); }
	sf::Texture* getButtonTexture(int index) {	return &(this->m_buttonsTextures[index]); }
	sf::Texture* getLevelWinTexture() { return &(this->m_levelWinTexture); }
	sf::Texture* getLevelLoseTexture() { return &(this->m_levelLoseTexture); }
	sf::Texture* getGameWinTexture() { return &(this->m_gameWinTexture); }

private:
	Textures() {
		// Objects
		loadObjectTexture("EmptyTile.png");
		loadObjectTexture("FrogAnimation.png");
		loadObjectTexture("BlockedTile.png");

		// Buttons
		loadButtonTexture("reset.png");
		loadButtonTexture("undo.png");
		loadButtonTexture("mute.png");
		loadButtonTexture("volumeUp.png");
		loadButtonTexture("volumeDown.png");
		loadButtonTexture("resetHL.png");
		loadButtonTexture("undoHL.png");
		loadButtonTexture("muteHL.png");
		loadButtonTexture("volumeUpHL.png");
		loadButtonTexture("volumeDownHL.png");

		// Etc
		loadGameBG("GameBG.jpg");
		loadLevelWinLoseTextures("LevelComplete.png", "LevelFailed.png");
		loadGameWinTexture("WinGame.png");
	}

	std::vector<sf::Texture> m_objectsTextures; // Stores textures of objects.
	std::vector<sf::Texture> m_buttonsTextures; // Stores textures of buttons.
	sf::Texture m_gameBG; // Stores game background texture.
	sf::Texture m_levelWinTexture; // Stores level win texture.
	sf::Texture m_levelLoseTexture; // Stores level lose texture.
	sf::Texture m_gameWinTexture; // Stores game win texture.
};