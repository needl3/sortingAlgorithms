#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class VisualizeSort
{
private:
	const unsigned short FRAMERATE=60;
	const int WIDTH = sf::VideoMode::getDesktopMode().width;
	const int HEIGHT = sf::VideoMode::getDesktopMode().height;
	const unsigned short DATA_BITS = 60;

	sf::SoundBuffer sbuf;
//	sbuf.loadFromFile("../assets/beep.wav");
	sf::Sound sound;

	sf::RenderWindow *window;
	sf::Event *events;

protected:
	int changedIndexes[2];

	bool isSorted = false;

	std::vector<sf::RectangleShape> rects;

	void renderChanges(const int*, bool renderAll = false, bool lastAnimation = false);

	void swap(sf::RectangleShape&, sf::RectangleShape&);

	void playBeep(float);

	void stopBeep();

public:
	VisualizeSort();

	virtual void sort(bool debug = false) = 0;

	void displayData();

	void run();

	std::vector<sf::RectangleShape>& giveData();
};
#endif