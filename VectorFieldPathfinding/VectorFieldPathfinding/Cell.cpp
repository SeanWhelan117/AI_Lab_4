#include "Cell.h"

Cell::Cell()
{

}

Cell::~Cell()
{
}

Cell::Cell(sf::Vector2f t_position, int t_cellID)
{
	m_id = t_cellID;
	m_shape.setSize(sf::Vector2f(1400 / 20, 900 / 20));
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOutlineColor(sf::Color::Cyan);
	m_shape.setOutlineThickness(3);
	m_shape.setPosition(t_position);
	m_isPassable = true;
	m_previousCellId = -1;

}

Cell* Cell::previous() const
{
	return m_previous;
}

int Cell::weight() const
{
	return 1;
}



void Cell::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_shape);

}



void Cell::setMarked(bool t_marked)
{
	m_marked = t_marked;
}

bool Cell::marked() const
{
	return m_marked;
}

void Cell::setPrevious(Cell* previous)
{
	m_previous = previous;
}

void Cell::addNeighbours(int t_cellID)
{
	m_neighbours.push_back(t_cellID);
}

