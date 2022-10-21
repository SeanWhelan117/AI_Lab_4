#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Grid
{
public:
	Grid();

	void loadFiles();

	void update(sf::Time t_deltaTime);

	void render(sf::RenderWindow& t_window);

private:


};



