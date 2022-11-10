#include "Grid.h"

class AStarComparer
{
public:
	bool operator()(Cell* t_n1, Cell* t_n2) const
	{
		return (t_n1->getCost() + t_n1->theCost) > (t_n2->getCost() + t_n2->theCost);

	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL  CELL
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Cell::Cell()
{

}

Cell::~Cell()
{
}

Cell::Cell(sf::Vector2f t_position, int t_cellID, sf::Font& t_font)
{
	cellCost.setFont(t_font);
	id = t_cellID;
	cellShape.setSize(sf::Vector2f(750 / 50, 750 / 50));
	cellShape.setFillColor(sf::Color::Transparent);
	cellShape.setOutlineColor(sf::Color::White);
	cellShape.setOutlineThickness(0.5);
	cellShape.setPosition(t_position);
	isPassableBool = true;
	previousCellid = -1;

	sf::VertexArray v(sf::Lines, 2);

	v[0].color = sf::Color::Red;
	v[1].color = sf::Color::White;
	vertex = v;
}

Cell* Cell::previous() const
{
	return previousCell;
}

int Cell::weight() const
{
	return 1;
}

bool Cell::getMarked() const
{
	return markedBool;
}

int Cell::getCost()
{
	return theCost;
}

void Cell::setMarked(bool t_markedBool)
{
	markedBool = t_markedBool;
}

void Cell::render(sf::RenderWindow& t_window)
{
	t_window.draw(cellShape);
	if (drawCost == true)
	{
		t_window.draw(cellCost);
	}
}

void Cell::addCost(int m_cost)
{
	theCost = m_cost;

	if (theCost != -1)
	{
		cellCost.setPosition(cellShape.getPosition());
		cellCost.setCharacterSize(10U);
		cellCost.setString(std::to_string(m_cost));

		showCostBool = true;
	}
	else
	{
		showCostBool = false;
	}
}

void Cell::addNeighbour(int t_cellID) // adding a cell id to the neighbours
{
	neighbours.push_back(t_cellID);
}

void Cell::setColor(sf::Vector3f t_colourValue)
{
	sf::Uint8 red = t_colourValue.x;
	sf::Uint8 green = t_colourValue.y;
	sf::Uint8 blue = t_colourValue.z;
	cellShape.setFillColor(sf::Color{ red, green ,blue });
}

void Cell::setVectorDistance(sf::Vector2f t_endPos)
{
	if (!m_isWall)
	{
		float lCost = std::numeric_limits<float>::max();

		sf::Vector2f position = sf::Vector2f(cellShape.getPosition().x + 12.5f, cellShape.getPosition().y + 12.5f);
		sf::Vector2f neighbourPosition;

		vertex[0].position = position;


		/*for (Cell* n : neighbours)
		{*/
		//for(int i = 0; i < neighbours.size(); i++)
		//{

		//	//float currentCost = neighbours.at(i).;
		//	currentCost = 100;

		//	neighbourPosition = sf::Vector2f(n->cellShape.getPosition().x + 12.5f, n->cellShape.getPosition().y + 12.5f);

		//	sf::Vector2f v = (neighbourPosition - t_endPos);
		//	float mag = (v.x * v.x) + (v.y * v.y);

		//	currentCost += mag;

		//	if (currentCost < lCost)
		//	{
		//		lCost = currentCost;
		//		vertex[1].position = neighbourPosition;
		//		setNextNode(n);
		//	}
		//}
	}


}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID  GRID
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Grid::Grid()
{
	initialiseMap();
}

Grid::~Grid()
{
}

Cell& Grid::returnCell(int t_id)
{
	return cellsArray.at(t_id);
}

void Grid::neighbours(int t_row, int t_col, std::vector<Cell>& t_cells, int t_currentCell)
{
	// List all neighbors:
	//9 directions. 4 is the currentCell
	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue; 

		//t_row and t_col for neighbour
		int rowNum = t_row + ((direction % 3) - 1); 
		int colNum = t_col + ((direction / 3) - 1);

		//std::cout << "t_row is --" << t_row << "  t_col is -- " << t_col << std::endl;

		// Check the bounds:
		if (rowNum >= 0 && rowNum < maxRows && colNum >= 0 && colNum < maxCols) {

			// A valid neighbor:
			t_cells.at(t_currentCell).addNeighbour(rowNum + (colNum * 50));
			// add the cell id 
			if (direction == 0 || direction == 2 || direction == 6 || direction == 8)
			{
				int diagonalID = t_cells.at(rowNum + (colNum * 50)).id;
				t_cells.at(t_currentCell).diagonalList.push_back(t_cells.at(rowNum + (colNum * 50)).id);
			}
		}
	}
}

void Grid::reset()
{

	for (int i = 0; i < cellsArray.size(); i++)
	{
		cellsArray.at(i).setMarked(false);
		cellsArray.at(i).setPrevious(nullptr);
	}

}

void Grid::initialiseMap()
{
	srand(time(NULL));

	if (!m_font.loadFromFile("Assets/Fonts/ariblk.ttf"))
	{
		std::cout << "error loading font file for the font in Grid.cpp... file called ariblk.ttf";

	}

	sf::Vector2f cellPos{ 0,0 };
	int count = 0;
	for (int row = 0; row < maxRows; row++)
	{

		for (int i = 0; i < maxCols; i++)
		{
			Cell cell(cellPos, count, m_font);

			cellPos.x += sizeOfScreen / 50; // adjusting cell position on screen - x axis
			if (cellPos.x >= sizeOfScreen)
			{
				cellPos.x = 0;
				cellPos.y += sizeOfScreen / 50; // adjusting cell position on screen - y axis
			}

			count++;
			cellsArray.push_back(cell);// pushing back the cell
		}
	}
	int p = 0;


	for (int index = 0; index < notTraversableNum; index++)
	{
		randomCellId = rand() % maxCells;
		notTraversable[index].setSize(sf::Vector2f(sizeOfGridCell, sizeOfGridCell));
		notTraversable[index].setFillColor(sf::Color::Blue);
		
		pathItTakes[index].setSize(sf::Vector2f(sizeOfGridCell, sizeOfGridCell));
		pathItTakes[index].setFillColor(sf::Color::Green);

		notTraversable[index].setPosition((cellsArray.at(randomCellId).cellShape.getPosition()));
		cellsArray.at(randomCellId).setMarked(true);
	}


	for (int i = 0; i < maxCells; i++) // 40 * 40 = 1600
	{
		int xPos = i % 50;
		int yPos = i / 50;
		neighbours(xPos, yPos, cellsArray, i);
	}
	cellsArray.size();
	int i = 0;
	int h = 0;
}

void Grid::update(sf::RenderWindow& t_window) // update method
{
	startPosCreate(t_window);
	endPosCreate(t_window);
}

void Grid::render(sf::RenderWindow& t_window) // rendering the grid
{
	for (int m = 0; m < maxCells; m++)
	{
		cellsArray.at(m).render(t_window);
		//t_window.draw(m_cellsArray.at(index).m_cellcost);
		//t_window.draw(m_cellId[index]);
	}

	for (int i = 0; i < notTraversableNum; i++)
	{
		t_window.draw(notTraversable[i]);
		t_window.draw(pathItTakes[i]);
	}
}

int Grid::startPosCreate(sf::RenderWindow& t_window)
{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && startPosSelected == false)
		{
			sf::Vector2f translateMousePos = sf::Vector2f{ sf::Mouse::getPosition(t_window) };

			int xPos = translateMousePos.x / sizeOfGridCell;
			int yPos = translateMousePos.y / sizeOfGridCell;

			float id = yPos * 50;
			id += xPos;
			if (cellsArray.at(id).getMarked() == false)
			{
				cellsArray.at(id).cellShape.setFillColor(sf::Color::Yellow);
				startPosSelected = true;
				startPointId = id;
				return startPointId;
			}
		}
}

