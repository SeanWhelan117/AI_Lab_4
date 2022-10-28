#pragma once
#include "SFML/Graphics.hpp"
#include "Cell.h"
#include <iostream>
#include <array>
#include <list>
#include <functional>
#include <queue>
#include <vector>
#include <stack>



class Grid
{
public:
	Grid();
	~Grid();
	//Grid(int t_rows, int t_cols);

	Cell& returnCell(int t_id);

	//sf::RectangleShape m_notPassable[400];
	sf::Text m_cellId[400];
	//sf::Vector2f tempWallPosArray[400];

	int m_maxRows = 50;
	int m_maxCols = 50;
	int m_currentRow;
	int m_currentCol;


	void neighbours(int t_row, int t_col, std::vector<Cell>& t_cells, int t_current);
	void reset();
	//void initialiseMap(MazeGenerator& maze);
	void update(float dt);
	void render(sf::RenderWindow& t_window);
	//void placeImpassables(MazeGenerator& maze);
	//void placeObstacles(MazeGenerator& maze);


	//-------------Not Ideal the way its done below, should have passed on array of enemy objects----------------------


	std::vector<Cell>& returnAllCells();
	std::vector<std::vector<Cell>> m_cellsVectorArray;
	std::vector<Cell> m_cellsArray;
	std::vector<Cell>& returnCellsArray()
	{
		return m_cellsArray;
	}

	sf::Font m_font;
	sf::RectangleShape optimalRouteShape[200];


	//Player& myPlayer; //passing player as a ref

};