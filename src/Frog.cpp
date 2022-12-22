#include "Frog.h"

// Constructor.
Frog::Frog(sf::Vector2f pos, Objects objEnum, sf::Vector2f imageCount, float switchTime)
	: m_frogAnim(Textures::instance().getObjectTexture(int(objEnum)), imageCount, switchTime), GameObject(pos, objEnum), m_currInd(startPos)
{
	// Animation settings.
	this->m_speed = 100.f;
	this->m_row = 0;
	this->m_faceRight = true;
	this->getSprite().setScale(0.8, 0.8);
	this->m_isStuck = false;
	this->m_direction = STUCK;
	this->m_newPosition.setPosition(pos);
}

// Updates the frog.
bool Frog::update(float deltaTime)
{
	// Limits clicks while the frog is moving.
	bool stoppedMoving = true;
	sf::Vector2f movement(0.0f, 0.0f);

	// If the frog didn't reach its destination.
	if (!this->checkStop())
		movement = this->getMovement(deltaTime);
	else
		stoppedMoving = false;

	// If standing still.
	if (movement.x == 0.0f && movement.y == 0.0f)
		this->m_row = 1;
	else
	{
		this->m_row = 0;

		// If facing right.
		if (movement.x > 0.0f)
			this->m_faceRight = false;
		else if (movement.x < 0.0f)
			this->m_faceRight = true;
	}

	// Updates.
	this->m_frogAnim.update(this->m_row, deltaTime, this->m_faceRight);
	this->getSprite().setTextureRect(this->m_frogAnim.getUVRect());
	this->getSprite().move(movement);

	// Returns if the frog is still moving.
	return stoppedMoving;
}

// Sets "destination".
void Frog::setNewPos(sf::Sprite newPos)
{
	this->m_newPosition = newPos;
	this->m_newPosition.setScale(0.1, 0.1);
	this->setDirection();
}

// Gets the direction of the movement.
sf::Vector2f Frog::getMovement(float deltaTime) const
{
	sf::Vector2f movement(0.0f, 0.0f);

	switch (this->m_direction)
	{
	case UP_LEFT:
		movement.x -= (this->m_speed * deltaTime) / 2;
		movement.y -= this->m_speed * deltaTime;
		break;
	case UP_RIGHT:
		movement.x += (this->m_speed * deltaTime) / 2;
		movement.y -= this->m_speed * deltaTime;
		break;
	case LEFT:
		movement.x -= this->m_speed * deltaTime;
		break;
	case RIGHT:
		movement.x += this->m_speed * deltaTime;
		break;
	case DOWN_LEFT:
		movement.x -= (this->m_speed * deltaTime) / 2;
		movement.y += this->m_speed * deltaTime;
		break;
	case DOWN_RIGHT:
		movement.x += (this->m_speed * deltaTime) / 2;
		movement.y += this->m_speed * deltaTime;
		break;

	default:
		break;
	}

	return movement;
}

// Sets the direction the frog is jumping towards.
void Frog::setDirection()
{
	sf::Vector2f currPos = this->getSprite().getPosition();
	sf::Vector2f newPos = this->m_newPosition.getPosition();
	if (newPos.x > currPos.x) // Going right.
	{
		if (newPos.y > currPos.y) // Going down.
			this->m_direction = DOWN_RIGHT;

		else if (newPos.y < currPos.y) // Going up.
			this->m_direction = UP_RIGHT;

		else  // Not up or down.
			this->m_direction = RIGHT;
	}
	else if (newPos.x < currPos.x) // Going left.
	{
		if (newPos.y > currPos.y) // Going down.
			this->m_direction = DOWN_LEFT;

		else if (newPos.y < currPos.y) // Going up.
			this->m_direction = UP_LEFT;

		else  // Not up or down.
			this->m_direction = LEFT;
	}
}

// Checks if the frog reached its destination and can stop.
bool Frog::checkStop()
{
	sf::Vector2f frogPos = this->getSprite().getPosition();
	sf::Vector2f tilePos = this->m_newPosition.getPosition();
	
	if (abs(frogPos.x - tilePos.x) < 1 && abs(frogPos.y - tilePos.y) < 1)
	{
		this->getSprite().setPosition(tilePos);
		return true;
	}
	else
		return false;
}
