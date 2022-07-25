#include "Tile.h"

// Constructor.
Tile::Tile(sf::Vector2f& pos, Objects objEnum, sf::Vector2u index)
	: GameObject(pos, objEnum), m_blocked(false), m_index(index)
{}

// Sets if the tile is blocked or not.
void Tile::setBlocked(bool state)
{
	this->setTrans(false);

	if(state)
		this->setTexture(int(GameObject::Objects::BlockedTile));
	else
		this->setTexture(int(GameObject::Objects::EmptyTile));

	this->m_blocked = state;
}

// Checks if the click position is inside the circle of the tile.
bool Tile::checkInCircle(const sf::Vector2f clickPos) 
{
	int dx = clickPos.x - this->getSprite().getPosition().x;
	int dy = clickPos.y - this->getSprite().getPosition().y;
	float d3 = (dx * dx) + (dy * dy);
	float d = sqrt(d3);

	if (d < (BLOCK_SIZE / 2))
		return true;

	return false;
}

// For hovering effects.
void Tile::setTrans(bool trans)
{
	if (trans)
		this->getSprite().setColor(sf::Color(255, 255, 255, 128));
	else
		this->getSprite().setColor(sf::Color(255, 255, 255, 255));
}