int Grid::endPosCreate(sf::RenderWindow& t_window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && endPosSelected == false)
	{
		sf::Vector2f translateMousePos = sf::Vector2f{ sf::Mouse::getPosition(t_window) };
		int xPos = translateMousePos.x / sizeOfGridCell; 
		int yPos = translateMousePos.y / sizeOfGridCell;
		float id = yPos * 50;
		id += xPos;
		if (cellsArray.at(id).getMarked() == false)
		{
			cellsArray.at(id).cellShape.setFillColor(sf::Color::Blue);
			endPosSelected = true;
			endPointId = id;
			for (int i = 0; i < maxCells; i++) // 40 * 40 = 1600
			{
				cellsArray[i].drawCost = true;
				cellsArray[i].isPassableBool = true;
			}
			costCalculation();
			notTraversableCost();
			generateHeatMap();
			callAstar(startPointId, endPointId);
			return endPointId;
		}
	}
}

void Grid::costCalculation()
{
	if (cellsArray.at(endPointId).getMarked() == false)
	{
		int cost = 0;
		cellsArray[endPointId].addCost(cost);
		horizontalCells(endPointId, +1, cost);
		horizontalCells(endPointId, -1, cost);
		verticalCells(endPointId, 50, cost);
		verticalCells(endPointId, -50, cost);

		setCellCost(endPointId, -50, -1, cost);
		setCellCost(endPointId, -50, +1, cost);
		setCellCost(endPointId, +50, -1, cost);
		setCellCost(endPointId, +50, +1, cost);
	}
}

