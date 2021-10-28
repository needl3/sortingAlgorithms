#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>

class VisualizeSort
{
private:
	const unsigned short FRAMERATE=60;
	int WIDTH = sf::VideoMode::getDesktopMode().width;
	int HEIGHT = sf::VideoMode::getDesktopMode().height;
	const unsigned short POSITION_OFFSET = 1;	//For distinct seperation of rectangle bodies
	
	sf::SoundBuffer *sbuf = new sf::SoundBuffer;
	sf::Sound *sound = new sf::Sound;

	sf::RenderWindow *window;
	sf::Event *events;

	std::thread *sort_thread;

	void shuffle(int*);

	void handleInputs();

protected:
	const unsigned short DATA_BITS = 200,
						 THREAD_DELAY = 10;

	int *data_array;
	int changedIndexes[2];

	bool is_sorted = false, is_sorting = false, kill_signal=false;
	sf::RectangleShape rect_shape;

	void renderChanges(bool lastAnimation = false, void (*fptr) (std::chrono::milliseconds const&) = std::this_thread::sleep_for);

	void swap(const int l_index, const int r_index, void (*fptr)(std::chrono::milliseconds const&) = std::this_thread::sleep_for);

	void playBeep(const int);

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