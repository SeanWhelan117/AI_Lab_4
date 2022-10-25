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

	int m_maxRows = 20;
	int m_maxCols = 20;
	int m_currentRow;
	int m_currentCol;


	void neighbours(int t_row, int t_col, std::vector<Cell>& t_cells, int t_current);
	void reset();
	//void initialiseMap(MazeGenerator& maze);
	void update(float dt);
	void render(sf::RenderWindow& t_window);
	void aStar(Cell* start, Cell* dest);
	//void placeImpassables(MazeGenerator& maze);
	//void placeObstacles(MazeGenerator& maze);


	//-------------Not Ideal the way its done below, should have passed on array of enemy objects----------------------
	int i = 0;
	int i2 = 0;
	int i3 = 0;


	std::stack<Cell*> reversedPath;
	std::stack<Cell*> reversedPath2;
	std::stack<Cell*> reversedPath3;

	std::vector<Cell*> path;
	std::vector<Cell*> path2;
	std::vector<Cell*> path3;

	bool wanderingAround = true;
	bool wanderingAround2 = true;
	bool wanderingAround3 = true;

	bool playerCaught = false;
	bool playerCaught2 = false;
	bool playerCaught3 = false;

	bool keepMoving = false;
	bool keepMoving2 = false;
	bool keepMoving3 = false;


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