#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Cell
{


	sf::RectangleShape cellRect;
	int ID = 0;
	bool markedBool = false;
	bool startPointSquare = false;
	bool endPointSquare = false;


public:
	//bool getEndPoint();
	void setEndPoint(bool t_endPointSet);
	void setStartPoint(bool t_startPointSet);

	//bool getStartPoint();
	//bool getMarked();
	void setMarked(bool t_marked);

	void setStartColour();
	void setEndColour();

	int getID();


	void setID(int t_id);

	void setPos(sf::Vector2f t_position);

	sf::RectangleShape getCellRect();
	void setupCellRect();



	int xPos;
	int yPos;


	std::vector<Cell*> m_neighbour;
	void setNeighbours(Cell* t_neighbour);

};