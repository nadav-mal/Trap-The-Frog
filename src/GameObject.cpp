#include "GameObject.h"

// Constructor.
GameObject::GameObject(sf::Vector2f& pos, Objects objEnum)
{
	this->m_sprite.setOrigin(BLOCK_SIZE / 2, BLOCK_SIZE / 2);
	this->setTexture(int(objEnum));
	this->m_sprite.setPosition(pos);
}

// Displays a game object.
void GameObject::display(sf::RenderWindow* window) const
{
	window->draw(this->m_sprite);
}

// Sets the texture.
void GameObject::setTexture(int objEnum)
{
	sf::Texture* temp = Textures::instance().getObjectTexture(int(objEnum));
	this->m_sprite.setTexture(*temp);
}

