#include "Grid.h"

Cell* Grid::atIndex(int t_id)
{
	int x = t_id % MAX_ROWS;
	int y = t_id / MAX_COLS;
	// does
	int total = x + (y * MAX_COLS);
	return 	&gridVector.at(total);
}

Grid::Grid()
{
	setupGrid();
	Cell theCell;
	theCell.setID(901);
	theCell.setStartColour();
	setNeighbours(&theCell);

	int i = 0;
}

Grid::~Grid()
{
}

void Grid::setNeighbours(Cell* t_cell)
{
	int row = t_cell->xPos;
	int col = t_cell->yPos;

	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue;

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < MAX_ROWS && n_col >= 0 && n_col < MAX_COLS) {

			int id = n_row + (n_col * 50);
			t_cell->setNeighbours(atIndex(id));
			//std::cout <<"ID"<<id<< " Neighbor: " << n_row << "," << n_col << ": " << std::endl;		
		}
	}



}

void Grid::selectStartEndPositions(sf::RenderWindow& t_window)
{
	const  sf::RenderWindow& m_window = t_window;
	sf::Vector2f mousePosition = sf::Vector2f{ sf::Mouse::getPosition(m_window) };


	for (int i = 0; i < MAX_CELLS; i++)
	{
		if (gridVector.at(i).getCellRect().getGlobalBounds().contains(mousePosition))
		{
			if (startPositionFoundBool == false)
			{
				// for the start position  for the algorithim
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					cout << std::to_string(gridVector.at(i).getID()) << endl;
					gridVector.at(i).setStartColour();
					gridVector.at(i).setStartPoint(true);
					startPositionFoundBool = true;
				}
			}

			if (endPositionFoundBool == false)
			{
				// for the start position  for the algorithim
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					cout << std::to_string(gridVector.at(i).getID()) << endl;
					gridVector.at(i).setEndColour();
					gridVector.at(i).setEndPoint(true);
					endPositionFoundBool = true;
				}
			}

		}
	}

}

void Grid::setupGrid()
{
	int j = 0;
	sf::Vector2f position{ 0.0f,0.f };
	for (int i = 0; i < MAX_CELLS; i++)
	{
		Cell cell;
		cell.setupCellRect();
		cell.setPos(position);
		position.x += cell.getCellRect().getSize().x;
		if (position.x == 1500)
		{
			position.y += cell.getCellRect().getSize().y;
			position.x = 0;
		}
		gridVector.push_back(cell);
		gridVector.at(i).setID(j);
		j++;
	}

	int i = 0;
}

void Grid::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		t_window.draw(gridVector.at(i).getCellRect());
	}

}

void Grid::update(sf::Time& t_deltatime)
{

}