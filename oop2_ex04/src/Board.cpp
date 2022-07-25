#include "Board.h"

// Constructor.
Board::Board(const unsigned int currLevel)
	: m_frog(Frog(START_LOC, GameObject::Objects::Frog, sf::Vector2f(4, 2), 0.3f)), 
	  m_graph(Graph(BOARD_SIZE* BOARD_SIZE)), m_lose(false), m_end(false)
{
	this->initTiles(currLevel);
	this->setBoardFrame();
}

// Draws the board and its content.
void Board::drawBoard(sf::RenderWindow* window) 
{
	window->draw(this->m_boardFrame);

	for (std::vector<Tile> row : this->m_tiles)
		for (Tile tile : row)
			tile.display(window);
	
	this->m_frog.display(window);
}

// Updates the board.
bool Board::updateBoard(const sf::Vector2f pos)
{
	for (int row = 0; row < BOARD_SIZE; row++)
		for (int col = 0; col < BOARD_SIZE; col++)
			if (this->isValidClick(pos, row, col))
			{
				this->saveMove(row, col);
				this->m_graph.handleEdges(row, col, true);
				this->m_tiles[row][col].setBlocked(true);
				this->relocateFrog();
				this->checkLose();
				return true;
			}

	// Returns false if the click position wasn't on a tile in the board.
	return false;
}

// Sets the board's frame.
void Board::setBoardFrame()
{
	auto fixedPos = sf::Vector2f((gameWidth - (BOARD_SIZE * BLOCK_SIZE)) / 2, (gameHeight - (BOARD_SIZE * BLOCK_SIZE)) / 2);
	this->m_boardFrame.setPosition(sf::Vector2f(fixedPos.x - QUARTER_BLOCK, fixedPos.y));
	this->m_boardFrame.setSize(sf::Vector2f(BLOCK_SIZE * (BOARD_SIZE + 0.5), BOARD_SIZE * BLOCK_SIZE));
	this->m_boardFrame.setOutlineColor(sf::Color::Black);
	this->m_boardFrame.setOutlineThickness(2);
	this->m_boardFrame.setFillColor(sf::Color(37, 37, 37, 170));
}

// Relocates the frog on the board.
void Board::relocateFrog()
{
	sf::Vector2f point;
	int index = 0;

	// If the frog is not circled, runs dijkstra's algorithm to find the next step. 
	if (!this->m_frog.getIsStuck())
	{
		index = this->m_graph.shortestPath(this->m_frog.getPos());

		if (index != STUCK)
		{
			point = sf::Vector2f(index / BOARD_SIZE, index % BOARD_SIZE);
			Tile tile = this->m_tiles[point.x][point.y];

			if (!tile.getIsBlocked())
			{
				sf::Sprite frogStep = tile.getSprite();
				this->m_frog.setNewPos(frogStep);
				this->m_frog.setPos(index);
			}
		}
		else
			this->m_frog.setIsStuck(true); // Frog is circled.
	} 

	// It's not else for a reason. Frog might be set to stuck during the first if.
	if(this->m_frog.getIsStuck())
	{
		// Finds an adjacent random empty tile to move to.
		point = findEmptyTile(sf::Vector2f(this->m_frog.getPos() / BOARD_SIZE, this->m_frog.getPos() % BOARD_SIZE));
		if (point == notFound) // The frog is blocked from all sides.
		{
			this->m_lose = false;
			this->m_end = true;
			return;
		}
		sf::Sprite tileSprite = this->m_tiles[point.x][point.y].getSprite();
		this->m_frog.setNewPos(tileSprite);
		this->m_frog.setPos(point.y + (point.x * BOARD_SIZE));
	}
}

// Checks if the user lost (frog reached an outer edge of the board).
void Board::checkLose()
{
	sf::Vector2f frogLoc = sf::Vector2f(this->m_frog.getPos() / BOARD_SIZE, this->m_frog.getPos() % BOARD_SIZE);
	if (frogLoc.x == BOARD_SIZE - 1 || frogLoc.x == 0 || frogLoc.y == (BOARD_SIZE - 1) || frogLoc.y == 0)
		this->m_lose = true;
}

