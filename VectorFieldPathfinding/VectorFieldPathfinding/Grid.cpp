#include "Grid.h"

class AStarComparer
{
public:
    bool operator()(Cell* t_n1, Cell* t_n2) const
    {
        return (t_n1->m_h + t_n1->m_pathCost) > (t_n2->m_h + t_n2->m_pathCost);

    }
};


Grid::Grid()
{
    if (!m_font.loadFromFile("Assets/Fonts/arial.ttf"))
    {
        std::cout << "error with font file file";
    }

    for (int i = 0; i < 200; i++)
    {
        optimalRouteShape[i].setSize(sf::Vector2f(70, 45));
        optimalRouteShape[i].setFillColor(sf::Color::Magenta);
    }

}

Grid::~Grid()
{

}

Cell& Grid::returnCell(int t_id)
{
    return m_cellsArray.at(t_id);
}

void Grid::neighbours(int t_row, int t_col, std::vector<Cell>& t_cells, int t_current)
{
    // List all neighbors:
    for (int direction = 0; direction < 9; direction++) {
        if (direction == 4) continue; // Skip 4, this is ourself.

        int n_row = t_row + ((direction % 3) - 1); // Neighbor row
        int n_col = t_col + ((direction / 3) - 1); // Neighbor column

        // Check the bounds:
        if (n_row >= 0 && n_row < m_maxRows && n_col >= 0 && n_col < m_maxCols) {

            // A valid neighbor:
            std::cout << "Neighbor: " << n_row << "," << n_col << " - " << t_current << std::endl;
            t_cells.at(t_current).addNeighbours(n_row + (n_col * 20));

            // add the cell id 
            if (direction == 0 || direction == 2 || direction == 6 || direction == 8)
            {
                int diagId = t_cells.at(n_row + (n_col * 20)).m_id;
                t_cells.at(t_current).m_diagonalList.push_back(t_cells.at(n_row + (n_col * 20)).m_id);
            }

        }
    }
}

void Grid::reset()
{
    for (int i = 0; i < m_cellsArray.size(); i++)
    {
        m_cellsArray.at(i).setMarked(false);
        m_cellsArray.at(i).setPrevious(nullptr);
    }

    for (int i = 0; i < 200; i++)
    {
        optimalRouteShape[i].setSize(sf::Vector2f(70, 45));
        optimalRouteShape[i].setFillColor(sf::Color::Magenta);
    }

    for (int i = 0; i < m_cellsArray.size(); i++)
    {
        m_cellsArray.at(i).m_isPassable = true;
    }

    while (!reversedPath.empty())
    {
        reversedPath.pop();

    }

    while (!reversedPath2.empty())
    {
        reversedPath2.pop();

    }

    while (!reversedPath3.empty())
    {
        reversedPath3.pop();
    }

    path.clear();
    path2.clear();
    path3.clear();
}



void Grid::update(float dt)
{
   
}



void Grid::render(sf::RenderWindow& t_window)
{
    for (int index = 0; index < m_cellsArray.size(); index++)
    {
        m_cellsArray.at(index).render(t_window);
        t_window.draw(m_cellId[index]);

    }

    for (int i = 0; i < 200; i++)
    {
        t_window.draw(optimalRouteShape[i]);
    }

}


std::vector<Cell>& Grid::returnAllCells()
{
    return m_cellsArray;
}