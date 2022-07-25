#pragma once
#include "GameObject.h"
#include "Animation.h"

// Frog class is in charge of the frog object in the game.
class Frog : public GameObject
{
public:
	Frog(sf::Vector2f pos, Objects objEnum, sf::Vector2f imageCount, float switchTime); // C-tor.
	~Frog() = default; // D-tor.

	// Frog management and getters.
	bool update(float deltaTime);
	bool getIsStuck() const { return this->m_isStuck; }
	bool checkStop();
	int getPos() const { return this->m_currInd; }
	sf::Vector2f getMovement(float deltaTime) const;

	// Setters.
	void setPos(int pos) { this->m_currInd = pos; }
	void setIsStuck(bool stuck) { this->m_isStuck = stuck; }
	void setDirection();
	void setNewPos(sf::Sprite newPos);

private:
	int m_currInd; // 1d index.
	bool m_isStuck; // Frog is circled.

	// For animation.
	Animation m_frogAnim;
	unsigned int m_row;
	float m_speed;
	bool m_faceRight;
	sf::Sprite m_newPosition;
	int m_direction;
}; 