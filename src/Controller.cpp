#pragma once

#include "Controller.h"

// Constructor.
Controller::Controller()
    : m_currLevel(0), m_board(Board(0)), m_frogIsMoving(false)
{
	this->initWindow();//Set window size and title
    this->m_sound.playMusic("BackgroundMusic.ogg"); //Background music
}

// Main function which runs the game process.
void Controller::run()
{
    float deltaTime = 0.0f; 

    while (this->m_window->isOpen())
    {
        deltaTime = this->m_clock.restart().asSeconds();

        while (this->m_window->pollEvent(this->m_event))
        {
            switch (this->m_event.type)
            {
            // Closes window.
            case sf::Event::Closed():
                this->m_window->close();
                break;

            // Pressed escape.
            case sf::Event::KeyPressed:
                if (this->m_event.key.code == sf::Keyboard::Escape)
                    this->m_window->close();
                break;

            // Clicked on the window.
            case sf::Event::MouseButtonReleased:
                if(!this->m_frogIsMoving) // If the frog isn't already moving (to complete animation).
                    handleClick(m_window->mapPixelToCoords({ this->m_event.mouseButton.x, this->m_event.mouseButton.y }));
                break;

            // Moved mouse on the window.
            case sf::Event::MouseMoved:
                auto hoverPos = sf::Vector2f(sf::Mouse::getPosition(*this->m_window));
                // Highlights current tile/button and play sound.
                if(this->m_board.highlightTiles(hoverPos)) 
                    this->m_sound.playSound(int(Sound::Sounds::hoverSound));// Plays sound for hover tiles.
                else if(this->m_utility.highlightButton(hoverPos))
                    this->m_sound.playSound(int(Sound::Sounds::hoverSound)); // Plays sound for button.
                break;
            }
        }
        // Updates.
        this->update(deltaTime);
        // Renders.
        this->render();
    }
}

// Updates game.
void Controller::update(float deltaTime)
{
    this->m_frogIsMoving = this->m_board.updateFrog(deltaTime); // Updates frog. 
    this->m_utility.updateClicks(); // Updates clicks counter.
}

// Renders game.
void Controller::render()
{
    this->m_window->clear(sf::Color{ 0x373737FF });

    // Draws.
    this->m_utility.drawBackground(this->m_window);
    this->m_board.drawBoard(this->m_window);
    this->m_utility.drawButtons(this->m_window);
    this->m_utility.drawClicksCounter(this->m_window);
    // End of drawing.

    this->m_window->display();
}

// Handles clicks on the window.
void Controller::handleClick(sf::Vector2f pos)
{   
    if (this->handleButtons(this->m_utility.checkOnButton(pos))) // Handles click on button.
    {
        this->m_sound.playSound(int(Sound::Sounds::buttonClick)); 
        return; // Already found what the user clicked on.
    }

    if (!this->m_board.getIsEnd() && !this->m_board.getIsLose()) // Level has not ended and not lost.
    {
        if (this->m_board.updateBoard(pos)) // Updates the board.
        {
            this->m_utility.increaseClicks(); // Clicks counter++.
            this->m_sound.playSound(int(Sound::Sounds::clickOnEmptyTile));// Empty tile sound.
        }
        else
            this->m_sound.playSound(int(Sound::Sounds::clickOnBlockedTile));// Blocked tile sound.
    }
    else if (this->m_board.getIsLose()) // If lost and ended.
        this->levelWinLose(LOST);

    if(this->m_board.getIsEnd() && !this->m_board.getIsLose()) // Ended and won.
        this->levelWinLose(WON);
}

// Handles clicks on buttons.
bool Controller::handleButtons(Utility::Button button)
{
    switch (button)
    {
    case Utility::Button::Undo:
        this->m_utility.decreaseClicks();
        this->m_board.undo();
        break;
    case Utility::Button::Reset:
        this->m_utility.resetClicks();
        this->m_board.reset();
        break;
    case Utility::Button::Mute:
        this->m_sound.muteVolume();
        break;
    case Utility::Button::VolumeDown:
        this->m_sound.decVolume();
        break;
    case Utility::Button::VolumeUp:
        this->m_sound.incVolume();
        break;
    case Utility::Button::None:
        return false;
    }

    return true;
}

// Loads a level by the number of the current level.
void Controller::loadLevel()
{
    this->m_utility.resetClicks();

    if (this->m_currLevel < NUM_OF_LEVELS) // If didn't end game.
        this->m_board = Board(this->m_currLevel);
    else
        exit(EXIT_SUCCESS);  // Game ended.
}

// Initiates the window.
void Controller::initWindow()
{
    this->m_window = nullptr;
    this->m_video.height = gameHeight;
    this->m_video.width = gameWidth;
    this->m_window = new sf::RenderWindow(this->m_video, GAME_NAME, sf::Style::Default);
}

// Prepares for a new level (win) or the same level (lose).
void Controller::levelWinLose(bool won)
{
    sf::Time timer = cooldown; // Sets a timer to display the banner (win level or win game).
    this->m_clock.restart();

    if (won)
    {
        this->m_currLevel++;
        if (this->m_currLevel < NUM_OF_LEVELS)  // Won level.
        {
            this->m_sound.playSound(int(Sound::Sounds::winLevel));
            this->m_utility.drawLevelWin(this->m_window);
        }
        else // Won game.
        {
            this->m_sound.playSound(int(Sound::Sounds::winGame));
            this->m_utility.drawGameWin(this->m_window);
        }
    }
    else // Lost level.
    {
        this->m_sound.playSound(int(Sound::Sounds::loseLevel));
        this->m_utility.drawLevelLose(this->m_window);
    }

    // Displays the window with the banner.
    this->m_window->display();

    // Timer loop.
    while (timer.asSeconds() > endTime)
        timer -= m_clock.restart();

    this->loadLevel();
}