// Shuffles randomly blocked tiles.
void Board::shuffleBlocked(const unsigned int currLevel)
{
	int counter = 0;
	std::vector<bool> places(BOARD_SIZE * BOARD_SIZE, false);
	while (counter < BLOCKED_NUMBER[currLevel]) // Inserts BLOCKED_NUMBER amount of trues (true = blocked).
	{
		places[counter] = true;
		counter++;
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(places.begin(), places.end(), std::default_random_engine(seed)); // Shuffles the BLOCKED_NUMBER trues randomly.

	this->spreadBlocked(places, counter);
}

// Check if a click on the board is valid.
bool Board::isValidClick(const sf::Vector2f pos, int row, int col)
{
	return this->m_tiles[row][col].getSprite().getGlobalBounds().contains(pos) &&
		   !this->m_frog.getSprite().getGlobalBounds().contains(pos) &&
		   this->m_tiles[row][col].checkInCircle(pos) &&
		   !this->m_tiles[row][col].getIsBlocked();
}

// Checks if the cell of the index of the tile is set to true and blocks it if so.
void Board::spreadBlocked(vector<bool>& places, int counter)
{
	for (int index = 0; index < (BOARD_SIZE * BOARD_SIZE) && counter > 0; index++)
	{
		if (places[index] == true)
		{
			if (index == startPos)
			{
				index = this->placeBlocked(places);
				continue;
			}

			std::pair point = std::make_pair(index / BOARD_SIZE, index % BOARD_SIZE);
			this->m_graph.handleEdges(point.first, point.second, true);
			this->m_tiles[point.first][point.second].setBlocked(true);
			counter--;
		}
	}
}

// Places the blocked tiles.
int Board::placeBlocked(vector<bool>& places) const
{
	for (int index = startPos + 1; index < (BOARD_SIZE * BOARD_SIZE); index++)
	{
		if (places[index] == false)
		{
			places[index] = true;
			return (index - 1);
		}
	}

	return startPos;
}

// Randomly finds a random tile which the frog can move to.
sf::Vector2f Board::findEmptyTile(sf::Vector2f frogPos) 
{
	sf::Vector2f neighborLoc = notFound;
	srand(time(NULL));
	int offSet = rand();

	for (int index = 0; index < MAX_EDGES; index++)
	{
		int dir = (offSet + index) % MAX_EDGES;
		if (this->m_graph.isEven(frogPos.x))
			neighborLoc = sf::Vector2f((frogPos.x + evenRowEdges[dir].x), (frogPos.y + evenRowEdges[dir].y));
		else
			neighborLoc = sf::Vector2f((frogPos.x + oddRowEdges[dir].x), (frogPos.y + oddRowEdges[dir].y));

		if (neighborLoc != notFound)
		{
			Tile tile = this->m_tiles[neighborLoc.x][neighborLoc.y];

			if (!tile.getIsBlocked())
				return neighborLoc;
		}
	}

	return notFound;
}

// Highlights tiles on the board which are hovered on.
bool Board::highlightTiles(sf::Vector2f hoverPos)
{
	bool highlighted = false;

	for (int row = 0; row < BOARD_SIZE; row++)
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			if (!this->m_tiles[row][col].getIsBlocked() && int((col + (row * BOARD_SIZE))) != this->m_frog.getPos())
			{
				if (this->m_tiles[row][col].getSprite().getGlobalBounds().contains(hoverPos))
				{
					this->m_tiles[row][col].setTrans(true);
					highlighted = true;
				}
				else
					this->m_tiles[row][col].setTrans(false);
			}
		}

	return highlighted;
}

// Saves the last move for undo and reset.
void Board::saveMove(int row, int col)
{
	sf::Vector2f frogPos = sf::Vector2f(this->m_frog.getPos() / BOARD_SIZE, this->m_frog.getPos() % BOARD_SIZE);
	this->m_moves.push_back(std::make_pair(frogPos, sf::Vector2f(row, col)));
}

