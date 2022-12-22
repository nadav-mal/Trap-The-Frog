#pragma once

// Game settings.
const std::string GAME_NAME = "Circle the Frog"; // Name of the game.
const sf::Vector2f START_LOC = sf::Vector2f(766, 375); // Frog start loc.
const unsigned int startPos = 60; // Frog start index.
const unsigned int gameHeight = 750, gameWidth = 1500, BLOCK_SIZE = 64, QUARTER_BLOCK = 16; // Quarter block is used for offsets.
const unsigned int NUM_OF_LEVELS = 3, BLOCKED_NUMBER[NUM_OF_LEVELS] = { 20, 18, 16 }, NUM_OF_BUTTONS = 5; // Levels and buttons control.
const unsigned int BOARD_SIZE = 11, MAX_EDGES = 6;
const unsigned int buttonsHeight = 120, buttonsWidth = 360; // Buttons bar.
const unsigned int WINDOWS_GAP = 6; // To fill some gaps and fix positions.
const sf::Time cooldown = sf::seconds(2); // Cooldown between levels.
const float endTime = (-0.5); // Time up.
const bool WON = true, LOST = false;

// Defaults.
const int STUCK = -1; // Frog is stuck.
const unsigned int DefaultWeight = 1; // Default weight for edges in graph.
const sf::Vector2f notFound(-1, -1);
const unsigned int DEFAULT_VOLUME = 60;

// Directions for frog.
const unsigned int UP_LEFT = 0, UP_RIGHT = 1, LEFT = 2, RIGHT = 3, DOWN_LEFT = 4, DOWN_RIGHT = 5;

const std::vector<sf::Vector2i> oddRowEdges = {
	sf::Vector2i(-1, 0), // Up left
	sf::Vector2i(-1, 1), // Up right
	sf::Vector2i(0, -1), // Left
	sf::Vector2i(0, 1), // Right
	sf::Vector2i(1, 0), // Down left
	sf::Vector2i(1, 1), // Down right
};

const std::vector<sf::Vector2i> evenRowEdges = {
	sf::Vector2i(-1, -1), // Up left
	sf::Vector2i(-1, 0), // Up right
	sf::Vector2i(0, -1), // Left
	sf::Vector2i(0, 1), // Right
	sf::Vector2i(1, -1), // Down left
	sf::Vector2i(1, 0), // Down right
};
