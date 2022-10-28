#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

#include "Cell.h"
#include <vector>
using namespace std;


class Grid
{

	std::vector<Cell> gridVector;
	const int MAX_CELLS = 2500;

	bool startPositionFoundBool = false;
	bool endPositionFoundBool = false;
	//Grid is 50 * 50 in size

	const static int MAX_ROWS = 50;
	const static int MAX_COLS = 50;

	Cell* atIndex(int t_id);
public:
	Grid();
	~Grid();
	void setNeighbours(Cell* t_cell);
	void selectStartEndPositions(sf::RenderWindow& t_window);
	void setupGrid();
	void render(sf::RenderWindow& t_window);
	void update(sf::Time& t_deltatime);

};