// Initiates the tiles.
void Board::initTiles(const unsigned int currLevel)
{
	sf::Vector2f fix = sf::Vector2f((gameWidth - (BOARD_SIZE * BLOCK_SIZE)) / 2, (gameHeight - (BOARD_SIZE * BLOCK_SIZE)) / 2);
	for (int col = 0; col < BOARD_SIZE; col++)
	{
		std::vector<Tile> curr_row;
		sf::Vector2f pos;

		for (int row = 0; row < BOARD_SIZE; row++)
		{
			// There's a difference between even and odd rows.
			if(this->m_graph.isEven(col))
				pos = sf::Vector2f(fix.x + (row * BLOCK_SIZE) - QUARTER_BLOCK, fix.y + col * BLOCK_SIZE);
			else
				pos = sf::Vector2f(fix.x + (row * BLOCK_SIZE) + QUARTER_BLOCK, fix.y + col * BLOCK_SIZE);
			
			// Offset.
			pos.x += (BLOCK_SIZE / 2);
			pos.y += (BLOCK_SIZE / 2);
			curr_row.push_back(Tile(pos, GameObject::Objects::EmptyTile, sf::Vector2u(row, col)));
		}
		this->m_tiles.push_back(curr_row);
	}

	// Shuffles randomly blocked tiles by the current level.
	this->shuffleBlocked(currLevel);
}

// Resets the board.
void Board::reset()
{
	while (!this->m_moves.empty())
		this->undo();
}

// Undoes a move on the board.
void Board::undo()
{
	if (!this->m_moves.empty())
	{
		this->m_lose = false;
		sf::Vector2f lastFrogPos = this->m_moves[this->m_moves.size() - 1].first; // Undoes frog step.
		this->undoFrog(lastFrogPos);
		sf::Vector2f lastTileChanged = this->m_moves[this->m_moves.size() - 1].second; // Undoes tile blocked.
		this->undoTile(lastTileChanged);
		this->m_moves.pop_back();
	}
}

// Undoes the last frog step.
void Board::undoFrog(sf::Vector2f lastFrogPos)
{
	this->m_frog.getSprite().setPosition(this->m_tiles[lastFrogPos.x][lastFrogPos.y].getSprite().getPosition());
	this->m_frog.setNewPos(this->m_tiles[lastFrogPos.x][lastFrogPos.y].getSprite());
	this->m_frog.setPos(lastFrogPos.y + (lastFrogPos.x * BOARD_SIZE));
	this->m_frog.setIsStuck(false);
}

// Undoes the last tile block.
void Board::undoTile(sf::Vector2f lastTileChanged)
{
	this->m_tiles[lastTileChanged.x][lastTileChanged.y].setBlocked(false);
	this->restoreEdge(lastTileChanged.x, lastTileChanged.y);
}

// Restores the edges of a vertice.
void Board::restoreEdge(int row, int col)
{
	unsigned int convertFormula = col + (row * BOARD_SIZE);
	sf::Vector2i neighborLoc;

	for (int index = 0; index < MAX_EDGES; index++)
	{
		if (this->m_graph.isEven(row)) //check if the row is even
			neighborLoc = sf::Vector2i((row + evenRowEdges[index].x), (col + evenRowEdges[index].y));
		else
			neighborLoc = sf::Vector2i((row + oddRowEdges[index].x), (col + oddRowEdges[index].y));

		if (this->m_graph.inGraph(neighborLoc.x) && this->m_graph.inGraph(neighborLoc.y))
		{
			if (!this->m_tiles[neighborLoc.x][neighborLoc.y].getIsBlocked())
			{
				this->m_graph.restore(convertFormula, (neighborLoc.y + (neighborLoc.x * BOARD_SIZE)));
				this->m_graph.restore((neighborLoc.y + (neighborLoc.x * BOARD_SIZE)), convertFormula);
			}
		}
	}
}
