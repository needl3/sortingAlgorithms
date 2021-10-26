#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <SFML/Graphics.hpp>

class VisualizeSort
{
private:
	const unsigned short FRAMERATE=10;
	const int WIDTH = sf::VideoMode::getDesktopMode().width;
	const int HEIGHT = sf::VideoMode::getDesktopMode().height;
	const unsigned short DATA_BITS = 20;

	sf::RenderWindow *window;
	sf::Event *events;

protected:
	int changedIndexes[2];

	bool isSorted = false;

	std::vector<sf::RectangleShape> rects;

	void renderChanges(const int*, bool renderAll = false, bool lastAnimation = false);

	void swap(sf::RectangleShape&, sf::RectangleShape&);

public:
	VisualizeSort();

	virtual void sort(bool debug = false) = 0;

	void displayData();

	void run();

	std::vector<sf::RectangleShape>& giveData();
};
#endif