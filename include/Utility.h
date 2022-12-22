#pragma once
#include "Textures.h"

// Utility class is in charge of the utilities of the program.
class Utility
{
public:
	Utility(); // C-tor.
	~Utility() = default; // D-tor.

	// Enum for buttons (and their highlighted version).
	enum class Button {
		Reset,
		Undo,
		Mute,
		VolumeUp,
		VolumeDown,
		ResetHL,
		UndoHL,
		MuteHL,
		VolumeUpHL,
		VolumeDownHL,
		None,
	};

	// Draw functions.
	void drawButtons(sf::RenderWindow* window) const;
	void drawBackground(sf::RenderWindow* window) const;
	void drawLevelWin(sf::RenderWindow* window) const;
	void drawLevelLose(sf::RenderWindow* window) const;
	void drawGameWin(sf::RenderWindow* window) const;
	void drawClicksCounter(sf::RenderWindow* window) const;

	// For effects.
	bool highlightButton(sf::Vector2f hoverPos);
	void swapSprite(Utility::Button button);
	Utility::Button checkOnButton(sf::Vector2f clickPos) const;

	// Clicks counter management.
	void resetClicks() { this->m_clicks = 0; }
	void decreaseClicks() { if(this->m_clicks > 0) this->m_clicks--; }
	void increaseClicks() { this->m_clicks++; }
	void updateClicks();

private:
	// Buttons sprites.
	sf::RectangleShape m_buttonsFrame;
	std::vector<sf::Sprite> m_buttons;

	// Clicks counter.
	unsigned int m_clicks;
	sf::Font m_clicksFont;
	sf::Text m_clicksText;

	// Other sprites.
	sf::Sprite m_gameBG;
	sf::Sprite m_levelWin;
	sf::Sprite m_levelLose;
	sf::Sprite m_gameWin;

	// Others.
	std::vector<bool> m_reHover;

	// Init functions.
	void initButtons();
	void initButtonsFrame();
	void initBackground();
	void initWinLoseLevel();
	void initWinGame();
	void initClicksCounter();
};