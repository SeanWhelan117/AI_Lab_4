#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <SFML/Graphics.hpp>
#include <stack>

class Cell {
public:
	Cell();
	~Cell();
	int id = 0;
	int previousCellid{ -1 };
	bool markedBool = false;
	bool isPassableBool = true;
	bool m_isPuddle = false;
	bool m_isWall = false;

	int m_centreX = 0;
	int m_centreY = 0;

	float hCost;
	int m_pathCost = -1;
	int theCost = -1;


	bool drawCost = false;
	std::vector<int> diagonalList;

	Cell* previousCell;

	Cell(sf::Vector2f t_position, int t_cellID, sf::Font& t_font);
	Cell* previous() const;
	int weight() const;
	void setPrevious(Cell* previous)
	{
		previousCell = previous;
	}
	bool getMarked() const;
	void setMarked(bool t_marked);
	void addNeighbour(int t_cellID);
	void setColor(sf::Vector3f t_RGBValue);
	int returnID() const {
		return id;
	}
	void render(sf::RenderWindow& t_window);

	sf::Text cellCost;
	sf::Font m_fonts;
	void addCost(int m_cost);
	bool showCostBool = false;

	sf::RectangleShape cellShape;

	std::vector<int> neighbours;
	bool pathBool = false;
	int getCost();
	sf::VertexArray vertex;
	sf::RectangleShape vectorLines;
	void update();

	bool drawVectors = false;

};

class Grid
{
public:
	Grid();
	~Grid();
	int notTraversableNum = 200;
	sf::RectangleShape notTraversable[200];
	
	sf::RectangleShape pathItTakes[200];
	std::vector<int> pathFound;

	Cell& returnCell(int t_id);

	bool startPosSelected;
	bool endPosSelected;
	int endPointId;
	int startPointId;
	void neighbours(int t_row, int t_col, std::vector<Cell>& t_cells, int t_current);
	void reset();
	void initialiseMap();
	void update(sf::RenderWindow& t_window);
	int startPosCreate(sf::RenderWindow& t_window);
	int endPosCreate(sf::RenderWindow& t_window);
	void costCalculation();
	void verticalCells(int t_point, int t_row, int t_cost);
	void horizontalCells(int t_point, int t_col, int t_cost);
	void setCellCost(int t_p, int t_col, int t_cal, int t_cost);
	void notTraversableCost();
	void render(sf::RenderWindow& t_window);
	void callAstar(int t_start, int t_end);
	void aStar(Cell* start, Cell* dest);
	Cell* findCellPoint(sf::Vector2f point);

	void generateHeatMap();

	std::vector<Cell>& returnAllCells();
	sf::Vector2f findEndPos(int t_findEndPos);

	//sf::Text m_cellId[2501];
	sf::Font m_font;
	std::vector<std::vector<Cell>> m_cellsVectorArray;
	std::vector<Cell> cellsArray;


	int maxRows = 50;
	int maxCols = 50;
	int m_currentRow;
	int m_currentCol;
	int randomCellId = 0;

	int sizeOfScreen = 750;
	int sizeOfGridCell = 15;
	int maxCells = 2500;
	float PI = 3.14159;

	void generateVertexArrays();
};

