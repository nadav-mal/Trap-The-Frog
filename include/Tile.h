#pragma once
#include "GameObject.h"

// Tile class is in charge of the tile object.
class Tile : public GameObject
{

public:
	Tile(sf::Vector2f& pos, Objects objEnum, sf::Vector2u index); // C-tor.
	~Tile() = default; // D-tor.

	// Setter and getter of the state of the tile.
	void setBlocked(bool state);
	bool getIsBlocked() const { return this->m_blocked; }

	// For precision in clicks.
	bool checkInCircle(const sf::Vector2f clickPos);

	// For hovering.
	void setTrans(bool trans);

private:
	bool m_blocked; // Stores if the tile is blocked.
	sf::Vector2u m_index; // Stores the row and col of the tile.
};