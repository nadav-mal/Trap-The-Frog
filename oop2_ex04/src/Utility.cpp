#include "Utility.h"

// Constructor.
Utility::Utility()
{
	this->initButtonsFrame();
	this->initButtons();
	this->initBackground();
	this->initWinLoseLevel();
	this->initWinGame();
	this->initClicksCounter();
}

// Draws the buttons.
void Utility::drawButtons(sf::RenderWindow* window) const
{
	window->draw(this->m_buttonsFrame);

	for (auto button : this->m_buttons)
		window->draw(button);
}

// Draws the background.
void Utility::drawBackground(sf::RenderWindow* window) const
{
	window->draw(this->m_gameBG);
}

// Draws the level win banner.
void Utility::drawLevelWin(sf::RenderWindow* window) const
{
	window->draw(this->m_levelWin);
}

// Draws the level lose banner.
void Utility::drawLevelLose(sf::RenderWindow* window) const
{
	window->draw(this->m_levelLose);
}

// Draws the game win banner.
void Utility::drawGameWin(sf::RenderWindow* window) const
{
	window->draw(this->m_gameWin);
}

// Draws the clicks counter.
void Utility::drawClicksCounter(sf::RenderWindow* window) const
{
	window->draw(this->m_clicksText);
}

// Highlights buttons when hovered on.
bool Utility::highlightButton(sf::Vector2f hoverPos)
{
	// Receives the currently hovered button.
	Utility::Button button = checkOnButton(hoverPos);

	// If not a button then returns false.
	if (button == Utility::Button::None)
	{
		this->swapSprite(button);
		return false;
	}

	// If it is a button, display the highlighted version of it.
	if (!this->m_reHover[int(button)])
	{
		this->m_reHover[int(button)] = true;
		
		this->swapSprite(button);
		return true;
	}

	return false;
}

// Swaps the sprite of the hovered button to the highlighted version and all others to normal version.
void Utility::swapSprite(Utility::Button button)
{
	sf::Sprite temp;

	for (int index = 0; index < NUM_OF_BUTTONS; index++)
	{
		if (int(button) == index) // Swaps to hovered sprite.
			this->m_buttons.at(index).setTexture(*Textures::instance().getButtonTexture((index + NUM_OF_BUTTONS)));
		else // Swaps to normal sprite.
		{
			this->m_reHover[index] = false;
			this->m_buttons.at(index).setTexture(*Textures::instance().getButtonTexture(index));
		}
	}
}

// Updates the clicks counter display text.
void Utility::updateClicks()
{
	char clicksInChars[3] = { 0 };
	_itoa(this->m_clicks, clicksInChars, 10);
	std::string clicksString = "Clicks: ";
	clicksString += clicksInChars;
	this->m_clicksText.setString(clicksString);
}

// Check which button was clicked/hovered, if any of the buttons at all.
Utility::Button Utility::checkOnButton(sf::Vector2f clickPos) const
{
	for (int index = 0; index < NUM_OF_BUTTONS; index++)
	{
		if (this->m_buttons.at(index).getGlobalBounds().contains(clickPos))
			return Utility::Button(index);
	}

	// Didn't click/hover on a button.
	return Utility::Button::None;
}

// Initiates the buttons.
void Utility::initButtons()
{
	sf::Vector2f framePos = this->m_buttonsFrame.getPosition();

	// Adjusts the icons we chose to look more aesthetic.
	for (int index = 0; index < NUM_OF_BUTTONS; index++)
	{
		sf::Sprite temp;
		temp.setTexture(*Textures::instance().getButtonTexture(index));
		temp.setPosition(sf::Vector2f(framePos.x + WINDOWS_GAP + (index * (BLOCK_SIZE + WINDOWS_GAP)), framePos.y + WINDOWS_GAP));
		if (index >= int(Utility::Button::Mute))
		{
			temp.setScale(0.8, 0.8);
			temp.setPosition(temp.getPosition().x, temp.getPosition().y + WINDOWS_GAP);
		}
		this->m_buttons.push_back(temp);
		this->m_reHover.push_back(false);			
	}
}

// Initiates the buttons frame.
void Utility::initButtonsFrame()
{
	auto fixedPos = sf::Vector2f((gameWidth - (BOARD_SIZE * BLOCK_SIZE)) / 2, (gameHeight - (BOARD_SIZE * BLOCK_SIZE)) / 2);
	this->m_buttonsFrame.setPosition(sf::Vector2f(fixedPos.x - (buttonsWidth + QUARTER_BLOCK + WINDOWS_GAP), fixedPos.y));
	this->m_buttonsFrame.setSize(sf::Vector2f(buttonsWidth, buttonsHeight));
	this->m_buttonsFrame.setOutlineColor(sf::Color::Black);
	this->m_buttonsFrame.setOutlineThickness(2);
	this->m_buttonsFrame.setFillColor(sf::Color(70, 70, 70, 170));
}

// Initiates the background.
void Utility::initBackground()
{
	this->m_gameBG.setTexture(*Textures::instance().getGameBG());
}

// Initiates the win/lose level banners.
void Utility::initWinLoseLevel()
{
	this->m_levelWin.setTexture(*Textures::instance().getLevelWinTexture()); // Win
	auto frame = m_levelWin.getGlobalBounds();
	this->m_levelWin.setPosition(sf::Vector2f((gameWidth - frame.width) / 2, (gameHeight - frame.height) / 2));

	this->m_levelLose.setTexture(*Textures::instance().getLevelLoseTexture()); // Lose
	frame = m_levelLose.getGlobalBounds();
	this->m_levelLose.setPosition(sf::Vector2f((gameWidth - frame.width) / 2, (gameHeight - frame.height) / 2));
}

// Initiates the game win banner.
void Utility::initWinGame()
{
	this->m_gameWin.setTexture(*Textures::instance().getGameWinTexture());
	this->m_gameWin.setScale(0.8, 0.8);
	auto frame = m_gameWin.getGlobalBounds();
	this->m_gameWin.setPosition(sf::Vector2f((gameWidth - frame.width) / 2, (gameHeight - frame.height) / 2));
}

// Initiates the clicks counter.
void Utility::initClicksCounter()
{
	// Clicks text visuals.
	this->m_clicks = 0;
	this->m_clicksFont.loadFromFile("digital.ttf");
	this->m_clicksText.setFont(this->m_clicksFont);
	this->m_clicksText.setCharacterSize(32);
	this->m_clicksText.setFillColor(sf::Color::White);
	this->m_clicksText.setOutlineThickness(1);
	this->m_clicksText.setOutlineColor(sf::Color::Black);

	// Clicks text positioning.
	auto fixedPos = sf::Vector2f((gameWidth - (BOARD_SIZE * BLOCK_SIZE)) / 2, (gameHeight - (BOARD_SIZE * BLOCK_SIZE)) / 2);
	this->m_clicksText.setPosition(sf::Vector2f(fixedPos.x - (buttonsWidth + (WINDOWS_GAP * 2)), fixedPos.y + BLOCK_SIZE + (WINDOWS_GAP * 2)));
}