void Grid::verticalCells(int t_point, int t_row, int t_cost)
{
	int point = t_point;
	int cost = t_cost;
	while (point >= 0 && point < maxCells)
	{
		cellsArray[point].addCost(cost);
		point += t_row;
		cost++;
	}

}

void Grid::horizontalCells(int t_point, int t_col, int t_cost)
{
	int point = t_point + t_col;
	int cost = t_cost + 1;

	if (t_col > 0)
	{
		while (point % 50 <= 50 - 1 && point % 50 != 0)
		{
			cellsArray[point].addCost(cost);
			point += t_col;
			cost++;
		}
	}
	else if (t_col < 0)
	{
		while (point % 50 != 50 - 1 && point % 50 >= 0)
		{
			cellsArray[point].addCost(cost);
			point += t_col;
			cost++;
		}
	}
}

void Grid::setCellCost(int t_p, int t_col, int t_cal, int t_cost)
{
	int pColCalSum = t_p + t_col + t_cal;
	if (pColCalSum > 0 && pColCalSum < maxCells && t_p % 50 == 0)
	{
		cellsArray[pColCalSum].addCost(t_cost + 1);
		verticalCells(pColCalSum, t_col, t_cost + 1);
		verticalCells(pColCalSum, t_col, t_cost + 1);
	}
	else if (pColCalSum > 0 && pColCalSum < maxCells && t_p % 50 >= 50 - 1)
	{
		cellsArray[pColCalSum].addCost(t_cost + 1);
		verticalCells(pColCalSum, t_col, t_cost + 1);
		verticalCells(pColCalSum, t_col, t_cost + 1);
	}
	else if (pColCalSum >= 0 && pColCalSum < maxCells)
	{
		cellsArray[pColCalSum].addCost(t_cost);
		setCellCost(pColCalSum, t_col, t_cal, t_cost + 1);
		verticalCells(pColCalSum, t_col, t_cost + 1);
		verticalCells(pColCalSum, t_col, t_cost + 1);
		horizontalCells(pColCalSum, t_cal, t_cost + 1);
	}
}

void Grid::notTraversableCost()
{
	for (int i = 0; i < maxCells; i++)
	{
		if (cellsArray[i].getMarked() == true) {

			cellsArray[i].addCost(10000);
			cellsArray[i].drawCost = false;
			cellsArray[i].isPassableBool = false;
			cellsArray[i].cellShape.setFillColor(sf::Color::Red);
		}
	}
}
std::vector<Cell>& Grid::returnAllCells() // returning all the cells
{
	return cellsArray;
}

Cell* Grid::findCellPoint(sf::Vector2f point)
{
	for (int i = 0; i < cellsArray.size(); i++)
	{
		if (cellsArray.at(i).cellShape.getGlobalBounds().contains(point))
		{
			return &cellsArray.at(i);
		}
	}
	return nullptr;
}

