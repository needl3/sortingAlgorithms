#include <iostream>
#include "visualize.hpp"
VisualizeSort::VisualizeSort(){
	//Fill the array
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT),"Sort Visualizer");
	events = new sf::Event;
	window->setFramerateLimit(FRAMERATE);

	//Prepare sound after loading to buffer
	sbuf->loadFromFile("assets/beep.wav");
	sound->setBuffer(*sbuf);

	//Prepare data
	data_array = new int[DATA_BITS];

	for (int i=0;i<DATA_BITS;i++){
		data_array[i] = i;
	}
	shuffle(data_array);
}
VisualizeSort::~VisualizeSort(){
	delete window;
	delete events;
	delete sound;
	delete sbuf;
}
void VisualizeSort::shuffle(int *arr){
	int random_position,temp_var;
	for(int i=0;i<DATA_BITS;i++){
		random_position =rand()%DATA_BITS;
		temp_var = arr[i];
		arr[i] = arr[random_position];
		arr[random_position] = temp_var;
	}
}
void VisualizeSort::setTitle(std::string title){
	window->setTitle(title);
}
void VisualizeSort::playBeep(float pitch){
	sound->setPitch(pitch);
	sound->play();
}
void VisualizeSort::stopBeep(){
	sound->stop();
}

void VisualizeSort::displayData(){
	for (int i=0;i<DATA_BITS;i++){
		std::cout << data_array[i] << " ";
	}
	std::cout << std::endl;
}

int* VisualizeSort::giveData(){
	return data_array;
}

void VisualizeSort::swap(int l_index, int r_index){
	int temp = data_array[r_index];
	data_array[r_index] = data_array[l_index];
	data_array[l_index] = temp;
	changedIndexes[0] = l_index;
	changedIndexes[1] = r_index;
	renderChanges(changedIndexes);
}

void VisualizeSort::renderChanges(const int *givenIndexes, bool renderAll /*= false*/, bool lastAnimation /*=false*/){
	float rect_height;

	//Check for quit signal
	window->pollEvent(*events);
	if (events->key.code == sf::Keyboard::Q){
		window->close();
		exit(0);
	}
	if (!renderAll and !lastAnimation){
		for (int i=0;i<2;i++){
			rect_height = -(float)data_array[givenIndexes[i]]/DATA_BITS*HEIGHT;
			playBeep(1.0f+(float)data_array[givenIndexes[i]]/HEIGHT);

			//Clear previous rectangle
			rect_shape.setPosition(givenIndexes[i]*(rect_width+POSITION_OFFSET),HEIGHT);
			rect_shape.setSize(sf::Vector2f(rect_width,-HEIGHT));
			rect_shape.setFillColor(sf::Color::Black);
			window->draw(rect_shape);

			//Draw updated Rectangle in same position
			rect_shape.setSize(sf::Vector2f(rect_width,rect_height));
			rect_shape.setFillColor(sf::Color(50
									,(float)givenIndexes[i]/WIDTH*255*rect_width
									,(float)data_array[givenIndexes[i]]/HEIGHT*255
									));
			window->draw(rect_shape);
		}
		window->display();
	}else if(renderAll and !lastAnimation){
		//First Display at once
		for(int i=0;i<DATA_BITS;i++){
			rect_height = -(float)data_array[i]/DATA_BITS*HEIGHT;
			rect_shape.setSize(sf::Vector2f(rect_width,rect_height));
			rect_shape.setFillColor(sf::Color(50
									,(float)i/WIDTH*255*rect_width
									,(float)data_array[i]/HEIGHT*255
									));
			rect_shape.setPosition(i*(rect_width+POSITION_OFFSET),HEIGHT);
			window->draw(rect_shape);
		}
		window->display();
		window->display();
	}else if (!renderAll and lastAnimation){
		//Last display animation
		for(int i=0;i<DATA_BITS;i++){
			rect_height = -(float)data_array[i]/DATA_BITS*HEIGHT;
			playBeep(1.0f+(float)data_array[i]/DATA_BITS);
			rect_shape.setFillColor(sf::Color::Cyan);
			rect_shape.setSize(sf::Vector2f(rect_width,rect_height));
			rect_shape.setPosition(i*(rect_width+POSITION_OFFSET),HEIGHT);
			window->draw(rect_shape);
			window->display();
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
//						sort_thread = new std::thread(&VisualizeSort::sort, this,false);
						sort();
					}
		        }
	            break;
    	}
		window->display();
	}
//	sort_thread->detach();
}