#include "Cell.h"

void Cell::setStartColour()
{
    cellRect.setFillColor(sf::Color::Green);
}


//bool Cell::getMarked()
//{
//    return markedBool;
//}


void Cell::setMarked(bool t_marked)
{
    markedBool = t_marked;
}


void Cell::setEndColour()
{
    cellRect.setFillColor(sf::Color::Red);
}

//bool Cell::getEndPoint()
//{
//    return endPointSquare;
//}

int Cell::getID()
{
    return ID;
}

//bool Cell::getStartPoint()
//{
//    return startPointSquare;
//}

void Cell::setEndPoint(bool t_endPointSet)
{
    endPointSquare = t_endPointSet;
    std::cout << "end point set" << std::endl;
}

void Cell::setStartPoint(bool t_startPointSet)
{
    startPointSquare = t_startPointSet;
    std::cout << "start point set" << std::endl;
}



void Cell::setID(int t_id)
{
    ID = t_id;
}

void Cell::setPos(sf::Vector2f t_position)
{
    cellRect.setPosition(t_position);
}



sf::RectangleShape Cell::getCellRect()
{
    return cellRect;
}

void Cell::setupCellRect()
{
    cellRect.setFillColor(sf::Color::Transparent);
    cellRect.setOutlineColor(sf::Color::Cyan);
    cellRect.setOutlineThickness(1.5f);
    cellRect.setSize(sf::Vector2f{ 1500 / 50,1500 / 50 });
}

void Cell::setNeighbours(Cell* t_neighbour)
{
    t_neighbour->setEndColour();
    m_neighbour.push_back(t_neighbour);
}