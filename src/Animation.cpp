#include "Animation.h"

// Constructor.
Animation::Animation(sf::Texture* texture, sf::Vector2f imageCount, float switchTime)
	: m_imageCount(imageCount), m_switchTime(switchTime), m_totalTime(0.0f)
{
	this->m_currentImage.x = 0;
	this->uvRect.width = texture->getSize().x / float(imageCount.x);
	this->uvRect.height = texture->getSize().y / float(imageCount.y);
}

// Updates the animation.
void Animation::update(int row, float deltaTime, bool faceRight)
{
	this->m_currentImage.y = row;
	this->m_totalTime += deltaTime;

	if (this->m_totalTime >= this->m_switchTime)
	{
		this->m_totalTime -= this->m_switchTime;
		this->m_currentImage.x++;

		if (this->m_currentImage.x >= this->m_imageCount.x)
			this->m_currentImage.x = 0;
	}

	this->uvRect.top = this->m_currentImage.y * this->uvRect.height;

	if (faceRight)
	{
		this->uvRect.left = this->m_currentImage.x * this->uvRect.width;
		this->uvRect.width = abs(this->uvRect.width);
	}
	else
	{
		this->uvRect.left = (m_currentImage.x + 1) * abs(this->uvRect.width);
		this->uvRect.width = -abs(this->uvRect.width);
	}
}
