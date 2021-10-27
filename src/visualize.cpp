#include <iostream>
#include "visualize.hpp"
VisualizeSort::VisualizeSort(){
	//Fill the array
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT),"Sort Visualizer");
	events = new sf::Event;
	window->setFramerateLimit(FRAMERATE);

	//Prepare sound after loading to buffer
	sbuf.loadFromFile("../assets/beep.wav");
	sound.setBuffer(sbuf);

	//Prepare data
	sf::RectangleShape rectangle;
	std::vector<float> poss;
	for (int i=0;i<DATA_BITS;i++){
		poss.push_back((float)i/DATA_BITS*HEIGHT);
	}
	std::random_shuffle(poss.begin(),poss.end());
	for (int i=0;i<DATA_BITS;i++){
		rectangle.setSize(sf::Vector2f(WIDTH/DATA_BITS,-poss[i]));
		rectangle.setPosition((float)WIDTH/DATA_BITS*i,HEIGHT);
		rectangle.setFillColor(sf::Color(10,poss[i]/HEIGHT*255,poss[i]/HEIGHT*255));
		rects.push_back(rectangle);
	}
}

void VisualizeSort::playBeep(float pitch){
	sound.setPitch(pitch);
	sound.play();
}
void VisualizeSort::stopBeep(){
	sound.stop();
}

void VisualizeSort::displayData(){
	for (int i=0;i<DATA_BITS;i++){
		std::cout << rects[i].getSize().y << " ";
	}
	std::cout << std::endl;
}

std::vector<sf::RectangleShape>& VisualizeSort::giveData(){
	return rects;
}

void VisualizeSort::swap(sf::RectangleShape& rect1, sf::RectangleShape& rect2){
	sf::RectangleShape tempRect;
	tempRect.setSize(rect1.getSize());
	tempRect.setFillColor(rect1.getFillColor());

	rect1.setSize(rect2.getSize());
	rect1.setFillColor(rect2.getFillColor());

	rect2.setSize(tempRect.getSize());
	rect2.setFillColor(tempRect.getFillColor());
}

void VisualizeSort::renderChanges(const int givenIndexes[], bool renderAll /*= false*/, bool lastAnimation /*=false*/){
	//Check for quit signal
	window->pollEvent(*events);
	if (events->key.code == sf::Keyboard::Q){
		window->close();
		exit(0);
	}

	if (!renderAll and !lastAnimation){
		sf::RectangleShape tempRect;
		for (int i=0;i<2;i++){
			playBeep(1.0f+rects[givenIndexes[i]].getSize().y/HEIGHT);
			tempRect.setPosition(rects[givenIndexes[i]].getPosition());
			tempRect.setSize(sf::Vector2f(rects[givenIndexes[i]].getSize().x,-HEIGHT));
			tempRect.setFillColor(sf::Color::Black);
			window->draw(tempRect);
			window->draw(rects[givenIndexes[i]]);
			stopBeep();
		}
		window->display();
	}else if(renderAll and !lastAnimation){
		//First Display at once
		for(int i=0;i<DATA_BITS;i++){
			window->draw(rects[i]);
		}
		window->display();
		window->display();
	}else if (!renderAll and lastAnimation){
		//Last display animation
		for(int i=0;i<DATA_BITS;i++){
			playBeep(1.0f+rects[i].getSize().y/HEIGHT);
			rects[i].setFillColor(sf::Color::Cyan);
			window->draw(rects[i]);
			window->display();
			stopBeep();
		}
	}
}

void VisualizeSort::run(){
	//Draw initial shuffled states
	renderChanges(changedIndexes,true);
	while(window->isOpen()){
		window->pollEvent(*events);
		switch (events->type){
	        case sf::Event::Closed:
	            window->close();
	            break;
	        case sf::Event::KeyPressed:
	            if (events->key.code == sf::Keyboard::Q)
	                window->close();
				else{
					if (!isSorted){
						renderChanges(changedIndexes,true);
		            	sort();
					}
		        }
	            break; 
    	}
	}
}