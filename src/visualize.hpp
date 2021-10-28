#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>

class VisualizeSort
{
private:
	const unsigned short FRAMERATE=60;
	const int WIDTH = sf::VideoMode::getDesktopMode().width;
	const int HEIGHT = sf::VideoMode::getDesktopMode().height;
	const unsigned short POSITION_OFFSET = 1;	//For distinct seperation of rectangle bodies
	
	sf::SoundBuffer *sbuf = new sf::SoundBuffer;
	sf::Sound *sound = new sf::Sound;

	sf::RenderWindow *window;
	sf::Event *events;

	std::thread *sort_thread;

	void shuffle(int*);

protected:
	const unsigned short DATA_BITS = 200;

	int *data_array;
	int changedIndexes[2];

	bool isSorted = false;
	sf::RectangleShape rect_shape;

	void renderChanges(const int*, bool renderAll = false, bool lastAnimation = false);

	void swap(const int l_index, const int r_index);

	void playBeep(const float);

	void stopBeep();

	void setTitle(const std::string);

private:
	const float rect_width = (float)(WIDTH-DATA_BITS*POSITION_OFFSET)/DATA_BITS;

public:
	VisualizeSort();
	~VisualizeSort();

	virtual void sort(bool debug = false) = 0;

	void displayData();

	void run();

	int* giveData();
};
#endif