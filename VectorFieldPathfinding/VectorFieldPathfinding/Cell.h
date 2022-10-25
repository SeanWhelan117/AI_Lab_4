#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <functional>
#include <vector>
#include <queue>

class Cell
{
public:
	Cell();
	~Cell();
	Cell(sf::Vector2f t_position, int t_cellID);

	Cell* m_previous;
	Cell* previous() const;

	std::vector<int> m_diagonalList;

	int weight() const;
	int m_id = 0;
	int m_previousCellId{ -1 };
	int m_centreX = 0;
	int m_centreY = 0;
	int m_h;
	int m_pathCost;
	int returnID() const
	{
		return m_id;
	}

	short weights = 100;
	short additionalWallWeight = 200;
	short additionalPuddleWeight = 2;
	short additionalFenceWeight = 3;

	bool m_marked = false;
	bool m_isPassable = true;
	bool isWallObject;
	bool isPuddle;
	bool isBarbed;
	void setMarked(bool t_marked);
	bool marked() const;

	void setPrevious(Cell* previous);
	void addNeighbours(int t_cellID);
	void render(sf::RenderWindow& t_window);

	sf::RectangleShape m_shape;
	std::vector<int> m_neighbours;

};