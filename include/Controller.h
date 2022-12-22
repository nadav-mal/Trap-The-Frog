#pragma once

#include "Board.h" 
#include "Utility.h"
#include "Sound.h"

// Controller class is in charge of controlling the process of the game.
class Controller
{
public:
	Controller(); // C-tor.
	~Controller() = default; // D-tor.

	// Game management.
	void run(); // Main function of the game.

private:
	void update(float deltaTime);
	void render();
	void handleClick(sf::Vector2f pos);
	bool handleButtons(Utility::Button button);
	void loadLevel();
	void levelWinLose(bool won);

	Board m_board; // Stores the board object.
	Utility m_utility; // Stores the utility object.
	Sound m_sound; // Stores the sound object.

	// States in the game.
	bool m_frogIsMoving;
	unsigned int m_currLevel;

	// SFML
	sf::RenderWindow* m_window; // Used to display the game.
	sf::Event m_event; // Used to keep up with the events given.
	sf::VideoMode m_video; // Used to set the window and control it.
	sf::Clock m_clock;

	// Initiation functions.
	void initWindow();
};