void Grid::generateHeatMap()
{
	float redColour = 255;

	for (int i = 0; i < 2500; i++)
	{
		if (cellsArray.at(i).isPassableBool == true)
		{
			if (cellsArray.at(i).pathBool == false)
			{
				sf::Vector3f colourValue = { redColour - (cellsArray.at(i).getCost() * 8),0.0f,0.0f };
				if (colourValue.x < 100)
				{
					colourValue.x = 100;
				}
				cellsArray.at(i).setColor(colourValue);
			}
		}
	}
}

void Grid::generateVertexArrays()
{
	for (int i = 0; i < maxCells; i++)
	{
		//cellsArray[i].setVectorDistance(m_endNode->getPosition());
	}
}


void Grid::callAstar(int t_start, int t_end)
{
	Cell* start;
	Cell* end;
	start = &returnCell(t_start);
	end = &returnCell(t_end);
	aStar(start, end);

	int i = 0;
	int index = end->id;

	pathItTakes[i].setPosition(cellsArray.at(index).cellShape.getPosition());
	if (pathFound.empty() == true)
	{
		pathFound.push_back(index);
		while (cellsArray.at(index).previousCell != nullptr)
		{
			//std::cout << m_cellsArray.at(index).m_previous->m_id << std::endl;
			pathFound.push_back(cellsArray.at(index).previousCell->id);
			pathItTakes[i].setPosition(cellsArray.at(index).cellShape.getPosition());
			cellsArray[index].pathBool = true;
			index = cellsArray.at(index).previousCell->id;
			i++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*  A*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Grid::aStar(Cell* start, Cell* dest)
{
	Cell* s = start; // s start node
	Cell* goal = dest; //g goal node
	std::priority_queue<Cell*, std::vector<Cell*>, AStarComparer > pq; //pq = new priority queue

	int dist = std::numeric_limits<int>::max();    // Initialise dist[v] to infinity

	//for each node v in graph G
	for (int i = 0; i < cellsArray.size(); i++)
	{
		int xOne = cellsArray[i].m_centreX;
		int yOne = cellsArray[i].m_centreY;

		int xTwo = goal->m_centreX;
		int yTwo = goal->m_centreY;

		//m_cellsArray[i].m_h = abs(xTwo - xOne) + abs(yTwo - yOne);  //Calculate h[v]

		cellsArray[i].theCost = dist / 10;  //Initialise g[v] to infinity
		cellsArray[i].setPrevious(nullptr);
		cellsArray[i].setMarked(false);
	}

	if (goal != nullptr && start != nullptr)
	{
		start->theCost = 0; //Initialise g[start] to 0
		start->setMarked(true); //Mark(start)
		pq.push(start); //Add start to pq

		while (pq.size() != 0 && pq.top() != goal) //While the queue is not empty AND pq.top() != g
		{
			auto iter = pq.top()->neighbours.begin();
			auto endIter = pq.top()->neighbours.end();

			for (; iter != endIter; iter++) //For each child node of pq.top()
			{
				Cell* mychild = &returnAllCells().at(*iter);
				//std::cout << "Visiting: " << mychild->m_id << std::endl;

				if (mychild != pq.top()->previous()) //If (child !=previous(pq.top())
				{
					float weightOfArc = 0;
					float distToChild = 0;

					weightOfArc = mychild->weight(); //g(child)

					distToChild = (weightOfArc + pq.top()->theCost);

					if (distToChild < mychild->theCost && mychild->isPassableBool == true) //If ( distToChild < f(child) )
					{
						mychild->theCost = distToChild; //let f[child] = distToChild
						mychild->setPrevious(pq.top()); //Set previous pointer of child to pq.top()
						//mychild->m_shape.setFillColor(sf::Color::Red);						//uncomment to see how it expands

						if (mychild == goal)
						{
							std::cout << "uh oh we got it" << std::endl;
						}

					} //End if
					if (mychild->getMarked() == false) //If (notMarked(child))
					{
						//pq.push(mychild);//Add child to the pq
						if (mychild->isPassableBool == true)
						{
							pq.push(mychild);//Add child to the pq
						}
						mychild->setMarked(true); //Mark Child

					} //end if
				}

			}//end for
			pq.pop();
		} //end while
	}
}

