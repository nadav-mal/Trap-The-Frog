#pragma once
#include "Textures.h"
#include "Macros.h"

// GameObject class is the base class of the objects in the game.
class GameObject 
{
public:
	// Enum for objects.
	enum class Objects
	{
		EmptyTile,
		Frog,
		BlockedTile,
	};

	GameObject(sf::Vector2f& pos, Objects objEnum); // C-tor.
	~GameObject() = default; // D-tor.

	// Game object management.
	void display(sf::RenderWindow* window) const;
	void setTexture(int objEnum);
	sf::Sprite& getSprite() { return this->m_sprite; } 

private:
	sf::Sprite m_sprite; // Stores the sprite of the object.
};