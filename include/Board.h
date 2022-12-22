#pragma once
#include <vector>
#include "Tile.h"
#include "Graph.h"
#include <algorithm> // std::shuffle
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock

// Board class is in charge of the game board management.
class Board 
{
public:
	Board(const unsigned int currLevel); // C-tor.

	// Boolean funcs for management.
	bool updateBoard(const sf::Vector2f pos);
	bool updateFrog(float deltaTime) { return this->m_frog.update(deltaTime); }
	bool getIsLose() const { return this->m_lose; }
	bool getIsEnd() const { return this->m_end; }
	bool isValidClick(const sf::Vector2f pos, int row, int col);
	
	// Board management.
	void reset();
	void undo();
	void undoFrog(sf::Vector2f lastFrogPos);
	void undoTile(sf::Vector2f lastTileChanged);
	void restoreEdge(int row, int col);
	void drawBoard(sf::RenderWindow* window); 
	void setBoardFrame();
	void relocateFrog();
	void checkLose();
	sf::Vector2f findEmptyTile(sf::Vector2f frogPos);

	// New level.
	void shuffleBlocked(const unsigned int currLevel);
	void spreadBlocked(vector<bool>& places, int counter);
	int placeBlocked(vector<bool>& places) const;

	// Board effects.
	bool highlightTiles(sf::Vector2f hoverPos);

private:
	Frog m_frog; // Stores the frog which is on the board.
	Graph m_graph; // Stores the graph of the board.
	bool m_lose; // Stores if board management generated a lose.
	bool m_end; // Stores if it's the end of the current board.
	vector<std::pair<sf::Vector2f, sf::Vector2f>> m_moves; // For undo and reset.
	std::vector<std::vector<Tile>> m_tiles; // Stores the tiles of the game board.
	sf::RectangleShape m_boardFrame; // Stores the game area.

	// Private functions.
	void saveMove(int row, int col);
	void initTiles(unsigned int currLevel);
};